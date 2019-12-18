#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  Access ; 
 int /*<<< orphan*/  ArpDhcpOnly ; 
 int /*<<< orphan*/  AutoDisconnect ; 
 int /*<<< orphan*/  CheckIP ; 
 int /*<<< orphan*/  CheckIPv6 ; 
 int /*<<< orphan*/  CheckMac ; 
 int /*<<< orphan*/  DHCPFilter ; 
 int /*<<< orphan*/  DHCPForce ; 
 int /*<<< orphan*/  DHCPNoServer ; 
 int /*<<< orphan*/  DHCPv6Filter ; 
 int /*<<< orphan*/  DHCPv6NoServer ; 
 int /*<<< orphan*/  FilterIPv4 ; 
 int /*<<< orphan*/  FilterIPv6 ; 
 int /*<<< orphan*/  FilterNonIP ; 
 int /*<<< orphan*/  FixPassword ; 
 int /*<<< orphan*/  MaxConnection ; 
 int /*<<< orphan*/  MaxDownload ; 
 int /*<<< orphan*/  MaxIP ; 
 int /*<<< orphan*/  MaxIPv6 ; 
 int /*<<< orphan*/  MaxMac ; 
 int /*<<< orphan*/  MaxUpload ; 
 int /*<<< orphan*/  MonitorPort ; 
 int /*<<< orphan*/  MultiLogins ; 
 int /*<<< orphan*/  NoBridge ; 
 int /*<<< orphan*/  NoBroadcastLimiter ; 
 int /*<<< orphan*/  NoIPv6DefaultRouterInRA ; 
 int /*<<< orphan*/  NoIPv6DefaultRouterInRAWhenIPv6 ; 
 int /*<<< orphan*/  NoQoS ; 
 int /*<<< orphan*/  NoRouting ; 
 int /*<<< orphan*/  NoRoutingV6 ; 
 int /*<<< orphan*/  NoSavePassword ; 
 int /*<<< orphan*/  NoServer ; 
 int /*<<< orphan*/  NoServerV6 ; 
 int /*<<< orphan*/  PACK_ADD_POLICY_BOOL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACK_ADD_POLICY_UINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PrivacyFilter ; 
 int /*<<< orphan*/  RAFilter ; 
 int /*<<< orphan*/  RSandRAFilter ; 
 int /*<<< orphan*/  TimeOut ; 
 int /*<<< orphan*/  VLanId ; 

void PackAddPolicy(PACK *p, POLICY *y)
{
	// Validate arguments
	if (p == NULL || y == NULL)
	{
		return;
	}

	// Bool value
	// Ver 2
	PACK_ADD_POLICY_BOOL("Access", Access);
	PACK_ADD_POLICY_BOOL("DHCPFilter", DHCPFilter);
	PACK_ADD_POLICY_BOOL("DHCPNoServer", DHCPNoServer);
	PACK_ADD_POLICY_BOOL("DHCPForce", DHCPForce);
	PACK_ADD_POLICY_BOOL("NoBridge", NoBridge);
	PACK_ADD_POLICY_BOOL("NoRouting", NoRouting);
	PACK_ADD_POLICY_BOOL("PrivacyFilter", PrivacyFilter);
	PACK_ADD_POLICY_BOOL("NoServer", NoServer);
	PACK_ADD_POLICY_BOOL("CheckMac", CheckMac);
	PACK_ADD_POLICY_BOOL("CheckIP", CheckIP);
	PACK_ADD_POLICY_BOOL("ArpDhcpOnly", ArpDhcpOnly);
	PACK_ADD_POLICY_BOOL("MonitorPort", MonitorPort);
	PACK_ADD_POLICY_BOOL("NoBroadcastLimiter", NoBroadcastLimiter);
	PACK_ADD_POLICY_BOOL("FixPassword", FixPassword);
	PACK_ADD_POLICY_BOOL("NoQoS", NoQoS);
	// Ver 3
	PACK_ADD_POLICY_BOOL("RSandRAFilter", RSandRAFilter);
	PACK_ADD_POLICY_BOOL("RAFilter", RAFilter);
	PACK_ADD_POLICY_BOOL("DHCPv6Filter", DHCPv6Filter);
	PACK_ADD_POLICY_BOOL("DHCPv6NoServer", DHCPv6NoServer);
	PACK_ADD_POLICY_BOOL("NoRoutingV6", NoRoutingV6);
	PACK_ADD_POLICY_BOOL("CheckIPv6", CheckIPv6);
	PACK_ADD_POLICY_BOOL("NoServerV6", NoServerV6);
	PACK_ADD_POLICY_BOOL("NoSavePassword", NoSavePassword);
	PACK_ADD_POLICY_BOOL("FilterIPv4", FilterIPv4);
	PACK_ADD_POLICY_BOOL("FilterIPv6", FilterIPv6);
	PACK_ADD_POLICY_BOOL("FilterNonIP", FilterNonIP);
	PACK_ADD_POLICY_BOOL("NoIPv6DefaultRouterInRA", NoIPv6DefaultRouterInRA);
	PACK_ADD_POLICY_BOOL("NoIPv6DefaultRouterInRAWhenIPv6", NoIPv6DefaultRouterInRAWhenIPv6);

	// UINT value
	// Ver 2
	PACK_ADD_POLICY_UINT("MaxConnection", MaxConnection);
	PACK_ADD_POLICY_UINT("TimeOut", TimeOut);
	PACK_ADD_POLICY_UINT("MaxMac", MaxMac);
	PACK_ADD_POLICY_UINT("MaxIP", MaxIP);
	PACK_ADD_POLICY_UINT("MaxUpload", MaxUpload);
	PACK_ADD_POLICY_UINT("MaxDownload", MaxDownload);
	PACK_ADD_POLICY_UINT("MultiLogins", MultiLogins);
	// Ver 3
	PACK_ADD_POLICY_UINT("MaxIPv6", MaxIPv6);
	PACK_ADD_POLICY_UINT("AutoDisconnect", AutoDisconnect);
	PACK_ADD_POLICY_UINT("VLanId", VLanId);

	// Ver 3 flag
	PackAddBool(p, "policy:Ver3", true);
}