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
struct TYPE_3__ {int /*<<< orphan*/  UseHubNameAsRadiusNasId; int /*<<< orphan*/  UseHubNameAsDhcpUserClassOption; int /*<<< orphan*/  NoPhysicalIPOnPacketLog; int /*<<< orphan*/  DetectDormantSessionInterval; int /*<<< orphan*/  SecureNAT_RandomizeAssignIp; int /*<<< orphan*/  DenyAllRadiusLoginWithNoVlanAssign; int /*<<< orphan*/  AssignVLanIdByRadiusAttribute; int /*<<< orphan*/  FloodingSendQueueBufferQuota; int /*<<< orphan*/  SuppressClientUpdateNotification; int /*<<< orphan*/  DropArpInPrivacyFilterMode; int /*<<< orphan*/  DropBroadcastsInPrivacyFilterMode; int /*<<< orphan*/  DoNotSaveHeavySecurityLogs; int /*<<< orphan*/  MaxLoggedPacketsPerMinute; int /*<<< orphan*/  BroadcastLimiterStrictMode; int /*<<< orphan*/  DisableCorrectIpOffloadChecksum; int /*<<< orphan*/  DisableCheckMacOnLocalBridge; int /*<<< orphan*/  DisableUserModeSecureNAT; int /*<<< orphan*/  DisableIpRawModeSecureNAT; int /*<<< orphan*/  DisableKernelModeSecureNAT; int /*<<< orphan*/  AccessListIncludeFileCacheLifetime; int /*<<< orphan*/  SecureNAT_MaxIcmpSessionsPerIp; int /*<<< orphan*/  SecureNAT_MaxDnsSessionsPerIp; int /*<<< orphan*/  SecureNAT_MaxUdpSessionsPerIp; int /*<<< orphan*/  SecureNAT_MaxTcpSynSentPerIp; int /*<<< orphan*/  SecureNAT_MaxTcpSessionsPerIp; int /*<<< orphan*/  RemoveDefGwOnDhcpForLocalhost; int /*<<< orphan*/  ApplyIPv4AccessListOnArpPacket; int /*<<< orphan*/  DisableUdpFilterForLocalBridgeNic; int /*<<< orphan*/  DisableUdpAcceleration; int /*<<< orphan*/  DisableHttpParsing; int /*<<< orphan*/  NoDhcpPacketLogOutsideHub; int /*<<< orphan*/  DisableAdjustTcpMss; int /*<<< orphan*/  AdjustTcpMssValue; int /*<<< orphan*/  RequiredClientId; int /*<<< orphan*/  FixForDLinkBPDU; int /*<<< orphan*/  VlanTypeId; int /*<<< orphan*/  NoManageVlanId; int /*<<< orphan*/  NoLookBPDUBridgeId; int /*<<< orphan*/  NoIPv6DefaultRouterInRAWhenIPv6; int /*<<< orphan*/  FilterBPDU; int /*<<< orphan*/  NoIPv6PacketLog; int /*<<< orphan*/  NoIPv4PacketLog; int /*<<< orphan*/  FilterNonIP; int /*<<< orphan*/  FilterIPv6; int /*<<< orphan*/  FilterIPv4; int /*<<< orphan*/  FilterOSPF; int /*<<< orphan*/  FilterPPPoE; int /*<<< orphan*/  ClientMinimumRequiredBuild; int /*<<< orphan*/  BroadcastStormDetectionThreshold; int /*<<< orphan*/  NoSpinLockForPacketDelay; int /*<<< orphan*/  YieldAfterStorePacket; int /*<<< orphan*/  DisableIPParsing; int /*<<< orphan*/  ManageOnlyLocalUnicastIPv6; int /*<<< orphan*/  ManageOnlyPrivateIP; int /*<<< orphan*/  NoMacAddressLog; int /*<<< orphan*/  NoIpTable; int /*<<< orphan*/  NoIPv6AddrPolling; int /*<<< orphan*/  NoArpPolling; } ;
typedef  int /*<<< orphan*/  RPC_ADMIN_OPTION ;
typedef  TYPE_1__ HUB_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  GetHubAdminOptionDataAndSet (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

void DataToHubOptionStruct(HUB_OPTION *o, RPC_ADMIN_OPTION *ao)
{
	// Validate arguments
	if (o == NULL || ao == NULL)
	{
		return;
	}

	GetHubAdminOptionDataAndSet(ao, "NoAddressPollingIPv4", &o->NoArpPolling);
	GetHubAdminOptionDataAndSet(ao, "NoAddressPollingIPv6", &o->NoIPv6AddrPolling);
	GetHubAdminOptionDataAndSet(ao, "NoIpTable", &o->NoIpTable);
	GetHubAdminOptionDataAndSet(ao, "NoMacAddressLog", &o->NoMacAddressLog);
	GetHubAdminOptionDataAndSet(ao, "ManageOnlyPrivateIP", &o->ManageOnlyPrivateIP);
	GetHubAdminOptionDataAndSet(ao, "ManageOnlyLocalUnicastIPv6", &o->ManageOnlyLocalUnicastIPv6);
	GetHubAdminOptionDataAndSet(ao, "DisableIPParsing", &o->DisableIPParsing);
	GetHubAdminOptionDataAndSet(ao, "YieldAfterStorePacket", &o->YieldAfterStorePacket);
	GetHubAdminOptionDataAndSet(ao, "NoSpinLockForPacketDelay", &o->NoSpinLockForPacketDelay);
	GetHubAdminOptionDataAndSet(ao, "BroadcastStormDetectionThreshold", &o->BroadcastStormDetectionThreshold);
	GetHubAdminOptionDataAndSet(ao, "ClientMinimumRequiredBuild", &o->ClientMinimumRequiredBuild);
	GetHubAdminOptionDataAndSet(ao, "FilterPPPoE", &o->FilterPPPoE);
	GetHubAdminOptionDataAndSet(ao, "FilterOSPF", &o->FilterOSPF);
	GetHubAdminOptionDataAndSet(ao, "FilterIPv4", &o->FilterIPv4);
	GetHubAdminOptionDataAndSet(ao, "FilterIPv6", &o->FilterIPv6);
	GetHubAdminOptionDataAndSet(ao, "FilterNonIP", &o->FilterNonIP);
	GetHubAdminOptionDataAndSet(ao, "NoIPv4PacketLog", &o->NoIPv4PacketLog);
	GetHubAdminOptionDataAndSet(ao, "NoIPv6PacketLog", &o->NoIPv6PacketLog);
	GetHubAdminOptionDataAndSet(ao, "FilterBPDU", &o->FilterBPDU);
	GetHubAdminOptionDataAndSet(ao, "NoIPv6DefaultRouterInRAWhenIPv6", &o->NoIPv6DefaultRouterInRAWhenIPv6);
	GetHubAdminOptionDataAndSet(ao, "NoLookBPDUBridgeId", &o->NoLookBPDUBridgeId);
	GetHubAdminOptionDataAndSet(ao, "NoManageVlanId", &o->NoManageVlanId);
	GetHubAdminOptionDataAndSet(ao, "VlanTypeId", &o->VlanTypeId);
	GetHubAdminOptionDataAndSet(ao, "FixForDLinkBPDU", &o->FixForDLinkBPDU);
	GetHubAdminOptionDataAndSet(ao, "RequiredClientId", &o->RequiredClientId);
	GetHubAdminOptionDataAndSet(ao, "AdjustTcpMssValue", &o->AdjustTcpMssValue);
	GetHubAdminOptionDataAndSet(ao, "DisableAdjustTcpMss", &o->DisableAdjustTcpMss);
	GetHubAdminOptionDataAndSet(ao, "NoDhcpPacketLogOutsideHub", &o->NoDhcpPacketLogOutsideHub);
	GetHubAdminOptionDataAndSet(ao, "DisableHttpParsing", &o->DisableHttpParsing);
	GetHubAdminOptionDataAndSet(ao, "DisableUdpAcceleration", &o->DisableUdpAcceleration);
	GetHubAdminOptionDataAndSet(ao, "DisableUdpFilterForLocalBridgeNic", &o->DisableUdpFilterForLocalBridgeNic);
	GetHubAdminOptionDataAndSet(ao, "ApplyIPv4AccessListOnArpPacket", &o->ApplyIPv4AccessListOnArpPacket);
	GetHubAdminOptionDataAndSet(ao, "RemoveDefGwOnDhcpForLocalhost", &o->RemoveDefGwOnDhcpForLocalhost);
	GetHubAdminOptionDataAndSet(ao, "SecureNAT_MaxTcpSessionsPerIp", &o->SecureNAT_MaxTcpSessionsPerIp);
	GetHubAdminOptionDataAndSet(ao, "SecureNAT_MaxTcpSynSentPerIp", &o->SecureNAT_MaxTcpSynSentPerIp);
	GetHubAdminOptionDataAndSet(ao, "SecureNAT_MaxUdpSessionsPerIp", &o->SecureNAT_MaxUdpSessionsPerIp);
	GetHubAdminOptionDataAndSet(ao, "SecureNAT_MaxDnsSessionsPerIp", &o->SecureNAT_MaxDnsSessionsPerIp);
	GetHubAdminOptionDataAndSet(ao, "SecureNAT_MaxIcmpSessionsPerIp", &o->SecureNAT_MaxIcmpSessionsPerIp);
	GetHubAdminOptionDataAndSet(ao, "AccessListIncludeFileCacheLifetime", &o->AccessListIncludeFileCacheLifetime);
	GetHubAdminOptionDataAndSet(ao, "DisableKernelModeSecureNAT", &o->DisableKernelModeSecureNAT);
	GetHubAdminOptionDataAndSet(ao, "DisableIpRawModeSecureNAT", &o->DisableIpRawModeSecureNAT);
	GetHubAdminOptionDataAndSet(ao, "DisableUserModeSecureNAT", &o->DisableUserModeSecureNAT);
	GetHubAdminOptionDataAndSet(ao, "DisableCheckMacOnLocalBridge", &o->DisableCheckMacOnLocalBridge);
	GetHubAdminOptionDataAndSet(ao, "DisableCorrectIpOffloadChecksum", &o->DisableCorrectIpOffloadChecksum);
	GetHubAdminOptionDataAndSet(ao, "BroadcastLimiterStrictMode", &o->BroadcastLimiterStrictMode);
	GetHubAdminOptionDataAndSet(ao, "MaxLoggedPacketsPerMinute", &o->MaxLoggedPacketsPerMinute);
	GetHubAdminOptionDataAndSet(ao, "DoNotSaveHeavySecurityLogs", &o->DoNotSaveHeavySecurityLogs);
	GetHubAdminOptionDataAndSet(ao, "DropBroadcastsInPrivacyFilterMode", &o->DropBroadcastsInPrivacyFilterMode);
	GetHubAdminOptionDataAndSet(ao, "DropArpInPrivacyFilterMode", &o->DropArpInPrivacyFilterMode);
	GetHubAdminOptionDataAndSet(ao, "SuppressClientUpdateNotification", &o->SuppressClientUpdateNotification);
	GetHubAdminOptionDataAndSet(ao, "FloodingSendQueueBufferQuota", &o->FloodingSendQueueBufferQuota);
	GetHubAdminOptionDataAndSet(ao, "AssignVLanIdByRadiusAttribute", &o->AssignVLanIdByRadiusAttribute);
	GetHubAdminOptionDataAndSet(ao, "DenyAllRadiusLoginWithNoVlanAssign", &o->DenyAllRadiusLoginWithNoVlanAssign);
	GetHubAdminOptionDataAndSet(ao, "SecureNAT_RandomizeAssignIp", &o->SecureNAT_RandomizeAssignIp);
	GetHubAdminOptionDataAndSet(ao, "DetectDormantSessionInterval", &o->DetectDormantSessionInterval);
	GetHubAdminOptionDataAndSet(ao, "NoPhysicalIPOnPacketLog", &o->NoPhysicalIPOnPacketLog);
	GetHubAdminOptionDataAndSet(ao, "UseHubNameAsDhcpUserClassOption", &o->UseHubNameAsDhcpUserClassOption);
	GetHubAdminOptionDataAndSet(ao, "UseHubNameAsRadiusNasId", &o->UseHubNameAsRadiusNasId);
}