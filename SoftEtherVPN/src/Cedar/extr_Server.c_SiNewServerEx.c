#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int CheckExpires; int Bridge; TYPE_1__* Server; int /*<<< orphan*/  BuildInfo; int /*<<< orphan*/  VerString; int /*<<< orphan*/  ServerStr; } ;
struct TYPE_20__ {int Me; int /*<<< orphan*/  Weight; void* HubList; int /*<<< orphan*/  hostname; TYPE_3__* Cedar; } ;
struct TYPE_19__ {int NoHighPriorityProcess; scalar_t__ ServerType; int FarmControllerInited; int DisableNatTraversal; TYPE_3__* Cedar; int /*<<< orphan*/  EnableVpnOverDns; void* DynListenerDns; int /*<<< orphan*/  EnableVpnOverIcmp; void* DynListenerIcmp; int /*<<< orphan*/  NatTGlobalUdpPort; int /*<<< orphan*/ * AzureClient; void* FarmMemberList; TYPE_2__* Me; int /*<<< orphan*/  Weight; int /*<<< orphan*/  FarmController; void* SyslogLock; int /*<<< orphan*/  ListenIP; int /*<<< orphan*/  Syslog; int /*<<< orphan*/  Logger; int /*<<< orphan*/  Keep; void* TasksFromFarmControllerLock; int /*<<< orphan*/  StartTime; void* ServerListenerList; int /*<<< orphan*/  AzureServer; int /*<<< orphan*/  IsInVm; int /*<<< orphan*/  ref; void* SaveCfgLock; void* OpenVpnSstpConfigLock; void* lock; int /*<<< orphan*/  MyRandomKey; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  LISTENER ;
typedef  TYPE_2__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (void*,TYPE_2__*) ; 
 int /*<<< orphan*/  BRIDGE_LOG_DIR_NAME ; 
 int /*<<< orphan*/ * CompareHubList ; 
 int /*<<< orphan*/ * CompareServerListener ; 
 int /*<<< orphan*/  DEFAULT_GETIP_THREAD_MAX_NUM ; 
 int /*<<< orphan*/  DisableRDUPServerGlobally () ; 
 int /*<<< orphan*/  GetMachineName (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitServerCapsCache (TYPE_1__*) ; 
 scalar_t__ IsFileExists (char*) ; 
 int IsHamMode () ; 
 int /*<<< orphan*/  LISTENER_DNS ; 
 int /*<<< orphan*/  LISTENER_ICMP ; 
 int /*<<< orphan*/  LISTENER_INPROC ; 
 int /*<<< orphan*/  LISTENER_REVERSE ; 
 int /*<<< orphan*/  LISTENER_RUDP ; 
 int /*<<< orphan*/  LOG_SWITCH_DAY ; 
 int /*<<< orphan*/  MEM_FIFO_REALLOC_MEM_SIZE ; 
 int /*<<< orphan*/  MakeDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsIsInVm () ; 
 int /*<<< orphan*/  NewAzureServer (TYPE_3__*) ; 
 TYPE_3__* NewCedar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* NewDynamicListener (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListener (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewListenerEx4 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* NewLock () ; 
 int /*<<< orphan*/  NewLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  NewSysLog (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSetHighPriority () ; 
 int /*<<< orphan*/  RAND_PORT_ID_SERVER_LISTEN ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RegistWindowsFirewallAll () ; 
 int /*<<< orphan*/  ReleaseListener (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVER_LOG_DIR_NAME ; 
 int /*<<< orphan*/  SERVER_LOG_PERFIX ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  SLog (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  SetCedarVpnBridge (TYPE_3__*) ; 
 int /*<<< orphan*/  SetEraserCheckInterval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFifoCurrentReallocMemSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetGetIpThreadMaxNum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiInitConfiguration (TYPE_1__*) ; 
 int /*<<< orphan*/  SiInitDeadLockCheck (TYPE_1__*) ; 
 int /*<<< orphan*/  SiInitHubCreateHistory (TYPE_1__*) ; 
 int /*<<< orphan*/  SiStartConnectToController (TYPE_1__*) ; 
 int /*<<< orphan*/  SiStartFarmControl (TYPE_1__*) ; 
 int /*<<< orphan*/  SiUpdateCurrentRegion (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 int /*<<< orphan*/  StartKeep () ; 
 int /*<<< orphan*/  SystemTime64 () ; 
 int /*<<< orphan*/  TCPAcceptedThread ; 
 int /*<<< orphan*/  UnixIsInVm () ; 
 int /*<<< orphan*/  UnixSetHighOomScore () ; 
 void* ZeroMalloc (int) ; 

SERVER *SiNewServerEx(bool bridge, bool in_client_inner_server, bool relay_server)
{
	SERVER *s;
	LISTENER *inproc;
	LISTENER *azure;
	LISTENER *rudp;

	SetGetIpThreadMaxNum(DEFAULT_GETIP_THREAD_MAX_NUM);

	s = ZeroMalloc(sizeof(SERVER));

	SetEraserCheckInterval(0);

	SiInitHubCreateHistory(s);

	InitServerCapsCache(s);

	Rand(s->MyRandomKey, sizeof(s->MyRandomKey));

	s->lock = NewLock();


	s->OpenVpnSstpConfigLock = NewLock();
	s->SaveCfgLock = NewLock();
	s->ref = NewRef();
	s->Cedar = NewCedar(NULL, NULL);
	s->Cedar->Server = s;


#ifdef	OS_WIN32
	s->IsInVm = MsIsInVm();
#else	// OS_WIN32
	s->IsInVm = UnixIsInVm();
#endif	// OS_WIN32

#ifdef	ENABLE_AZURE_SERVER
	if (IsFileExists("@azureserver.config"))
	{
		DisableRDUPServerGlobally();
		s->AzureServer = NewAzureServer(s->Cedar);

		SleepThread(500);
	}
#endif	// ENABLE_AZURE_SERVER

	s->Cedar->CheckExpires = true;
	s->ServerListenerList = NewList(CompareServerListener);
	s->StartTime = SystemTime64();
	s->TasksFromFarmControllerLock = NewLock();

	if (bridge)
	{
		SetCedarVpnBridge(s->Cedar);
	}

#ifdef OS_WIN32
	if (IsHamMode() == false)
	{
		RegistWindowsFirewallAll();
	}
#endif

	s->Keep = StartKeep();

	// Log related
	MakeDir(bridge == false ? SERVER_LOG_DIR_NAME : BRIDGE_LOG_DIR_NAME);
	s->Logger = NewLog(bridge == false ? SERVER_LOG_DIR_NAME : BRIDGE_LOG_DIR_NAME, SERVER_LOG_PERFIX, LOG_SWITCH_DAY);

	SLog(s->Cedar, "L_LINE");
	SLog(s->Cedar, "LS_START_2", s->Cedar->ServerStr, s->Cedar->VerString);
	SLog(s->Cedar, "LS_START_3", s->Cedar->BuildInfo);
	SLog(s->Cedar, "LS_START_UTF8");
	SLog(s->Cedar, "LS_START_1");



	// Initialize the configuration
	SiInitConfiguration(s);

	s->Syslog = NewSysLog(NULL, 0, &s->Cedar->Server->ListenIP);
	s->SyslogLock = NewLock();

	SetFifoCurrentReallocMemSize(MEM_FIFO_REALLOC_MEM_SIZE);


	// Raise the priority
	if (s->NoHighPriorityProcess == false)
	{
		OSSetHighPriority();
	}

#ifdef	OS_UNIX
	UnixSetHighOomScore();
#endif	// OS_UNIX

	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		// Start a connection to the controller
		s->FarmController = SiStartConnectToController(s);
	}
	else if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		FARM_MEMBER *f;
		// Start operating as a controller
		s->FarmMemberList = NewList(NULL);

		f = ZeroMalloc(sizeof(FARM_MEMBER));
		f->Cedar = s->Cedar;
		GetMachineName(f->hostname, sizeof(f->hostname));
		f->Me = true;
		f->HubList = NewList(CompareHubList);
		f->Weight = s->Weight;

		s->Me = f;

		Add(s->FarmMemberList, f);

		SiStartFarmControl(s);

		s->FarmControllerInited = true;
	}

	// Start a in-processlistener 
	inproc = NewListener(s->Cedar, LISTENER_INPROC, 0);
	ReleaseListener(inproc);

	// Start a listener for Azure
	if (s->AzureClient != NULL)
	{
		azure = NewListener(s->Cedar, LISTENER_REVERSE, 0);
		ReleaseListener(azure);
	}

	// Start a R-UDP listener
	if (s->DisableNatTraversal == false && s->Cedar->Bridge == false)
	{
		rudp = NewListenerEx4(s->Cedar, LISTENER_RUDP, 0, TCPAcceptedThread, NULL, false, false,
			&s->NatTGlobalUdpPort, RAND_PORT_ID_SERVER_LISTEN);
		ReleaseListener(rudp);
	}

	// Start a VPN-over-ICMP listener
	s->DynListenerIcmp = NewDynamicListener(s->Cedar, &s->EnableVpnOverIcmp, LISTENER_ICMP, 0);

	// Start a VPN-over-DNS listener
	s->DynListenerDns = NewDynamicListener(s->Cedar, &s->EnableVpnOverDns, LISTENER_DNS, 53);


	SiInitDeadLockCheck(s);

	SiUpdateCurrentRegion(s->Cedar, "", true);

	return s;
}