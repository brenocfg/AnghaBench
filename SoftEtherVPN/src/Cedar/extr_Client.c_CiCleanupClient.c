#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int HaltPulseThread; int /*<<< orphan*/ * MsSuspendHandler; struct TYPE_6__* CmSetting; int /*<<< orphan*/  SockList; int /*<<< orphan*/  NotifyCancelList; int /*<<< orphan*/ * GlobalPulse; int /*<<< orphan*/ * PulseRecvThread; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * lockForConnect; int /*<<< orphan*/  Cedar; int /*<<< orphan*/ * Logger; int /*<<< orphan*/  Eraser; } ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLog (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  CiFreeConfiguration (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeEraser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeLog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeSockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeWinUi () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  MsCloseGlobalPulse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsFreeSuspendHandler (int /*<<< orphan*/ *) ; 
 int MsIsNt () ; 
 int /*<<< orphan*/  MsSendGlobalPulse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopCedarLog () ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Win32ReleaseAllDhcp9x (int) ; 
 int /*<<< orphan*/ * ci_active_sessions_lock ; 
 scalar_t__ ci_num_active_sessions ; 

void CiCleanupClient(CLIENT *c)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}


	// Release the settings
	CiFreeConfiguration(c);

#ifdef	OS_WIN32
	// Release the Win32 UI
	FreeWinUi();
#endif	// OS_WIN32

	CLog(c, "LC_END");
	CLog(c, "L_LINE");
	FreeEraser(c->Eraser);
	FreeLog(c->Logger);
	c->Logger = NULL;


	ReleaseCedar(c->Cedar);

	DeleteLock(c->lockForConnect);
	DeleteLock(c->lock);

	c->HaltPulseThread = true;

	if (c->GlobalPulse != NULL)
	{
#ifdef	OS_WIN32
		MsSendGlobalPulse(c->GlobalPulse);
#endif	// OS_WIN32
	}

	if (c->PulseRecvThread != NULL)
	{
		WaitThread(c->PulseRecvThread, INFINITE);
		ReleaseThread(c->PulseRecvThread);
	}

	if (c->GlobalPulse != NULL)
	{
#ifdef	OS_WIN32
		MsCloseGlobalPulse(c->GlobalPulse);
#endif	// OS_WIN32
	}

	ReleaseList(c->NotifyCancelList);

	FreeSockList(c->SockList);

	Free(c->CmSetting);


#ifdef	OS_WIN32
	if (c->MsSuspendHandler != NULL)
	{
		MsFreeSuspendHandler(c->MsSuspendHandler);
	}
#endif	// OS_WIN32

	Free(c);

#ifdef	OS_WIN32
	// For Win9x, release the DHCP address of all the virtual LAN card
	if (MsIsNt() == false)
	{
		Win32ReleaseAllDhcp9x(true);
	}
#endif	// OS_WIN32

	StopCedarLog();

	if (ci_active_sessions_lock != NULL)
	{
		DeleteLock(ci_active_sessions_lock);
		ci_active_sessions_lock = NULL;

		ci_num_active_sessions = 0;
	}
}