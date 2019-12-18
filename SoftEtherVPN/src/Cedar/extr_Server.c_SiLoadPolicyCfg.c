#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* VLanId; void* NoIPv6DefaultRouterInRAWhenIPv6; void* NoIPv6DefaultRouterInRA; void* FilterNonIP; void* FilterIPv6; void* FilterIPv4; void* AutoDisconnect; void* NoSavePassword; void* MaxIPv6; void* NoServerV6; void* CheckIPv6; void* NoRoutingV6; void* DHCPv6NoServer; void* DHCPv6Filter; void* RAFilter; void* RSandRAFilter; void* NoQoS; void* MultiLogins; void* FixPassword; void* MaxDownload; void* MaxUpload; void* MaxIP; void* MaxMac; void* TimeOut; void* MaxConnection; void* MonitorPort; void* NoBroadcastLimiter; void* NoServer; void* PrivacyFilter; void* ArpDhcpOnly; void* CheckIP; void* CheckMac; void* NoRouting; void* NoBridge; void* DHCPForce; void* DHCPNoServer; void* DHCPFilter; void* Access; } ;
typedef  TYPE_1__ POLICY ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void SiLoadPolicyCfg(POLICY *p, FOLDER *f)
{
	// Validate arguments
	if (f == NULL || p == NULL)
	{
		return;
	}

	Zero(p, sizeof(POLICY));

	// Ver 2
	p->Access = CfgGetBool(f, "Access");
	p->DHCPFilter = CfgGetBool(f, "DHCPFilter");
	p->DHCPNoServer = CfgGetBool(f, "DHCPNoServer");
	p->DHCPForce = CfgGetBool(f, "DHCPForce");
	p->NoBridge = CfgGetBool(f, "NoBridge");
	p->NoRouting = CfgGetBool(f, "NoRouting");
	p->CheckMac = CfgGetBool(f, "CheckMac");
	p->CheckIP = CfgGetBool(f, "CheckIP");
	p->ArpDhcpOnly = CfgGetBool(f, "ArpDhcpOnly");
	p->PrivacyFilter = CfgGetBool(f, "PrivacyFilter");
	p->NoServer = CfgGetBool(f, "NoServer");
	p->NoBroadcastLimiter = CfgGetBool(f, "NoBroadcastLimiter");
	p->MonitorPort = CfgGetBool(f, "MonitorPort");
	p->MaxConnection = CfgGetInt(f, "MaxConnection");
	p->TimeOut = CfgGetInt(f, "TimeOut");
	p->MaxMac = CfgGetInt(f, "MaxMac");
	p->MaxIP = CfgGetInt(f, "MaxIP");
	p->MaxUpload = CfgGetInt(f, "MaxUpload");
	p->MaxDownload = CfgGetInt(f, "MaxDownload");
	p->FixPassword = CfgGetBool(f, "FixPassword");
	p->MultiLogins = CfgGetInt(f, "MultiLogins");
	p->NoQoS = CfgGetBool(f, "NoQoS");

	// Ver 3
	p->RSandRAFilter = CfgGetBool(f, "RSandRAFilter");
	p->RAFilter = CfgGetBool(f, "RAFilter");
	p->DHCPv6Filter = CfgGetBool(f, "DHCPv6Filter");
	p->DHCPv6NoServer = CfgGetBool(f, "DHCPv6NoServer");
	p->NoRoutingV6 = CfgGetBool(f, "NoRoutingV6");
	p->CheckIPv6 = CfgGetBool(f, "CheckIPv6");
	p->NoServerV6 = CfgGetBool(f, "NoServerV6");
	p->MaxIPv6 = CfgGetInt(f, "MaxIPv6");
	p->NoSavePassword = CfgGetBool(f, "NoSavePassword");
	p->AutoDisconnect = CfgGetInt(f, "AutoDisconnect");
	p->FilterIPv4 = CfgGetBool(f, "FilterIPv4");
	p->FilterIPv6 = CfgGetBool(f, "FilterIPv6");
	p->FilterNonIP = CfgGetBool(f, "FilterNonIP");
	p->NoIPv6DefaultRouterInRA = CfgGetBool(f, "NoIPv6DefaultRouterInRA");
	p->NoIPv6DefaultRouterInRAWhenIPv6 = CfgGetBool(f, "NoIPv6DefaultRouterInRAWhenIPv6");
	p->VLanId = CfgGetInt(f, "VLanId");
}