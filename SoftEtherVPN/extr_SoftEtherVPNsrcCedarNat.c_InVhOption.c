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
struct TYPE_4__ {int /*<<< orphan*/  DhcpPushRoutes; void* ApplyDhcpPushRoutes; int /*<<< orphan*/  HubName; void* SaveLog; int /*<<< orphan*/  DhcpDomainName; int /*<<< orphan*/  DhcpDnsServerAddress2; int /*<<< orphan*/  DhcpDnsServerAddress; int /*<<< orphan*/  DhcpGatewayAddress; void* DhcpExpireTimeSpan; int /*<<< orphan*/  DhcpSubnetMask; int /*<<< orphan*/  DhcpLeaseIPEnd; int /*<<< orphan*/  DhcpLeaseIPStart; void* UseDhcp; void* NatUdpTimeout; void* NatTcpTimeout; void* Mtu; void* UseNat; int /*<<< orphan*/  Mask; int /*<<< orphan*/  Ip; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ VH_OPTION ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InVhOption(VH_OPTION *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(VH_OPTION));
	PackGetData2(p, "MacAddress", t->MacAddress, 6);
	PackGetIp(p, "Ip", &t->Ip);
	PackGetIp(p, "Mask", &t->Mask);
	t->UseNat = PackGetBool(p, "UseNat");
	t->Mtu = PackGetInt(p, "Mtu");
	t->NatTcpTimeout = PackGetInt(p, "NatTcpTimeout");
	t->NatUdpTimeout = PackGetInt(p, "NatUdpTimeout");
	t->UseDhcp = PackGetBool(p, "UseDhcp");
	PackGetIp(p, "DhcpLeaseIPStart", &t->DhcpLeaseIPStart);
	PackGetIp(p, "DhcpLeaseIPEnd", &t->DhcpLeaseIPEnd);
	PackGetIp(p, "DhcpSubnetMask", &t->DhcpSubnetMask);
	t->DhcpExpireTimeSpan = PackGetInt(p, "DhcpExpireTimeSpan");
	PackGetIp(p, "DhcpGatewayAddress", &t->DhcpGatewayAddress);
	PackGetIp(p, "DhcpDnsServerAddress", &t->DhcpDnsServerAddress);
	PackGetIp(p, "DhcpDnsServerAddress2", &t->DhcpDnsServerAddress2);
	PackGetStr(p, "DhcpDomainName", t->DhcpDomainName, sizeof(t->DhcpDomainName));
	t->SaveLog = PackGetBool(p, "SaveLog");
	PackGetStr(p, "RpcHubName", t->HubName, sizeof(t->HubName));
	t->ApplyDhcpPushRoutes = PackGetBool(p, "ApplyDhcpPushRoutes");
	PackGetStr(p, "DhcpPushRoutes", t->DhcpPushRoutes, sizeof(t->DhcpPushRoutes));
}