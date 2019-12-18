#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int DropBroadcastsInPrivacyFilterMode; int DropArpInPrivacyFilterMode; int NoDhcpPacketLogOutsideHub; int RemoveDefGwOnDhcpForLocalhost; scalar_t__ AccessListIncludeFileCacheLifetime; int ManageOnlyPrivateIP; int ManageOnlyLocalUnicastIPv6; int NoMacAddressLog; void* UseHubNameAsRadiusNasId; void* UseHubNameAsDhcpUserClassOption; void* NoPhysicalIPOnPacketLog; void* DetectDormantSessionInterval; void* SecureNAT_RandomizeAssignIp; void* DenyAllRadiusLoginWithNoVlanAssign; void* AssignVLanIdByRadiusAttribute; void* SuppressClientUpdateNotification; void* DisableCorrectIpOffloadChecksum; void* DisableCheckMacOnLocalBridge; void* DisableUserModeSecureNAT; void* DisableIpRawModeSecureNAT; void* DisableKernelModeSecureNAT; void* SecureNAT_MaxIcmpSessionsPerIp; void* SecureNAT_MaxDnsSessionsPerIp; void* SecureNAT_MaxUdpSessionsPerIp; void* SecureNAT_MaxTcpSynSentPerIp; void* SecureNAT_MaxTcpSessionsPerIp; void* ApplyIPv4AccessListOnArpPacket; void* DisableUdpFilterForLocalBridgeNic; void* DisableUdpAcceleration; void* DisableHttpParsing; void* DisableAdjustTcpMss; void* AdjustTcpMssValue; void* NoLookBPDUBridgeId; void* DoNotSaveHeavySecurityLogs; void* FloodingSendQueueBufferQuota; void* MaxLoggedPacketsPerMinute; void* BroadcastLimiterStrictMode; void* FixForDLinkBPDU; int /*<<< orphan*/  VlanTypeId; void* NoManageVlanId; void* RequiredClientId; void* ClientMinimumRequiredBuild; void* BroadcastStormDetectionThreshold; void* NoSpinLockForPacketDelay; void* YieldAfterStorePacket; void* DisableIPParsing; void* NoIPv6DefaultRouterInRAWhenIPv6; void* NoIPv6PacketLog; void* NoIPv4PacketLog; void* FilterBPDU; void* FilterNonIP; void* FilterIPv6; void* FilterIPv4; void* FilterOSPF; void* FilterPPPoE; void* NoEnum; void* NoIpTable; void* NoIPv6AddrPolling; void* NoArpPolling; void* MaxSession; } ;
typedef  TYPE_1__ HUB_OPTION ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 scalar_t__ ACCESS_LIST_INCLUDE_FILE_CACHE_LIFETIME ; 
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ CfgIsItem (int /*<<< orphan*/ *,char*) ; 
 void* DEFAULT_FLOODING_QUEUE_LENGTH ; 
 int /*<<< orphan*/  HexToInt (char*) ; 
 int /*<<< orphan*/  MAC_PROTO_TAGVLAN ; 
 int MAX_SIZE ; 

void SiLoadHubOptionCfg(FOLDER *f, HUB_OPTION *o)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (f == NULL || o == NULL)
	{
		return;
	}

	o->MaxSession = CfgGetInt(f, "MaxSession");
	o->NoArpPolling = CfgGetBool(f, "NoArpPolling");
	o->NoIPv6AddrPolling = CfgGetBool(f, "NoIPv6AddrPolling");
	o->NoIpTable = CfgGetBool(f, "NoIpTable");
	o->NoEnum = CfgGetBool(f, "NoEnum");
	o->FilterPPPoE = CfgGetBool(f, "FilterPPPoE");
	o->FilterOSPF = CfgGetBool(f, "FilterOSPF");
	o->FilterIPv4 = CfgGetBool(f, "FilterIPv4");
	o->FilterIPv6 = CfgGetBool(f, "FilterIPv6");
	o->FilterNonIP = CfgGetBool(f, "FilterNonIP");
	o->FilterBPDU = CfgGetBool(f, "FilterBPDU");
	o->NoIPv4PacketLog = CfgGetBool(f, "NoIPv4PacketLog");
	o->NoIPv6PacketLog = CfgGetBool(f, "NoIPv6PacketLog");
	o->NoIPv6DefaultRouterInRAWhenIPv6 = CfgGetBool(f, "NoIPv6DefaultRouterInRAWhenIPv6");
	o->DisableIPParsing = CfgGetBool(f, "DisableIPParsing");
	o->YieldAfterStorePacket = CfgGetBool(f, "YieldAfterStorePacket");
	o->NoSpinLockForPacketDelay = CfgGetBool(f, "NoSpinLockForPacketDelay");
	o->BroadcastStormDetectionThreshold = CfgGetInt(f, "BroadcastStormDetectionThreshold");
	o->ClientMinimumRequiredBuild = CfgGetInt(f, "ClientMinimumRequiredBuild");
	o->RequiredClientId = CfgGetInt(f, "RequiredClientId");
	o->NoManageVlanId = CfgGetBool(f, "NoManageVlanId");
	o->VlanTypeId = 0;
	if (CfgGetStr(f, "VlanTypeId", tmp, sizeof(tmp)))
	{
		o->VlanTypeId = HexToInt(tmp);
	}
	if (o->VlanTypeId == 0)
	{
		o->VlanTypeId = MAC_PROTO_TAGVLAN;
	}
	o->FixForDLinkBPDU = CfgGetBool(f, "FixForDLinkBPDU");
	o->BroadcastLimiterStrictMode = CfgGetBool(f, "BroadcastLimiterStrictMode");
	o->MaxLoggedPacketsPerMinute = CfgGetInt(f, "MaxLoggedPacketsPerMinute");
	if (CfgIsItem(f, "FloodingSendQueueBufferQuota"))
	{
		o->FloodingSendQueueBufferQuota = CfgGetInt(f, "FloodingSendQueueBufferQuota");
	}
	else
	{
		o->FloodingSendQueueBufferQuota = DEFAULT_FLOODING_QUEUE_LENGTH;
	}
	o->DoNotSaveHeavySecurityLogs = CfgGetBool(f, "DoNotSaveHeavySecurityLogs");

	if (CfgIsItem(f, "DropBroadcastsInPrivacyFilterMode"))
	{
		o->DropBroadcastsInPrivacyFilterMode = CfgGetBool(f, "DropBroadcastsInPrivacyFilterMode");
	}
	else
	{
		o->DropBroadcastsInPrivacyFilterMode = true;
	}

	if (CfgIsItem(f, "DropArpInPrivacyFilterMode"))
	{
		o->DropArpInPrivacyFilterMode = CfgGetBool(f, "DropArpInPrivacyFilterMode");
	}
	else
	{
		o->DropArpInPrivacyFilterMode = true;
	}

	o->NoLookBPDUBridgeId = CfgGetBool(f, "NoLookBPDUBridgeId");
	o->AdjustTcpMssValue = CfgGetInt(f, "AdjustTcpMssValue");
	o->DisableAdjustTcpMss = CfgGetBool(f, "DisableAdjustTcpMss");
	if (CfgIsItem(f, "NoDhcpPacketLogOutsideHub"))
	{
		o->NoDhcpPacketLogOutsideHub = CfgGetBool(f, "NoDhcpPacketLogOutsideHub");
	}
	else
	{
		o->NoDhcpPacketLogOutsideHub = true;
	}
	o->DisableHttpParsing = CfgGetBool(f, "DisableHttpParsing");
	o->DisableUdpAcceleration = CfgGetBool(f, "DisableUdpAcceleration");
	o->DisableUdpFilterForLocalBridgeNic = CfgGetBool(f, "DisableUdpFilterForLocalBridgeNic");
	o->ApplyIPv4AccessListOnArpPacket = CfgGetBool(f, "ApplyIPv4AccessListOnArpPacket");
	if (CfgIsItem(f, "RemoveDefGwOnDhcpForLocalhost"))
	{
		o->RemoveDefGwOnDhcpForLocalhost = CfgGetBool(f, "RemoveDefGwOnDhcpForLocalhost");
	}
	else
	{
		o->RemoveDefGwOnDhcpForLocalhost = true;
	}
	o->SecureNAT_MaxTcpSessionsPerIp = CfgGetInt(f, "SecureNAT_MaxTcpSessionsPerIp");
	o->SecureNAT_MaxTcpSynSentPerIp = CfgGetInt(f, "SecureNAT_MaxTcpSynSentPerIp");
	o->SecureNAT_MaxUdpSessionsPerIp = CfgGetInt(f, "SecureNAT_MaxUdpSessionsPerIp");
	o->SecureNAT_MaxDnsSessionsPerIp = CfgGetInt(f, "SecureNAT_MaxDnsSessionsPerIp");
	o->SecureNAT_MaxIcmpSessionsPerIp = CfgGetInt(f, "SecureNAT_MaxIcmpSessionsPerIp");
	o->AccessListIncludeFileCacheLifetime = CfgGetInt(f, "AccessListIncludeFileCacheLifetime");

	if (o->AccessListIncludeFileCacheLifetime == 0)
	{
		o->AccessListIncludeFileCacheLifetime = ACCESS_LIST_INCLUDE_FILE_CACHE_LIFETIME;
	}

	o->DisableKernelModeSecureNAT = CfgGetBool(f, "DisableKernelModeSecureNAT");
	o->DisableIpRawModeSecureNAT = CfgGetBool(f, "DisableIpRawModeSecureNAT");
	o->DisableUserModeSecureNAT = CfgGetBool(f, "DisableUserModeSecureNAT");
	o->DisableCheckMacOnLocalBridge = CfgGetBool(f, "DisableCheckMacOnLocalBridge");
	o->DisableCorrectIpOffloadChecksum = CfgGetBool(f, "DisableCorrectIpOffloadChecksum");
	o->SuppressClientUpdateNotification = CfgGetBool(f, "SuppressClientUpdateNotification");
	o->AssignVLanIdByRadiusAttribute = CfgGetBool(f, "AssignVLanIdByRadiusAttribute");
	o->DenyAllRadiusLoginWithNoVlanAssign = CfgGetBool(f, "DenyAllRadiusLoginWithNoVlanAssign");
	o->SecureNAT_RandomizeAssignIp = CfgGetBool(f, "SecureNAT_RandomizeAssignIp");
	o->DetectDormantSessionInterval = CfgGetInt(f, "DetectDormantSessionInterval");
	o->NoPhysicalIPOnPacketLog = CfgGetBool(f, "NoPhysicalIPOnPacketLog");
	o->UseHubNameAsDhcpUserClassOption = CfgGetBool(f, "UseHubNameAsDhcpUserClassOption");
	o->UseHubNameAsRadiusNasId = CfgGetBool(f, "UseHubNameAsRadiusNasId");

	// Enabled by default
	if (CfgIsItem(f, "ManageOnlyPrivateIP"))
	{
		o->ManageOnlyPrivateIP = CfgGetBool(f, "ManageOnlyPrivateIP");
	}
	else
	{
		o->ManageOnlyPrivateIP = true;
	}
	if (CfgIsItem(f, "ManageOnlyLocalUnicastIPv6"))
	{
		o->ManageOnlyLocalUnicastIPv6 = CfgGetBool(f, "ManageOnlyLocalUnicastIPv6");
	}
	else
	{
		o->ManageOnlyLocalUnicastIPv6 = true;
	}
	if (CfgIsItem(f, "NoMacAddressLog"))
	{
		o->NoMacAddressLog = CfgGetBool(f, "NoMacAddressLog");
	}
	else
	{
		o->NoMacAddressLog = true;
	}
}