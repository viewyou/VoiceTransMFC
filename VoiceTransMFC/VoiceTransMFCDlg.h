
// VoiceTransMFCDlg.h: 头文件
//

#pragma once
#pragma comment(lib,"winmm.lib")
#include "stdafx.h"
#include "mmsystem.h"
#include "afxwin.h"
#include "afxsock.h"
#include "resource.h"
#include "MyRTPSession.h"
#include "./lib/G729aCompress.h"

#define InBlocks 4 //存储输入音频数据的单元数
#define OutBlocks 4  //存储输出音频数据的单元数
#define  INP_BUFFER_SIZE 8192// 5120//16384
#define SEND_BUF 512 //1024



struct CAudioData
{
	PBYTE lpdata;
	DWORD dwLength;
};
// CVoiceTransMFCDlg 对话框
class CVoiceTransMFCDlg : public CDialogEx
{
// 构造
public:
	CVoiceTransMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VOICETRANSMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedYes();
	afx_msg void OnBnClickedConnect();


	CEdit m_PortShow;
	CIPAddressCtrl m_IPAddress;
	CString m_TargetIp;
	int m_TargetPort;

	CString GetError(DWORD error);

	friend UINT Audio_Send_Thread(LPVOID lParam);

	void myInit(void); 
	void OnOK(void);
	BOOL m_IsSocCreated;

	HWAVEIN hWaveIn;    //声音输入
	HWAVEOUT hWaveOut;  //输出设备
	

	PWAVEHDR pWaveHdr1, pWaveHdr2;    //相关"头结构体"          
	PWAVEHDR pWaveHdrOut, pWaveHdrOutcpy;
	WAVEFORMATEX m_waveformin, m_waveformout;

	PBYTE pBuffer1, pBuffer2;//输入设备所用缓冲区

	afx_msg LRESULT OnMM_WIM_DATA(UINT wParam, LONG lParam);
	afx_msg LRESULT OnMM_WIM_CLOSE(UINT wParam, LONG lParam);
	afx_msg LRESULT OnMM_WOM_OPEN(UINT wParam, LONG lParam);
	afx_msg LRESULT OnMM_WOM_DONE(UINT wParam, LONG lParam);
	afx_msg LRESULT OnMM_WOM_CLOSE(UINT wParam, LONG lParam);

	 
	

//用于暂存录入后要发送的及接收到的即将要播放的声音文件的循环队列，
	static CAudioData m_AudioDataIn[InBlocks], m_AudioDataOut[OutBlocks];
	static int   nAudioIn, nSend, //录入、发送指针
			nAudioOut, nReceive;//接收、播放指针
							//对于录音和放音都存在和网络的同步问题，主要靠这些指针进行协调	

	CG729aCompress m_729a;
	//	G729a Compress/UnCompress Buffer,dynamic allocate
	char *m_AUnComped;
	char *m_AComped;

	int m_com_length;
	int m_uncom_length;

	
};

