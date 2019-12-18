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
struct TYPE_3__ {int /*<<< orphan*/  VLanId; int /*<<< orphan*/  NoIPv6DefaultRouterInRAWhenIPv6; int /*<<< orphan*/  NoIPv6DefaultRouterInRA; int /*<<< orphan*/  FilterNonIP; int /*<<< orphan*/  FilterIPv6; int /*<<< orphan*/  FilterIPv4; int /*<<< orphan*/  AutoDisconnect; int /*<<< orphan*/  NoSavePassword; int /*<<< orphan*/  MaxIPv6; int /*<<< orphan*/  NoServerV6; int /*<<< orphan*/  CheckIPv6; int /*<<< orphan*/  NoRoutingV6; int /*<<< orphan*/  DHCPv6NoServer; int /*<<< orphan*/  DHCPv6Filter; int /*<<< orphan*/  RAFilter; int /*<<< orphan*/  RSandRAFilter; int /*<<< orphan*/  NoQoS; int /*<<< orphan*/  MultiLogins; int /*<<< orphan*/  FixPassword; int /*<<< orphan*/  MaxDownload; int /*<<< orphan*/  MaxUpload; int /*<<< orphan*/  MaxIP; int /*<<< orphan*/  MaxMac; int /*<<< orphan*/  TimeOut; int /*<<< orphan*/  MaxConnection; int /*<<< orphan*/  MonitorPort; int /*<<< orphan*/  NoBroadcastLimiter; int /*<<< orphan*/  NoServer; int /*<<< orphan*/  PrivacyFilter; int /*<<< orphan*/  ArpDhcpOnly; int /*<<< orphan*/  CheckIP; int /*<<< orphan*/  CheckMac; int /*<<< orphan*/  NoRouting; int /*<<< orphan*/  NoBridge; int /*<<< orphan*/  DHCPForce; int /*<<< orphan*/  DHCPNoServer; int /*<<< orphan*/  DHCPFilter; int /*<<< orphan*/  Access; } ;
typedef  TYPE_1__ POLICY ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void SiWritePolicyCfg(FOLDER *f, POLICY *p, bool cascade_mode)
{
	// Validate arguments
	if (f == NULL || p == NULL)
	{
		return;
	}

	// Ver 2.0
	if (cascade_mode == false)
	{
		CfgAddBool(f, "Access", p->Access);
	}

	CfgAddBool(f, "DHCPFilter", p->DHCPFilter);
	CfgAddBool(f, "DHCPNoServer", p->DHCPNoServer);
	CfgAddBool(f, "DHCPForce", p->DHCPForce);

	if (cascade_mode == false)
	{
		CfgAddBool(f, "NoBridge", p->NoBridge);
		CfgAddBool(f, "NoRouting", p->NoRouting);
	}

	CfgAddBool(f, "CheckMac", p->CheckMac);
	CfgAddBool(f, "CheckIP", p->CheckIP);
	CfgAddBool(f, "ArpDhcpOnly", p->ArpDhcpOnly);

	if (cascade_mode == false)
	{
		CfgAddBool(f, "PrivacyFilter", p->PrivacyFilter);
	}

	CfgAddBool(f, "NoServer", p->NoServer);
	CfgAddBool(f, "NoBroadcastLimiter", p->NoBroadcastLimiter);

	if (cascade_mode == false)
	{
		CfgAddBool(f, "MonitorPort", p->MonitorPort);
		CfgAddInt(f, "MaxConnection", p->MaxConnection);
		CfgAddInt(f, "TimeOut", p->TimeOut);
	}

	CfgAddInt(f, "MaxMac", p->MaxMac);
	CfgAddInt(f, "MaxIP", p->MaxIP);
	CfgAddInt(f, "MaxUpload", p->MaxUpload);
	CfgAddInt(f, "MaxDownload", p->MaxDownload);

	if (cascade_mode == false)
	{
		CfgAddBool(f, "FixPassword", p->FixPassword);
		CfgAddInt(f, "MultiLogins", p->MultiLogins);
		CfgAddBool(f, "NoQoS", p->NoQoS);
	}

	// Ver 3.0
	CfgAddBool(f, "RSandRAFilter", p->RSandRAFilter);
	CfgAddBool(f, "RAFilter", p->RAFilter);
	CfgAddBool(f, "DHCPv6Filter", p->DHCPv6Filter);
	CfgAddBool(f, "DHCPv6NoServer", p->DHCPv6NoServer);

	if (cascade_mode == false)
	{
		CfgAddBool(f, "NoRoutingV6", p->NoRoutingV6);
	}

	CfgAddBool(f, "CheckIPv6", p->CheckIPv6);
	CfgAddBool(f, "NoServerV6", p->NoServerV6);
	CfgAddInt(f, "MaxIPv6", p->MaxIPv6);

	if (cascade_mode == false)
	{
		CfgAddBool(f, "NoSavePassword", p->NoSavePassword);
		CfgAddInt(f, "AutoDisconnect", p->AutoDisconnect);
	}

	CfgAddBool(f, "FilterIPv4", p->FilterIPv4);
	CfgAddBool(f, "FilterIPv6", p->FilterIPv6);
	CfgAddBool(f, "FilterNonIP", p->FilterNonIP);
	CfgAddBool(f, "NoIPv6DefaultRouterInRA", p->NoIPv6DefaultRouterInRA);
	CfgAddBool(f, "NoIPv6DefaultRouterInRAWhenIPv6", p->NoIPv6DefaultRouterInRAWhenIPv6);
	CfgAddInt(f, "VLanId", p->VLanId);
}