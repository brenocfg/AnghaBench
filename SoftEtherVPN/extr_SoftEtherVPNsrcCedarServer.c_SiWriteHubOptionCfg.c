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
struct TYPE_3__ {scalar_t__ UseHubNameAsRadiusNasId; scalar_t__ UseHubNameAsDhcpUserClassOption; scalar_t__ DisableCorrectIpOffloadChecksum; scalar_t__ DisableCheckMacOnLocalBridge; scalar_t__ DisableUserModeSecureNAT; scalar_t__ DisableIpRawModeSecureNAT; scalar_t__ DisableKernelModeSecureNAT; int /*<<< orphan*/  AccessListIncludeFileCacheLifetime; int /*<<< orphan*/  SecureNAT_MaxIcmpSessionsPerIp; int /*<<< orphan*/  SecureNAT_MaxDnsSessionsPerIp; int /*<<< orphan*/  SecureNAT_MaxUdpSessionsPerIp; int /*<<< orphan*/  SecureNAT_MaxTcpSynSentPerIp; int /*<<< orphan*/  SecureNAT_MaxTcpSessionsPerIp; scalar_t__ RemoveDefGwOnDhcpForLocalhost; scalar_t__ ApplyIPv4AccessListOnArpPacket; scalar_t__ DisableUdpFilterForLocalBridgeNic; scalar_t__ DisableUdpAcceleration; scalar_t__ DisableHttpParsing; scalar_t__ NoDhcpPacketLogOutsideHub; scalar_t__ DisableAdjustTcpMss; int /*<<< orphan*/  AdjustTcpMssValue; scalar_t__ NoLookBPDUBridgeId; int /*<<< orphan*/  DetectDormantSessionInterval; scalar_t__ NoPhysicalIPOnPacketLog; scalar_t__ SecureNAT_RandomizeAssignIp; scalar_t__ DenyAllRadiusLoginWithNoVlanAssign; scalar_t__ AssignVLanIdByRadiusAttribute; scalar_t__ SuppressClientUpdateNotification; scalar_t__ DropArpInPrivacyFilterMode; scalar_t__ DropBroadcastsInPrivacyFilterMode; scalar_t__ DoNotSaveHeavySecurityLogs; int /*<<< orphan*/  FloodingSendQueueBufferQuota; int /*<<< orphan*/  MaxLoggedPacketsPerMinute; scalar_t__ BroadcastLimiterStrictMode; scalar_t__ FixForDLinkBPDU; int /*<<< orphan*/  VlanTypeId; scalar_t__ NoManageVlanId; int /*<<< orphan*/  RequiredClientId; int /*<<< orphan*/  ClientMinimumRequiredBuild; int /*<<< orphan*/  BroadcastStormDetectionThreshold; scalar_t__ NoSpinLockForPacketDelay; scalar_t__ YieldAfterStorePacket; scalar_t__ DisableIPParsing; scalar_t__ ManageOnlyLocalUnicastIPv6; scalar_t__ ManageOnlyPrivateIP; scalar_t__ NoMacAddressLog; scalar_t__ NoIPv6DefaultRouterInRAWhenIPv6; scalar_t__ FilterBPDU; scalar_t__ NoIPv6PacketLog; scalar_t__ NoIPv4PacketLog; scalar_t__ FilterNonIP; scalar_t__ FilterIPv6; scalar_t__ FilterIPv4; scalar_t__ FilterOSPF; scalar_t__ FilterPPPoE; scalar_t__ NoEnum; scalar_t__ NoIpTable; scalar_t__ NoIPv6AddrPolling; scalar_t__ NoArpPolling; int /*<<< orphan*/  MaxSession; } ;
typedef  TYPE_1__ HUB_OPTION ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 

void SiWriteHubOptionCfg(FOLDER *f, HUB_OPTION *o)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (f == NULL || o == NULL)
	{
		return;
	}

	CfgAddInt(f, "MaxSession", o->MaxSession);
	CfgAddBool(f, "NoArpPolling", o->NoArpPolling);
	CfgAddBool(f, "NoIPv6AddrPolling", o->NoIPv6AddrPolling);
	CfgAddBool(f, "NoIpTable", o->NoIpTable);
	CfgAddBool(f, "NoEnum", o->NoEnum);
	CfgAddBool(f, "FilterPPPoE", o->FilterPPPoE);
	CfgAddBool(f, "FilterOSPF", o->FilterOSPF);
	CfgAddBool(f, "FilterIPv4", o->FilterIPv4);
	CfgAddBool(f, "FilterIPv6", o->FilterIPv6);
	CfgAddBool(f, "FilterNonIP", o->FilterNonIP);
	CfgAddBool(f, "NoIPv4PacketLog", o->NoIPv4PacketLog);
	CfgAddBool(f, "NoIPv6PacketLog", o->NoIPv6PacketLog);
	CfgAddBool(f, "FilterBPDU", o->FilterBPDU);
	CfgAddBool(f, "NoIPv6DefaultRouterInRAWhenIPv6", o->NoIPv6DefaultRouterInRAWhenIPv6);
	CfgAddBool(f, "NoMacAddressLog", o->NoMacAddressLog);
	CfgAddBool(f, "ManageOnlyPrivateIP", o->ManageOnlyPrivateIP);
	CfgAddBool(f, "ManageOnlyLocalUnicastIPv6", o->ManageOnlyLocalUnicastIPv6);
	CfgAddBool(f, "DisableIPParsing", o->DisableIPParsing);
	CfgAddBool(f, "YieldAfterStorePacket", o->YieldAfterStorePacket);
	CfgAddBool(f, "NoSpinLockForPacketDelay", o->NoSpinLockForPacketDelay);
	CfgAddInt(f, "BroadcastStormDetectionThreshold", o->BroadcastStormDetectionThreshold);
	CfgAddInt(f, "ClientMinimumRequiredBuild", o->ClientMinimumRequiredBuild);
	CfgAddInt(f, "RequiredClientId", o->RequiredClientId);
	CfgAddBool(f, "NoManageVlanId", o->NoManageVlanId);
	Format(tmp, sizeof(tmp), "0x%x", o->VlanTypeId);
	CfgAddStr(f, "VlanTypeId", tmp);
	if (o->FixForDLinkBPDU)
	{
		CfgAddBool(f, "FixForDLinkBPDU", o->FixForDLinkBPDU);
	}
	CfgAddBool(f, "BroadcastLimiterStrictMode", o->BroadcastLimiterStrictMode);
	CfgAddInt(f, "MaxLoggedPacketsPerMinute", o->MaxLoggedPacketsPerMinute);
	CfgAddInt(f, "FloodingSendQueueBufferQuota", o->FloodingSendQueueBufferQuota);
	CfgAddBool(f, "DoNotSaveHeavySecurityLogs", o->DoNotSaveHeavySecurityLogs);
	CfgAddBool(f, "DropBroadcastsInPrivacyFilterMode", o->DropBroadcastsInPrivacyFilterMode);
	CfgAddBool(f, "DropArpInPrivacyFilterMode", o->DropArpInPrivacyFilterMode);
	CfgAddBool(f, "SuppressClientUpdateNotification", o->SuppressClientUpdateNotification);
	CfgAddBool(f, "AssignVLanIdByRadiusAttribute", o->AssignVLanIdByRadiusAttribute);
	CfgAddBool(f, "DenyAllRadiusLoginWithNoVlanAssign", o->DenyAllRadiusLoginWithNoVlanAssign);
	CfgAddBool(f, "SecureNAT_RandomizeAssignIp", o->SecureNAT_RandomizeAssignIp);
	CfgAddBool(f, "NoPhysicalIPOnPacketLog", o->NoPhysicalIPOnPacketLog);
	CfgAddInt(f, "DetectDormantSessionInterval", o->DetectDormantSessionInterval);
	CfgAddBool(f, "NoLookBPDUBridgeId", o->NoLookBPDUBridgeId);
	CfgAddInt(f, "AdjustTcpMssValue", o->AdjustTcpMssValue);
	CfgAddBool(f, "DisableAdjustTcpMss", o->DisableAdjustTcpMss);
	CfgAddBool(f, "NoDhcpPacketLogOutsideHub", o->NoDhcpPacketLogOutsideHub);
	CfgAddBool(f, "DisableHttpParsing", o->DisableHttpParsing);
	CfgAddBool(f, "DisableUdpAcceleration", o->DisableUdpAcceleration);
	CfgAddBool(f, "DisableUdpFilterForLocalBridgeNic", o->DisableUdpFilterForLocalBridgeNic);
	CfgAddBool(f, "ApplyIPv4AccessListOnArpPacket", o->ApplyIPv4AccessListOnArpPacket);
	CfgAddBool(f, "RemoveDefGwOnDhcpForLocalhost", o->RemoveDefGwOnDhcpForLocalhost);
	CfgAddInt(f, "SecureNAT_MaxTcpSessionsPerIp", o->SecureNAT_MaxTcpSessionsPerIp);
	CfgAddInt(f, "SecureNAT_MaxTcpSynSentPerIp", o->SecureNAT_MaxTcpSynSentPerIp);
	CfgAddInt(f, "SecureNAT_MaxUdpSessionsPerIp", o->SecureNAT_MaxUdpSessionsPerIp);
	CfgAddInt(f, "SecureNAT_MaxDnsSessionsPerIp", o->SecureNAT_MaxDnsSessionsPerIp);
	CfgAddInt(f, "SecureNAT_MaxIcmpSessionsPerIp", o->SecureNAT_MaxIcmpSessionsPerIp);
	CfgAddInt(f, "AccessListIncludeFileCacheLifetime", o->AccessListIncludeFileCacheLifetime);
	CfgAddBool(f, "DisableKernelModeSecureNAT", o->DisableKernelModeSecureNAT);
	CfgAddBool(f, "DisableIpRawModeSecureNAT", o->DisableIpRawModeSecureNAT);
	CfgAddBool(f, "DisableUserModeSecureNAT", o->DisableUserModeSecureNAT);
	CfgAddBool(f, "DisableCheckMacOnLocalBridge", o->DisableCheckMacOnLocalBridge);
	CfgAddBool(f, "DisableCorrectIpOffloadChecksum", o->DisableCorrectIpOffloadChecksum);
	CfgAddBool(f, "UseHubNameAsDhcpUserClassOption", o->UseHubNameAsDhcpUserClassOption);
	CfgAddBool(f, "UseHubNameAsRadiusNasId", o->UseHubNameAsRadiusNasId);
}