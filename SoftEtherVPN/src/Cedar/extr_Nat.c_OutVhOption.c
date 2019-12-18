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
struct TYPE_3__ {int UseNat; int UseDhcp; int SaveLog; int /*<<< orphan*/  DhcpPushRoutes; int /*<<< orphan*/  HubName; int /*<<< orphan*/  DhcpDomainName; int /*<<< orphan*/  DhcpDnsServerAddress2; int /*<<< orphan*/  DhcpDnsServerAddress; int /*<<< orphan*/  DhcpGatewayAddress; int /*<<< orphan*/  DhcpExpireTimeSpan; int /*<<< orphan*/  DhcpSubnetMask; int /*<<< orphan*/  DhcpLeaseIPEnd; int /*<<< orphan*/  DhcpLeaseIPStart; int /*<<< orphan*/  NatUdpTimeout; int /*<<< orphan*/  NatTcpTimeout; int /*<<< orphan*/  Mtu; int /*<<< orphan*/  Mask; int /*<<< orphan*/  Ip; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ VH_OPTION ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutVhOption(PACK *p, VH_OPTION *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddData(p, "MacAddress", t->MacAddress, 6);
	PackAddIp(p, "Ip", &t->Ip);
	PackAddIp(p, "Mask", &t->Mask);
	PackAddBool(p, "UseNat", t->UseNat);
	PackAddInt(p, "Mtu", t->Mtu);
	PackAddInt(p, "NatTcpTimeout", t->NatTcpTimeout);
	PackAddInt(p, "NatUdpTimeout", t->NatUdpTimeout);
	PackAddBool(p, "UseDhcp", t->UseDhcp);
	PackAddIp(p, "DhcpLeaseIPStart", &t->DhcpLeaseIPStart);
	PackAddIp(p, "DhcpLeaseIPEnd", &t->DhcpLeaseIPEnd);
	PackAddIp(p, "DhcpSubnetMask", &t->DhcpSubnetMask);
	PackAddInt(p, "DhcpExpireTimeSpan", t->DhcpExpireTimeSpan);
	PackAddIp(p, "DhcpGatewayAddress", &t->DhcpGatewayAddress);
	PackAddIp(p, "DhcpDnsServerAddress", &t->DhcpDnsServerAddress);
	PackAddIp(p, "DhcpDnsServerAddress2", &t->DhcpDnsServerAddress2);
	PackAddStr(p, "DhcpDomainName", t->DhcpDomainName);
	PackAddBool(p, "SaveLog", t->SaveLog);
	PackAddStr(p, "RpcHubName", t->HubName);
	PackAddBool(p, "ApplyDhcpPushRoutes", true);
	PackAddStr(p, "DhcpPushRoutes", t->DhcpPushRoutes);
}