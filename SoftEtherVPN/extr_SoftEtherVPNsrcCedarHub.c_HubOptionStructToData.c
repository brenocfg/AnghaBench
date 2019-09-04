#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_7__ {int /*<<< orphan*/  UseHubNameAsRadiusNasId; int /*<<< orphan*/  UseHubNameAsDhcpUserClassOption; int /*<<< orphan*/  NoPhysicalIPOnPacketLog; int /*<<< orphan*/  DetectDormantSessionInterval; int /*<<< orphan*/  SecureNAT_RandomizeAssignIp; int /*<<< orphan*/  DenyAllRadiusLoginWithNoVlanAssign; int /*<<< orphan*/  AssignVLanIdByRadiusAttribute; int /*<<< orphan*/  FloodingSendQueueBufferQuota; int /*<<< orphan*/  SuppressClientUpdateNotification; int /*<<< orphan*/  DropArpInPrivacyFilterMode; int /*<<< orphan*/  DropBroadcastsInPrivacyFilterMode; int /*<<< orphan*/  DoNotSaveHeavySecurityLogs; int /*<<< orphan*/  MaxLoggedPacketsPerMinute; int /*<<< orphan*/  BroadcastLimiterStrictMode; int /*<<< orphan*/  DisableCorrectIpOffloadChecksum; int /*<<< orphan*/  DisableCheckMacOnLocalBridge; int /*<<< orphan*/  DisableUserModeSecureNAT; int /*<<< orphan*/  DisableIpRawModeSecureNAT; int /*<<< orphan*/  DisableKernelModeSecureNAT; int /*<<< orphan*/  AccessListIncludeFileCacheLifetime; int /*<<< orphan*/  SecureNAT_MaxIcmpSessionsPerIp; int /*<<< orphan*/  SecureNAT_MaxDnsSessionsPerIp; int /*<<< orphan*/  SecureNAT_MaxUdpSessionsPerIp; int /*<<< orphan*/  SecureNAT_MaxTcpSynSentPerIp; int /*<<< orphan*/  SecureNAT_MaxTcpSessionsPerIp; int /*<<< orphan*/  RemoveDefGwOnDhcpForLocalhost; int /*<<< orphan*/  ApplyIPv4AccessListOnArpPacket; int /*<<< orphan*/  DisableUdpFilterForLocalBridgeNic; int /*<<< orphan*/  DisableUdpAcceleration; int /*<<< orphan*/  DisableHttpParsing; int /*<<< orphan*/  NoDhcpPacketLogOutsideHub; int /*<<< orphan*/  DisableAdjustTcpMss; int /*<<< orphan*/  AdjustTcpMssValue; int /*<<< orphan*/  RequiredClientId; int /*<<< orphan*/  FixForDLinkBPDU; int /*<<< orphan*/  VlanTypeId; int /*<<< orphan*/  NoManageVlanId; int /*<<< orphan*/  NoLookBPDUBridgeId; int /*<<< orphan*/  NoIPv6DefaultRouterInRAWhenIPv6; int /*<<< orphan*/  FilterBPDU; int /*<<< orphan*/  NoIPv6PacketLog; int /*<<< orphan*/  NoIPv4PacketLog; int /*<<< orphan*/  FilterNonIP; int /*<<< orphan*/  FilterIPv6; int /*<<< orphan*/  FilterIPv4; int /*<<< orphan*/  FilterOSPF; int /*<<< orphan*/  FilterPPPoE; int /*<<< orphan*/  ClientMinimumRequiredBuild; int /*<<< orphan*/  BroadcastStormDetectionThreshold; int /*<<< orphan*/  NoSpinLockForPacketDelay; int /*<<< orphan*/  YieldAfterStorePacket; int /*<<< orphan*/  DisableIPParsing; int /*<<< orphan*/  ManageOnlyLocalUnicastIPv6; int /*<<< orphan*/  ManageOnlyPrivateIP; int /*<<< orphan*/  NoMacAddressLog; int /*<<< orphan*/  NoIpTable; int /*<<< orphan*/  NoIPv6AddrPolling; int /*<<< orphan*/  NoArpPolling; } ;
struct TYPE_6__ {size_t NumItem; int /*<<< orphan*/ * Items; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_ADMIN_OPTION ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ HUB_OPTION ;
typedef  int /*<<< orphan*/  ADMIN_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewAdminOption (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

void HubOptionStructToData(RPC_ADMIN_OPTION *ao, HUB_OPTION *o, char *hub_name)
{
	LIST *aol;
	UINT i;
	// Validate arguments
	if (ao == NULL || o == NULL || hub_name == NULL)
	{
		return;
	}

	aol = NewListFast(NULL);

	Add(aol, NewAdminOption("NoAddressPollingIPv4", o->NoArpPolling));
	Add(aol, NewAdminOption("NoAddressPollingIPv6", o->NoIPv6AddrPolling));
	Add(aol, NewAdminOption("NoIpTable", o->NoIpTable));
	Add(aol, NewAdminOption("NoMacAddressLog", o->NoMacAddressLog));
	Add(aol, NewAdminOption("ManageOnlyPrivateIP", o->ManageOnlyPrivateIP));
	Add(aol, NewAdminOption("ManageOnlyLocalUnicastIPv6", o->ManageOnlyLocalUnicastIPv6));
	Add(aol, NewAdminOption("DisableIPParsing", o->DisableIPParsing));
	Add(aol, NewAdminOption("YieldAfterStorePacket", o->YieldAfterStorePacket));
	Add(aol, NewAdminOption("NoSpinLockForPacketDelay", o->NoSpinLockForPacketDelay));
	Add(aol, NewAdminOption("BroadcastStormDetectionThreshold", o->BroadcastStormDetectionThreshold));
	Add(aol, NewAdminOption("ClientMinimumRequiredBuild", o->ClientMinimumRequiredBuild));
	Add(aol, NewAdminOption("FilterPPPoE", o->FilterPPPoE));
	Add(aol, NewAdminOption("FilterOSPF", o->FilterOSPF));
	Add(aol, NewAdminOption("FilterIPv4", o->FilterIPv4));
	Add(aol, NewAdminOption("FilterIPv6", o->FilterIPv6));
	Add(aol, NewAdminOption("FilterNonIP", o->FilterNonIP));
	Add(aol, NewAdminOption("NoIPv4PacketLog", o->NoIPv4PacketLog));
	Add(aol, NewAdminOption("NoIPv6PacketLog", o->NoIPv6PacketLog));
	Add(aol, NewAdminOption("FilterBPDU", o->FilterBPDU));
	Add(aol, NewAdminOption("NoIPv6DefaultRouterInRAWhenIPv6", o->NoIPv6DefaultRouterInRAWhenIPv6));
	Add(aol, NewAdminOption("NoLookBPDUBridgeId", o->NoLookBPDUBridgeId));
	Add(aol, NewAdminOption("NoManageVlanId", o->NoManageVlanId));
	Add(aol, NewAdminOption("VlanTypeId", o->VlanTypeId));
	Add(aol, NewAdminOption("FixForDLinkBPDU", o->FixForDLinkBPDU));
	Add(aol, NewAdminOption("RequiredClientId", o->RequiredClientId));
	Add(aol, NewAdminOption("AdjustTcpMssValue", o->AdjustTcpMssValue));
	Add(aol, NewAdminOption("DisableAdjustTcpMss", o->DisableAdjustTcpMss));
	Add(aol, NewAdminOption("NoDhcpPacketLogOutsideHub", o->NoDhcpPacketLogOutsideHub));
	Add(aol, NewAdminOption("DisableHttpParsing", o->DisableHttpParsing));
	Add(aol, NewAdminOption("DisableUdpAcceleration", o->DisableUdpAcceleration));
	Add(aol, NewAdminOption("DisableUdpFilterForLocalBridgeNic", o->DisableUdpFilterForLocalBridgeNic));
	Add(aol, NewAdminOption("ApplyIPv4AccessListOnArpPacket", o->ApplyIPv4AccessListOnArpPacket));
	Add(aol, NewAdminOption("RemoveDefGwOnDhcpForLocalhost", o->RemoveDefGwOnDhcpForLocalhost));
	Add(aol, NewAdminOption("SecureNAT_MaxTcpSessionsPerIp", o->SecureNAT_MaxTcpSessionsPerIp));
	Add(aol, NewAdminOption("SecureNAT_MaxTcpSynSentPerIp", o->SecureNAT_MaxTcpSynSentPerIp));
	Add(aol, NewAdminOption("SecureNAT_MaxUdpSessionsPerIp", o->SecureNAT_MaxUdpSessionsPerIp));
	Add(aol, NewAdminOption("SecureNAT_MaxDnsSessionsPerIp", o->SecureNAT_MaxDnsSessionsPerIp));
	Add(aol, NewAdminOption("SecureNAT_MaxIcmpSessionsPerIp", o->SecureNAT_MaxIcmpSessionsPerIp));
	Add(aol, NewAdminOption("AccessListIncludeFileCacheLifetime", o->AccessListIncludeFileCacheLifetime));
	Add(aol, NewAdminOption("DisableKernelModeSecureNAT", o->DisableKernelModeSecureNAT));
	Add(aol, NewAdminOption("DisableIpRawModeSecureNAT", o->DisableIpRawModeSecureNAT));
	Add(aol, NewAdminOption("DisableUserModeSecureNAT", o->DisableUserModeSecureNAT));
	Add(aol, NewAdminOption("DisableCheckMacOnLocalBridge", o->DisableCheckMacOnLocalBridge));
	Add(aol, NewAdminOption("DisableCorrectIpOffloadChecksum", o->DisableCorrectIpOffloadChecksum));
	Add(aol, NewAdminOption("BroadcastLimiterStrictMode", o->BroadcastLimiterStrictMode));
	Add(aol, NewAdminOption("MaxLoggedPacketsPerMinute", o->MaxLoggedPacketsPerMinute));
	Add(aol, NewAdminOption("DoNotSaveHeavySecurityLogs", o->DoNotSaveHeavySecurityLogs));
	Add(aol, NewAdminOption("DropBroadcastsInPrivacyFilterMode", o->DropBroadcastsInPrivacyFilterMode));
	Add(aol, NewAdminOption("DropArpInPrivacyFilterMode", o->DropArpInPrivacyFilterMode));
	Add(aol, NewAdminOption("SuppressClientUpdateNotification", o->SuppressClientUpdateNotification));
	Add(aol, NewAdminOption("FloodingSendQueueBufferQuota", o->FloodingSendQueueBufferQuota));
	Add(aol, NewAdminOption("AssignVLanIdByRadiusAttribute", o->AssignVLanIdByRadiusAttribute));
	Add(aol, NewAdminOption("DenyAllRadiusLoginWithNoVlanAssign", o->DenyAllRadiusLoginWithNoVlanAssign));
	Add(aol, NewAdminOption("SecureNAT_RandomizeAssignIp", o->SecureNAT_RandomizeAssignIp));
	Add(aol, NewAdminOption("DetectDormantSessionInterval", o->DetectDormantSessionInterval));
	Add(aol, NewAdminOption("NoPhysicalIPOnPacketLog", o->NoPhysicalIPOnPacketLog));
	Add(aol, NewAdminOption("UseHubNameAsDhcpUserClassOption", o->UseHubNameAsDhcpUserClassOption));
	Add(aol, NewAdminOption("UseHubNameAsRadiusNasId", o->UseHubNameAsRadiusNasId));

	Zero(ao, sizeof(RPC_ADMIN_OPTION));

	StrCpy(ao->HubName, sizeof(ao->HubName), hub_name);

	ao->NumItem = LIST_NUM(aol);
	ao->Items = ZeroMalloc(sizeof(ADMIN_OPTION) * ao->NumItem);

	for (i = 0;i < LIST_NUM(aol);i++)
	{
		ADMIN_OPTION *a = LIST_DATA(aol, i);

		Copy(&ao->Items[i], a, sizeof(ADMIN_OPTION));

		Free(a);
	}

	ReleaseList(aol);
}