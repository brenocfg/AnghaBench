#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ SavePacketLog; scalar_t__ PacketLogSwitchType; scalar_t__ SaveSecurityLog; scalar_t__ SecurityLogSwitchType; int /*<<< orphan*/ * PacketLogConfig; } ;
struct TYPE_10__ {scalar_t__ Type; int EnableSecureNAT; int /*<<< orphan*/  SecureNATOption; int /*<<< orphan*/  AccessList; TYPE_3__* Option; int /*<<< orphan*/  SecurePassword; int /*<<< orphan*/  HashedPassword; TYPE_1__ LogSetting; int /*<<< orphan*/  Name; TYPE_2__* Cedar; } ;
struct TYPE_9__ {scalar_t__ MaxSession; int NoArpPolling; int NoIPv6AddrPolling; int NoIpTable; int NoEnum; int FilterPPPoE; int YieldAfterStorePacket; int NoSpinLockForPacketDelay; scalar_t__ BroadcastStormDetectionThreshold; scalar_t__ MaxLoggedPacketsPerMinute; scalar_t__ FloodingSendQueueBufferQuota; int DoNotSaveHeavySecurityLogs; int DropBroadcastsInPrivacyFilterMode; int DropArpInPrivacyFilterMode; int SuppressClientUpdateNotification; int AssignVLanIdByRadiusAttribute; int DenyAllRadiusLoginWithNoVlanAssign; scalar_t__ ClientMinimumRequiredBuild; int SecureNAT_RandomizeAssignIp; int NoPhysicalIPOnPacketLog; scalar_t__ DetectDormantSessionInterval; int FixForDLinkBPDU; int BroadcastLimiterStrictMode; int NoLookBPDUBridgeId; int NoManageVlanId; scalar_t__ VlanTypeId; int FilterOSPF; int FilterIPv4; int FilterIPv6; int FilterNonIP; int NoIPv4PacketLog; int NoIPv6PacketLog; int FilterBPDU; int NoIPv6DefaultRouterInRAWhenIPv6; int NoMacAddressLog; int ManageOnlyPrivateIP; int ManageOnlyLocalUnicastIPv6; int DisableIPParsing; scalar_t__ AdjustTcpMssValue; int DisableAdjustTcpMss; int NoDhcpPacketLogOutsideHub; int DisableHttpParsing; int DisableUdpAcceleration; int DisableUdpFilterForLocalBridgeNic; int ApplyIPv4AccessListOnArpPacket; int RemoveDefGwOnDhcpForLocalhost; scalar_t__ SecureNAT_MaxTcpSessionsPerIp; scalar_t__ SecureNAT_MaxTcpSynSentPerIp; scalar_t__ SecureNAT_MaxUdpSessionsPerIp; scalar_t__ SecureNAT_MaxDnsSessionsPerIp; scalar_t__ SecureNAT_MaxIcmpSessionsPerIp; scalar_t__ AccessListIncludeFileCacheLifetime; int DisableKernelModeSecureNAT; int DisableIpRawModeSecureNAT; int DisableUserModeSecureNAT; int DisableCheckMacOnLocalBridge; int DisableCorrectIpOffloadChecksum; int UseHubNameAsDhcpUserClassOption; int UseHubNameAsRadiusNasId; } ;
struct TYPE_8__ {int /*<<< orphan*/ * Server; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_4__ HUB ;

/* Variables and functions */
 scalar_t__ GetHubAdminOption (TYPE_4__*,char*) ; 
 scalar_t__ INFINITE ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ NUM_PACKET_LOG ; 
 int /*<<< orphan*/  OutVhOption (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  SiAccessListToPack (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SiPackAddCreateHub(PACK *p, HUB *h)
{
	UINT i;
	UINT max_session;
	SERVER *s;


	// Validate arguments
	if (p == NULL || h == NULL)
	{
		return;
	}


	s = h->Cedar->Server;
	if (s != NULL)
	{
	}

	PackAddStr(p, "HubName", h->Name);
	PackAddInt(p, "HubType", h->Type);

	max_session = h->Option->MaxSession;

	if (GetHubAdminOption(h, "max_sessions") != 0)
	{
		if (max_session == 0)
		{
			max_session = GetHubAdminOption(h, "max_sessions");
		}
		else
		{
			UINT r = GetHubAdminOption(h, "max_sessions");
			max_session = MIN(max_session, r);
		}
	}

	PackAddInt(p, "MaxSession", max_session);

	if (GetHubAdminOption(h, "max_sessions_client_bridge_apply") != 0
		)
	{
		PackAddInt(p, "MaxSessionClient", GetHubAdminOption(h, "max_sessions_client"));
		PackAddInt(p, "MaxSessionBridge", GetHubAdminOption(h, "max_sessions_bridge"));
		PackAddBool(p, "MaxSessionClientBridgeApply", true);
	}
	else
	{
		PackAddInt(p, "MaxSessionClient", INFINITE);
		PackAddInt(p, "MaxSessionBridge", INFINITE);
	}

	PackAddBool(p, "NoArpPolling", h->Option->NoArpPolling);
	PackAddBool(p, "NoIPv6AddrPolling", h->Option->NoIPv6AddrPolling);
	PackAddBool(p, "NoIpTable", h->Option->NoIpTable);
	PackAddBool(p, "NoEnum", h->Option->NoEnum);
	PackAddBool(p, "FilterPPPoE", h->Option->FilterPPPoE);
	PackAddBool(p, "YieldAfterStorePacket", h->Option->YieldAfterStorePacket);
	PackAddBool(p, "NoSpinLockForPacketDelay", h->Option->NoSpinLockForPacketDelay);
	PackAddInt(p, "BroadcastStormDetectionThreshold", h->Option->BroadcastStormDetectionThreshold);
	PackAddInt(p, "MaxLoggedPacketsPerMinute", h->Option->MaxLoggedPacketsPerMinute);
	PackAddInt(p, "FloodingSendQueueBufferQuota", h->Option->FloodingSendQueueBufferQuota);
	PackAddBool(p, "DoNotSaveHeavySecurityLogs", h->Option->DoNotSaveHeavySecurityLogs);
	PackAddBool(p, "DropBroadcastsInPrivacyFilterMode", h->Option->DropBroadcastsInPrivacyFilterMode);
	PackAddBool(p, "DropArpInPrivacyFilterMode", h->Option->DropArpInPrivacyFilterMode);
	PackAddBool(p, "SuppressClientUpdateNotification", h->Option->SuppressClientUpdateNotification);
	PackAddBool(p, "AssignVLanIdByRadiusAttribute", h->Option->AssignVLanIdByRadiusAttribute);
	PackAddBool(p, "DenyAllRadiusLoginWithNoVlanAssign", h->Option->DenyAllRadiusLoginWithNoVlanAssign);
	PackAddInt(p, "ClientMinimumRequiredBuild", h->Option->ClientMinimumRequiredBuild);
	PackAddBool(p, "SecureNAT_RandomizeAssignIp", h->Option->SecureNAT_RandomizeAssignIp);
	PackAddBool(p, "NoPhysicalIPOnPacketLog", h->Option->NoPhysicalIPOnPacketLog);
	PackAddInt(p, "DetectDormantSessionInterval", h->Option->DetectDormantSessionInterval);
	PackAddBool(p, "FixForDLinkBPDU", h->Option->FixForDLinkBPDU);
	PackAddBool(p, "BroadcastLimiterStrictMode", h->Option->BroadcastLimiterStrictMode);
	PackAddBool(p, "NoLookBPDUBridgeId", h->Option->NoLookBPDUBridgeId);
	PackAddBool(p, "NoManageVlanId", h->Option->NoManageVlanId);
	PackAddInt(p, "VlanTypeId", h->Option->VlanTypeId);
	PackAddBool(p, "FilterOSPF", h->Option->FilterOSPF);
	PackAddBool(p, "FilterIPv4", h->Option->FilterIPv4);
	PackAddBool(p, "FilterIPv6", h->Option->FilterIPv6);
	PackAddBool(p, "FilterNonIP", h->Option->FilterNonIP);
	PackAddBool(p, "NoIPv4PacketLog", h->Option->NoIPv4PacketLog);
	PackAddBool(p, "NoIPv6PacketLog", h->Option->NoIPv6PacketLog);
	PackAddBool(p, "FilterBPDU", h->Option->FilterBPDU);
	PackAddBool(p, "NoIPv6DefaultRouterInRAWhenIPv6", h->Option->NoIPv6DefaultRouterInRAWhenIPv6);
	PackAddBool(p, "NoMacAddressLog", h->Option->NoMacAddressLog);
	PackAddBool(p, "ManageOnlyPrivateIP", h->Option->ManageOnlyPrivateIP);
	PackAddBool(p, "ManageOnlyLocalUnicastIPv6", h->Option->ManageOnlyLocalUnicastIPv6);
	PackAddBool(p, "DisableIPParsing", h->Option->DisableIPParsing);
	PackAddInt(p, "AdjustTcpMssValue", h->Option->AdjustTcpMssValue);
	PackAddBool(p, "DisableAdjustTcpMss", h->Option->DisableAdjustTcpMss);
	PackAddBool(p, "NoDhcpPacketLogOutsideHub", h->Option->NoDhcpPacketLogOutsideHub);
	PackAddBool(p, "DisableHttpParsing", h->Option->DisableHttpParsing);
	PackAddBool(p, "DisableUdpAcceleration", h->Option->DisableUdpAcceleration);
	PackAddBool(p, "DisableUdpFilterForLocalBridgeNic", h->Option->DisableUdpFilterForLocalBridgeNic);
	PackAddBool(p, "ApplyIPv4AccessListOnArpPacket", h->Option->ApplyIPv4AccessListOnArpPacket);
	PackAddBool(p, "RemoveDefGwOnDhcpForLocalhost", h->Option->RemoveDefGwOnDhcpForLocalhost);

	PackAddInt(p, "SecureNAT_MaxTcpSessionsPerIp", h->Option->SecureNAT_MaxTcpSessionsPerIp);
	PackAddInt(p, "SecureNAT_MaxTcpSynSentPerIp", h->Option->SecureNAT_MaxTcpSynSentPerIp);
	PackAddInt(p, "SecureNAT_MaxUdpSessionsPerIp", h->Option->SecureNAT_MaxUdpSessionsPerIp);
	PackAddInt(p, "SecureNAT_MaxDnsSessionsPerIp", h->Option->SecureNAT_MaxDnsSessionsPerIp);
	PackAddInt(p, "SecureNAT_MaxIcmpSessionsPerIp", h->Option->SecureNAT_MaxIcmpSessionsPerIp);
	PackAddInt(p, "AccessListIncludeFileCacheLifetime", h->Option->AccessListIncludeFileCacheLifetime);
	PackAddBool(p, "DisableKernelModeSecureNAT", h->Option->DisableKernelModeSecureNAT);
	PackAddBool(p, "DisableIpRawModeSecureNAT", h->Option->DisableIpRawModeSecureNAT);
	PackAddBool(p, "DisableUserModeSecureNAT", h->Option->DisableUserModeSecureNAT);
	PackAddBool(p, "DisableCheckMacOnLocalBridge", h->Option->DisableCheckMacOnLocalBridge);
	PackAddBool(p, "DisableCorrectIpOffloadChecksum", h->Option->DisableCorrectIpOffloadChecksum);

	PackAddInt(p, "SavePacketLog", h->LogSetting.SavePacketLog);
	PackAddInt(p, "PacketLogSwitchType", h->LogSetting.PacketLogSwitchType);
	for (i = 0;i < NUM_PACKET_LOG;i++)
	{
		PackAddIntEx(p, "PacketLogConfig", h->LogSetting.PacketLogConfig[i], i, NUM_PACKET_LOG);
	}
	PackAddInt(p, "SaveSecurityLog", h->LogSetting.SaveSecurityLog);
	PackAddInt(p, "SecurityLogSwitchType", h->LogSetting.SecurityLogSwitchType);
	PackAddData(p, "HashedPassword", h->HashedPassword, SHA1_SIZE);
	PackAddData(p, "SecurePassword", h->SecurePassword, SHA1_SIZE);
	PackAddBool(p, "UseHubNameAsDhcpUserClassOption", h->Option->UseHubNameAsDhcpUserClassOption);
	PackAddBool(p, "UseHubNameAsRadiusNasId", h->Option->UseHubNameAsRadiusNasId);

	SiAccessListToPack(p, h->AccessList);

	if (h->EnableSecureNAT)
	{
		PackAddBool(p, "EnableSecureNAT", h->EnableSecureNAT);
		OutVhOption(p, h->SecureNATOption);
	}
}