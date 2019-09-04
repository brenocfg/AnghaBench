#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  safe_hub_name ;
typedef  int /*<<< orphan*/  packet_logger_name ;
typedef  int /*<<< orphan*/  VH_OPTION ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_17__ {scalar_t__ Bridge; TYPE_2__* Server; int /*<<< orphan*/  ref; } ;
struct TYPE_14__ {int SavePacketLog; int SaveSecurityLog; void* SecurityLogSwitchType; void* PacketLogSwitchType; int /*<<< orphan*/ * PacketLogConfig; } ;
struct TYPE_16__ {int EnableSecureNAT; int FarmMember; int WatchDogStarted; int /*<<< orphan*/  Name; TYPE_4__* Cedar; int /*<<< orphan*/  HubMacAddr; TYPE_11__* Option; TYPE_1__ LogSetting; void* SecurityLogger; void* PacketLogger; int /*<<< orphan*/  UserList; void* TicketList; int /*<<< orphan*/  RadiusServerPort; void* RadiusOptionLock; int /*<<< orphan*/  HubIpV6; int /*<<< orphan*/  HubIp; void* SecureNATOption; int /*<<< orphan*/ * SecureNAT; int /*<<< orphan*/  HubSignature; void* OldTraffic; void* Traffic; void* LinkList; void* MonitorList; void* IpTable; int /*<<< orphan*/  MacHashTable; void* NumSessionsBridge; void* NumSessionsClient; void* NumSessions; void* SessionCounter; void* SessionList; int /*<<< orphan*/  HubDb; void* TrafficLock; scalar_t__ NumLogin; void* LastLoginTime; void* LastCommTime; void* AdminOptionList; int /*<<< orphan*/  Type; int /*<<< orphan*/  ref; void* lock_online; void* lock; int /*<<< orphan*/  SecurePassword; int /*<<< orphan*/  HashedPassword; } ;
struct TYPE_15__ {scalar_t__ ServerType; } ;
struct TYPE_13__ {scalar_t__ VlanTypeId; int DropBroadcastsInPrivacyFilterMode; int DropArpInPrivacyFilterMode; int NoArpPolling; int NoIpTable; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  HUB_OPTION ;
typedef  TYPE_3__ HUB ;
typedef  TYPE_4__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  ADMINISTRATOR_USERNAME ; 
 int /*<<< orphan*/  AddHubAdminOptionsDefaults (TYPE_3__*,int) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CompareAdminOption ; 
 int /*<<< orphan*/ * CompareIpTable ; 
 int /*<<< orphan*/  CompareMacTable ; 
 int /*<<< orphan*/  ConvertSafeFileName (char*,int,char*) ; 
 int /*<<< orphan*/  Copy (TYPE_11__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  Format (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GenHubIpAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GenHubMacAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GenerateEui64LocalAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GenerateMachineUniqueHash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetHashOfMacTable ; 
 int /*<<< orphan*/  HUB_PACKET_LOG_DIR_NAME ; 
 int /*<<< orphan*/  HUB_PACKET_LOG_FILE_NAME ; 
 int /*<<< orphan*/  HUB_PACKET_LOG_PREFIX ; 
 int /*<<< orphan*/  HUB_SECURITY_LOG_DIR_NAME ; 
 int /*<<< orphan*/  HUB_SECURITY_LOG_FILE_NAME ; 
 int /*<<< orphan*/  HUB_SECURITY_LOG_PREFIX ; 
 int /*<<< orphan*/  HUB_TYPE_STANDALONE ; 
 int /*<<< orphan*/  HashPassword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IPToIPv6Addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitAccessList (TYPE_3__*) ; 
 void* LOG_SWITCH_DAY ; 
 scalar_t__ MAC_PROTO_TAGVLAN ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MacToStr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeDir (int /*<<< orphan*/ ) ; 
 void* NewCounter () ; 
 int /*<<< orphan*/  NewHashList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  NewHubDb () ; 
 void* NewList (int /*<<< orphan*/ *) ; 
 void* NewLock () ; 
 void* NewLog (char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  NewRef () ; 
 void* NewTraffic () ; 
 int /*<<< orphan*/  NewUserList () ; 
 int /*<<< orphan*/  NiClearUnsupportedVhOptionForDynamicHub (void*,int) ; 
 int /*<<< orphan*/  NiSetDefaultVhOption (int /*<<< orphan*/ *,void*) ; 
 size_t PACKET_LOG_DHCP ; 
 int /*<<< orphan*/  PACKET_LOG_HEADER ; 
 size_t PACKET_LOG_TCP_CONN ; 
 int /*<<< orphan*/  RADIUS_DEFAULT_PORT ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SLog (TYPE_4__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  SetHubOnline (TYPE_3__*) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartHubWatchDog (TYPE_3__*) ; 
 void* SystemTime64 () ; 
 void* ZeroMalloc (int) ; 

HUB *NewHub(CEDAR *cedar, char *HubName, HUB_OPTION *option)
{
	HUB *h;
	char packet_logger_name[MAX_SIZE];
	char tmp[MAX_SIZE];
	char safe_hub_name[MAX_HUBNAME_LEN + 1];
	UCHAR hash[SHA1_SIZE];
	IP ip6;
	// Validate arguments
	if (cedar == NULL || option == NULL || HubName == NULL)
	{
		return NULL;
	}

	h = ZeroMalloc(sizeof(HUB));
	Sha0(h->HashedPassword, "", 0);
	HashPassword(h->SecurePassword, ADMINISTRATOR_USERNAME, "");
	h->lock = NewLock();
	h->lock_online = NewLock();
	h->ref = NewRef();
	h->Cedar = cedar;
	AddRef(h->Cedar->ref);
	h->Type = HUB_TYPE_STANDALONE;

	ConvertSafeFileName(safe_hub_name, sizeof(safe_hub_name), HubName);
	h->Name = CopyStr(safe_hub_name);


	h->AdminOptionList = NewList(CompareAdminOption);
	AddHubAdminOptionsDefaults(h, true);

	h->LastCommTime = SystemTime64();
	h->LastLoginTime = SystemTime64();
	h->NumLogin = 0;

	h->TrafficLock = NewLock();

	h->HubDb = NewHubDb();

	h->SessionList = NewList(NULL);
	h->SessionCounter = NewCounter();
	h->NumSessions = NewCounter();
	h->NumSessionsClient = NewCounter();
	h->NumSessionsBridge = NewCounter();
	h->MacHashTable = NewHashList(GetHashOfMacTable, CompareMacTable, 8, false);
	h->IpTable = NewList(CompareIpTable);
	h->MonitorList = NewList(NULL);
	h->LinkList = NewList(NULL);

	h->Traffic = NewTraffic();
	h->OldTraffic = NewTraffic();

	h->Option = ZeroMalloc(sizeof(HUB_OPTION));
	Copy(h->Option, option, sizeof(HUB_OPTION));

	if (h->Option->VlanTypeId == 0)
	{
		h->Option->VlanTypeId = MAC_PROTO_TAGVLAN;
	}

	h->Option->DropBroadcastsInPrivacyFilterMode = true;
	h->Option->DropArpInPrivacyFilterMode = true;

	Rand(h->HubSignature, sizeof(h->HubSignature));

	// SecureNAT related
	h->EnableSecureNAT = false;
	h->SecureNAT = NULL;
	h->SecureNATOption = ZeroMalloc(sizeof(VH_OPTION));
	NiSetDefaultVhOption(NULL, h->SecureNATOption);

	if (h->Cedar != NULL && h->Cedar->Server != NULL && h->Cedar->Server->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		NiClearUnsupportedVhOptionForDynamicHub(h->SecureNATOption, true);
	}

	// Generate a temporary MAC address for the HUB
	GenerateMachineUniqueHash(hash);
	GenHubMacAddress(h->HubMacAddr, h->Name);
	GenHubIpAddress(&h->HubIp, h->Name);

	// IPv6 address for the HUB
	GenerateEui64LocalAddress(&ip6, h->HubMacAddr);
	IPToIPv6Addr(&h->HubIpV6, &ip6);

	h->RadiusOptionLock = NewLock();
	h->RadiusServerPort = RADIUS_DEFAULT_PORT;

	h->TicketList = NewList(NULL);

	InitAccessList(h);

	// Create a user list
	h->UserList = NewUserList();

	// Default logging settings
	h->LogSetting.SavePacketLog = h->LogSetting.SaveSecurityLog = true;
	h->LogSetting.PacketLogConfig[PACKET_LOG_TCP_CONN] =
		h->LogSetting.PacketLogConfig[PACKET_LOG_DHCP] = PACKET_LOG_HEADER;
	h->LogSetting.SecurityLogSwitchType = LOG_SWITCH_DAY;
	h->LogSetting.PacketLogSwitchType = LOG_SWITCH_DAY;

	MakeDir(HUB_SECURITY_LOG_DIR_NAME);
	MakeDir(HUB_PACKET_LOG_DIR_NAME);

	// Start the packet logger
	Format(packet_logger_name, sizeof(packet_logger_name), HUB_PACKET_LOG_FILE_NAME, h->Name);
	h->PacketLogger = NewLog(packet_logger_name, HUB_PACKET_LOG_PREFIX, h->LogSetting.PacketLogSwitchType);

	// Start the security logger
	Format(tmp, sizeof(tmp), HUB_SECURITY_LOG_FILE_NAME, h->Name);
	h->SecurityLogger = NewLog(tmp, HUB_SECURITY_LOG_PREFIX, h->LogSetting.SecurityLogSwitchType);

	if (h->Cedar->Server != NULL && h->Cedar->Server->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		h->FarmMember = true;
	}

	// Start the HUB
	SetHubOnline(h);

	if (h->Cedar->Bridge)
	{
		h->Option->NoArpPolling = true;
	}

	if (h->Option->NoArpPolling == false && h->Option->NoIpTable == false)
	{
		StartHubWatchDog(h);
		h->WatchDogStarted = true;
	}

	SLog(h->Cedar, "LS_HUB_START", h->Name);

	MacToStr(tmp, sizeof(tmp), h->HubMacAddr);
	SLog(h->Cedar, "LS_HUB_MAC", h->Name, tmp);

	return h;
}