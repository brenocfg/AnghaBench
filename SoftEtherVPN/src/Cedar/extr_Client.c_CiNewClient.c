#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_12__ {int /*<<< orphan*/  BuildInfo; int /*<<< orphan*/  VerString; TYPE_1__* Client; } ;
struct TYPE_11__ {int NoSaveLog; TYPE_3__* Cedar; int /*<<< orphan*/  Logger; int /*<<< orphan*/  PulseRecvThread; int /*<<< orphan*/ * GlobalPulse; int /*<<< orphan*/  EncryptedPassword; int /*<<< orphan*/  NotifyCancelList; int /*<<< orphan*/  ref; void* lockForConnect; void* lock; int /*<<< orphan*/  SockList; void* CmSetting; int /*<<< orphan*/  MsSuspendHandler; } ;
typedef  int /*<<< orphan*/  CM_SETTING ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CEDAR_CLIENT_STR ; 
 int /*<<< orphan*/  CLIENT_GLOBAL_PULSE_NAME ; 
 int /*<<< orphan*/  CLIENT_LOG_DIR_NAME ; 
 int /*<<< orphan*/  CLIENT_LOG_PREFIX ; 
 int /*<<< orphan*/  CLog (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  CiApplyInnerVPNServerConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  CiChangeAllVLanMacAddressIfCleared (TYPE_1__*) ; 
 int /*<<< orphan*/  CiChangeAllVLanMacAddressIfMachineChanged (TYPE_1__*) ; 
 int /*<<< orphan*/  CiInitConfiguration (TYPE_1__*) ; 
 int /*<<< orphan*/  CiLoadIniSettings (TYPE_1__*) ; 
 int /*<<< orphan*/  CiPulseRecvThread ; 
 int /*<<< orphan*/  InitWinUi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_SWITCH_DAY ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MakeDir (int /*<<< orphan*/ ) ; 
 int MsIsNt () ; 
 scalar_t__ MsIsWindows7 () ; 
 int /*<<< orphan*/  MsNewSuspendHandler () ; 
 int /*<<< orphan*/ * MsOpenOrCreateGlobalPulse (int /*<<< orphan*/ ) ; 
 TYPE_3__* NewCedar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ *) ; 
 void* NewLock () ; 
 int /*<<< orphan*/  NewLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  NewSockList () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  OSSetHighPriority () ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Win32ReleaseAllDhcp9x (int) ; 
 void* ZeroMalloc (int) ; 
 int /*<<< orphan*/  _II (char*) ; 
 int /*<<< orphan*/  _SS (char*) ; 
 int /*<<< orphan*/ * ci_active_sessions_lock ; 
 scalar_t__ ci_num_active_sessions ; 

CLIENT *CiNewClient()
{
	CLIENT *c = ZeroMalloc(sizeof(CLIENT));

//	StartCedarLog();

	if (ci_active_sessions_lock == NULL)
	{
		ci_active_sessions_lock = NewLock();
		ci_num_active_sessions = 0;
	}

#ifdef	OS_WIN32
	if (MsIsWindows7())
	{
		c->MsSuspendHandler = MsNewSuspendHandler();
	}
#endif	// OS_WIN32


	c->CmSetting = ZeroMalloc(sizeof(CM_SETTING));

	c->SockList = NewSockList();

	c->lock = NewLock();
	c->lockForConnect = NewLock();
	c->ref = NewRef();

	c->Cedar = NewCedar(NULL, NULL);

	c->Cedar->Client = c;

	c->NotifyCancelList = NewList(NULL);

	Sha0(c->EncryptedPassword, "", 0);

#ifdef	OS_WIN32
	c->GlobalPulse = MsOpenOrCreateGlobalPulse(CLIENT_GLOBAL_PULSE_NAME);
#endif	// OS_WIN32

	if (c->GlobalPulse != NULL)
	{
		c->PulseRecvThread = NewThread(CiPulseRecvThread, c);
	}

	CiLoadIniSettings(c);

	// Log Settings
	if(c->NoSaveLog == false)
	{
		MakeDir(CLIENT_LOG_DIR_NAME);
		c->Logger = NewLog(CLIENT_LOG_DIR_NAME, CLIENT_LOG_PREFIX, LOG_SWITCH_DAY);
	}

	CLog(c, "L_LINE");
	CLog(c, "LC_START_2", CEDAR_CLIENT_STR, c->Cedar->VerString);
	CLog(c, "LC_START_3", c->Cedar->BuildInfo);
	CLog(c, "LC_START_1");

#ifdef	OS_WIN32
	{
		// Initialize the Win32 UI
		wchar_t tmp[MAX_SIZE];
		StrToUni(tmp, sizeof(tmp), CEDAR_CLIENT_STR);

		InitWinUi(tmp, _SS("DEFAULT_FONT"), _II("DEFAULT_FONT_SIZE"));
	}
#endif	// OS_WIN32

	// Initialize the settings
	CiInitConfiguration(c);

	// Raise the priority
	OSSetHighPriority();



#ifdef	OS_WIN32
	// For Win9x, release the DHCP address of all the virtual LAN card
	if (MsIsNt() == false)
	{
		Win32ReleaseAllDhcp9x(true);
	}
#endif	// OS_WIN32

	CiChangeAllVLanMacAddressIfMachineChanged(c);

	CiChangeAllVLanMacAddressIfCleared(c);

	// Initialize the internal VPN server
	CiApplyInnerVPNServerConfig(c);

	return c;
}