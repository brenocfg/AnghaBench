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
struct TYPE_4__ {int UseNat; int Mtu; int NatTcpTimeout; int NatUdpTimeout; int UseDhcp; int DhcpExpireTimeSpan; int SaveLog; int /*<<< orphan*/  DhcpDomainName; int /*<<< orphan*/  DhcpDnsServerAddress; int /*<<< orphan*/  DhcpGatewayAddress; int /*<<< orphan*/  DhcpSubnetMask; int /*<<< orphan*/  DhcpLeaseIPEnd; int /*<<< orphan*/  DhcpLeaseIPStart; int /*<<< orphan*/  Mask; int /*<<< orphan*/  Ip; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ VH_OPTION ;
typedef  int /*<<< orphan*/  NAT ;

/* Variables and functions */
 int /*<<< orphan*/  GenMacAddress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDomainName (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetIP (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void NiSetDefaultVhOption(NAT *n, VH_OPTION *o)
{
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	Zero(o, sizeof(VH_OPTION));
	GenMacAddress(o->MacAddress);

	// Set the virtual IP to 192.168.30.1/24
	SetIP(&o->Ip, 192, 168, 30, 1);
	SetIP(&o->Mask, 255, 255, 255, 0);
	o->UseNat = true;
	o->Mtu = 1500;
	o->NatTcpTimeout = 1800;
	o->NatUdpTimeout = 60;
	o->UseDhcp = true;
	SetIP(&o->DhcpLeaseIPStart, 192, 168, 30, 10);
	SetIP(&o->DhcpLeaseIPEnd, 192, 168, 30, 200);
	SetIP(&o->DhcpSubnetMask, 255, 255, 255, 0);
	o->DhcpExpireTimeSpan = 7200;
	o->SaveLog = true;

	SetIP(&o->DhcpGatewayAddress, 192, 168, 30, 1);
	SetIP(&o->DhcpDnsServerAddress, 192, 168, 30, 1);

	GetDomainName(o->DhcpDomainName, sizeof(o->DhcpDomainName));
}