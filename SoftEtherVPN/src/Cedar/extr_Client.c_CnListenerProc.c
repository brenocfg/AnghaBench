#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  function ;
struct TYPE_17__ {int* addr; } ;
struct TYPE_19__ {TYPE_1__ LocalIP; int /*<<< orphan*/  ref; } ;
struct TYPE_18__ {TYPE_3__* s; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ TCP_ACCEPTED_PARAM ;
typedef  TYPE_3__ SOCK ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  APPID_CM ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CnCheckCert (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CnConnectErrorDlg (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CnExecDriverInstaller (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CnMsgDlg (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CnNicInfo (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CnPasswordDlg (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CnReleaseSocket (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CnSecureSign (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CnStatusPrinter (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Disconnect (TYPE_3__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JL_SetCurrentProcessExplicitAppUserModelID (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MsGetCurrentTerminalSessionId () ; 
 int /*<<< orphan*/  MsTerminateProcess () ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/ * RecvPack (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_3__*) ; 
 int /*<<< orphan*/  SendPack (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 

void CnListenerProc(THREAD *thread, void *param)
{
	TCP_ACCEPTED_PARAM *data = (TCP_ACCEPTED_PARAM *)param;
	SOCK *s;
	PACK *p;
	// Validate arguments
	if (data == NULL || thread == NULL)
	{
		return;
	}

#ifdef	OS_WIN32
	//Set Application ID
	JL_SetCurrentProcessExplicitAppUserModelID(APPID_CM);
#endif	// OS_WIN32

	s = data->s;
	AddRef(s->ref);
	NoticeThreadInit(thread);

	if (s->LocalIP.addr[0] == 127)
	{
		p = RecvPack(s);

		if (p != NULL)
		{
			char function[MAX_SIZE];

			if (PackGetStr(p, "function", function, sizeof(function)))
			{
				if (StrCmpi(function, "status_printer") == 0)
				{
					CnStatusPrinter(s, p);
				}
				else if (StrCmpi(function, "connecterror_dialog") == 0)
				{
					CnConnectErrorDlg(s, p);
				}
				else if (StrCmpi(function, "msg_dialog") == 0)
				{
					CnMsgDlg(s, p);
				}
				else if (StrCmpi(function, "nicinfo") == 0)
				{
					CnNicInfo(s, p);
				}
				else if (StrCmpi(function, "password_dialog") == 0)
				{
					CnPasswordDlg(s, p);
				}
				else if (StrCmpi(function, "secure_sign") == 0)
				{
					CnSecureSign(s, p);
				}
				else if (StrCmpi(function, "check_cert") == 0)
				{
					CnCheckCert(s, p);
				}
				else if (StrCmpi(function, "exit") == 0)
				{
#ifdef	OS_WIN32
					MsTerminateProcess();
#else	// OS_WIN32
					_exit(0);
#endif	// OS_WIN32
				}
				else if (StrCmpi(function, "get_session_id") == 0)
				{
					PACK *p = NewPack();
#ifdef	OS_WIN32
					PackAddInt(p, "session_id", MsGetCurrentTerminalSessionId());
#endif	// OS_WIN32
					SendPack(s, p);
					FreePack(p);
				}
				else if (StrCmpi(function, "exec_driver_installer") == 0)
				{
					CnExecDriverInstaller(s, p);
				}
				else if (StrCmpi(function, "release_socket") == 0)
				{
					// Stop the listener
					CnReleaseSocket(s, p);
				}
			}

			FreePack(p);
		}
	}

	Disconnect(s);
	ReleaseSock(s);
}