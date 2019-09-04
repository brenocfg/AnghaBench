#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* Session; } ;
typedef  TYPE_1__ VH ;
struct TYPE_19__ {scalar_t__ AuthType; int RetryInterval; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  UseCompress; int /*<<< orphan*/  UseEncrypt; int /*<<< orphan*/  MaxConnection; int /*<<< orphan*/ * SecureSignProc; } ;
struct TYPE_18__ {scalar_t__ Id; scalar_t__ Param; } ;
struct TYPE_17__ {int ServerMode; int RetryInterval; int ClientModeAndUseVLan; int IsVPNClientAndVLAN_Win32; int VirtualHost; int LinkModeClient; int SecureNATMode; int BridgeMode; int* NicDownOnDisconnect; TYPE_12__* ClientOption; TYPE_12__* ClientAuth; int /*<<< orphan*/ * Account; int /*<<< orphan*/  ref; TYPE_3__* PacketAdapter; int /*<<< orphan*/ * Link; int /*<<< orphan*/  UseCompress; int /*<<< orphan*/  UseEncrypt; int /*<<< orphan*/  MaxConnection; int /*<<< orphan*/  CancelList; int /*<<< orphan*/  Cancel1; void* OldTraffic; void* TrafficLock; int /*<<< orphan*/  HaltEvent; void* Traffic; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  Name; int /*<<< orphan*/ * Cedar; void* lock; int /*<<< orphan*/  LoggingRecordCount; } ;
struct TYPE_15__ {int DisableQoS; int MaxConnection; int HalfConnection; scalar_t__ AuthType; scalar_t__ NumRetry; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/ * ClientK; int /*<<< orphan*/ * ClientX; scalar_t__ NoRoutingTracking; int /*<<< orphan*/  AdditionalConnectionInterval; } ;
struct TYPE_14__ {int /*<<< orphan*/  OsType; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ PACKET_ADAPTER ;
typedef  int /*<<< orphan*/  LINK ;
typedef  TYPE_4__ CLIENT_OPTION ;
typedef  TYPE_4__ CLIENT_AUTH ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  int /*<<< orphan*/  ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRIDGE_DEVICE_NAME ; 
 scalar_t__ CLIENT_AUTHTYPE_SECURE ; 
 int /*<<< orphan*/  ClientThread ; 
 int /*<<< orphan*/ * CloneK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CloneX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (TYPE_12__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  GSF_DISABLE_SESSION_RECONNECT ; 
 scalar_t__ GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 TYPE_11__* GetOsInfo () ; 
 int /*<<< orphan*/  LINK_DEVICE_NAME ; 
 int MAKESURE (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int) ; 
 int MAX_RETRY_INTERVAL ; 
 int /*<<< orphan*/  MIN_RETRY_INTERVAL ; 
 void* Malloc (int) ; 
 int /*<<< orphan*/  NewCancel () ; 
 int /*<<< orphan*/  NewCancelList () ; 
 int /*<<< orphan*/  NewCounter () ; 
 int /*<<< orphan*/  NewEvent () ; 
 void* NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,void*) ; 
 void* NewTraffic () ; 
 scalar_t__ OS_IS_WINDOWS_9X (int /*<<< orphan*/ ) ; 
 scalar_t__ PACKET_ADAPTER_ID_VLAN_WIN32 ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SNAT_DEVICE_NAME ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ StrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_2__* ZeroMalloc (int) ; 

SESSION *NewClientSessionEx(CEDAR *cedar, CLIENT_OPTION *option, CLIENT_AUTH *auth, PACKET_ADAPTER *pa, ACCOUNT *account, bool *NicDownOnDisconnect)
{
	SESSION *s;
	THREAD *t;
	// Validate arguments
	if (cedar == NULL || option == NULL || auth == NULL || pa == NULL ||
		(auth->AuthType == CLIENT_AUTHTYPE_SECURE && auth->SecureSignProc == NULL))
	{
		return NULL;
	}

	// Initialize the SESSION object
	s = ZeroMalloc(sizeof(SESSION));

	s->LoggingRecordCount = NewCounter();

	s->lock = NewLock();
	s->ref = NewRef();
	s->Cedar = cedar;
	s->ServerMode = false;
	s->Name = CopyStr("CLIENT_SESSION");
	s->CreatedTime = s->LastCommTime = Tick64();
	s->Traffic = NewTraffic();
	s->HaltEvent = NewEvent();
	s->PacketAdapter = pa;
	s->TrafficLock = NewLock();
	s->OldTraffic = NewTraffic();
	s->Cancel1 = NewCancel();
	s->CancelList = NewCancelList();

	// Copy the client connection options
	s->ClientOption = Malloc(sizeof(CLIENT_OPTION));
	Copy(s->ClientOption, option, sizeof(CLIENT_OPTION));

	if (GetGlobalServerFlag(GSF_DISABLE_SESSION_RECONNECT))
	{
		s->ClientOption->DisableQoS = true;
		s->ClientOption->MaxConnection = 1;
		s->ClientOption->HalfConnection = false;
	}

	s->MaxConnection = option->MaxConnection;
	s->UseEncrypt = option->UseEncrypt;
	s->UseCompress = option->UseCompress;

	// Set the retry interval
	s->RetryInterval = MAKESURE(option->RetryInterval, 0, 4000000) * 1000;
	s->RetryInterval = MAKESURE(s->RetryInterval, MIN_RETRY_INTERVAL, MAX_RETRY_INTERVAL);

	// Interval for additional connection creation is at least 1 second
	s->ClientOption->AdditionalConnectionInterval = MAX(s->ClientOption->AdditionalConnectionInterval, 1);

	// Hold whether the virtual LAN card is used in client mode
	s->ClientModeAndUseVLan = (StrLen(s->ClientOption->DeviceName) == 0) ? false : true;

	if (s->ClientOption->NoRoutingTracking)
	{
		s->ClientModeAndUseVLan = false;
	}

	if (pa->Id == PACKET_ADAPTER_ID_VLAN_WIN32)
	{
		s->IsVPNClientAndVLAN_Win32 = true;
	}

	if (StrLen(option->DeviceName) == 0)
	{
		// NAT mode
		s->ClientModeAndUseVLan = false;
		s->VirtualHost = true;
	}

	if (OS_IS_WINDOWS_9X(GetOsInfo()->OsType))
	{
		// Prohibit the half-duplex mode in the case of Win9x
		s->ClientOption->HalfConnection = false;
	}

	// Copy the client authentication data
	s->ClientAuth = Malloc(sizeof(CLIENT_AUTH));
	Copy(s->ClientAuth, auth, sizeof(CLIENT_AUTH));

	// Clone the certificate and the private key
	if (s->ClientAuth->ClientX != NULL)
	{
		s->ClientAuth->ClientX = CloneX(s->ClientAuth->ClientX);
	}
	if (s->ClientAuth->ClientK != NULL)
	{
		s->ClientAuth->ClientK = CloneK(s->ClientAuth->ClientK);
	}

	if (StrCmpi(s->ClientOption->DeviceName, LINK_DEVICE_NAME) == 0)
	{
		// Link client mode
		s->LinkModeClient = true;
		s->Link = (LINK *)s->PacketAdapter->Param;
	}

	if (StrCmpi(s->ClientOption->DeviceName, SNAT_DEVICE_NAME) == 0)
	{
		// SecureNAT mode
		s->SecureNATMode = true;
	}

	if (StrCmpi(s->ClientOption->DeviceName, BRIDGE_DEVICE_NAME) == 0)
	{
		// Bridge mode
		s->BridgeMode = true;
	}

	if (s->VirtualHost)
	{
		VH *v = (VH *)s->PacketAdapter->Param;

		// Add the session object to VH
		v->Session = s;
		AddRef(s->ref);
	}

	s->Account = account;

	if (s->ClientAuth->AuthType == CLIENT_AUTHTYPE_SECURE)
	{
		// Do not retry in the case of a smart card authentication
		s->ClientOption->NumRetry = 0;
	}

	s->NicDownOnDisconnect = NicDownOnDisconnect;

	// Create a client thread
	t = NewThread(ClientThread, (void *)s);
	WaitThreadInit(t);
	ReleaseThread(t);

	return s;
}