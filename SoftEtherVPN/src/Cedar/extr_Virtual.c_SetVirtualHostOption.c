#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rt ;
struct TYPE_7__ {scalar_t__* MacAddress; int Mtu; scalar_t__ NatTcpTimeout; scalar_t__ NatUdpTimeout; int DhcpExpireTimeSpan; int /*<<< orphan*/  DhcpPushRoutes; scalar_t__ ApplyDhcpPushRoutes; int /*<<< orphan*/  SaveLog; int /*<<< orphan*/  DhcpDomainName; int /*<<< orphan*/  DhcpDnsServerAddress2; int /*<<< orphan*/  DhcpDnsServerAddress; int /*<<< orphan*/  DhcpGatewayAddress; int /*<<< orphan*/  DhcpSubnetMask; int /*<<< orphan*/  DhcpLeaseIPEnd; int /*<<< orphan*/  DhcpLeaseIPStart; int /*<<< orphan*/  UseDhcp; int /*<<< orphan*/  UseNat; int /*<<< orphan*/  Mask; int /*<<< orphan*/  Ip; } ;
typedef  TYPE_1__ VH_OPTION ;
struct TYPE_8__ {int Mtu; int IpMss; int TcpMss; int UdpMss; int NatTcpTimeout; int NatUdpTimeout; int DhcpExpire; int /*<<< orphan*/  PushRoute; int /*<<< orphan*/  SaveLog; int /*<<< orphan*/  DhcpDomain; void* DhcpDns2; void* DhcpDns; void* DhcpGateway; void* DhcpMask; void* DhcpIpStart; void* DhcpIpEnd; int /*<<< orphan*/  UseDhcp; int /*<<< orphan*/  UseNat; void* HostMask; void* HostIP; int /*<<< orphan*/ * MacAddress; } ;
typedef  TYPE_2__ VH ;
typedef  int UINT ;
typedef  scalar_t__ DHCP_CLASSLESS_ROUTE_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int DHCP_MIN_EXPIRE_TIMESPAN ; 
 int /*<<< orphan*/  Debug (char*,int,int) ; 
 scalar_t__ Endian32 (void*) ; 
 int INFINITE ; 
 void* IPToUINT (int /*<<< orphan*/ *) ; 
 int IP_HEADER_SIZE ; 
 int /*<<< orphan*/  LockVirtual (TYPE_2__*) ; 
 int MAC_HEADER_SIZE ; 
 void* MAKESURE (int,int,int) ; 
 int MAX (int,int) ; 
 int MAX_L3_DATA_SIZE ; 
 int MIN (int,int) ; 
 int NAT_TCP_MAX_TIMEOUT ; 
 int NAT_TCP_MIN_TIMEOUT ; 
 int NAT_UDP_MAX_TIMEOUT ; 
 int NAT_UDP_MIN_TIMEOUT ; 
 scalar_t__ ParseClasslessRouteTableStr (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int TCP_HEADER_SIZE ; 
 int UDP_HEADER_SIZE ; 
 int /*<<< orphan*/  UnlockVirtual (TYPE_2__*) ; 
 int /*<<< orphan*/  Zero (scalar_t__*,int) ; 

void SetVirtualHostOption(VH *v, VH_OPTION *vo)
{
	UINT i;
	// Validate arguments
	if (v == NULL || vo == NULL)
	{
		return;
	}

	LockVirtual(v);
	{
		// Set the MAC address
		for (i = 0;i < 6;i++)
		{
			if (vo->MacAddress[i] != 0)
			{
				Copy(v->MacAddress, vo->MacAddress, 6);
				break;
			}
		}

		// Set the host information list
		v->HostIP = IPToUINT(&vo->Ip);
		v->HostMask = IPToUINT(&vo->Mask);

		// Set the MTU, MMS
		v->Mtu = MIN(vo->Mtu, MAX_L3_DATA_SIZE);
		if (v->Mtu == 0)
		{
			v->Mtu = MAX_L3_DATA_SIZE;
		}
		v->Mtu = MAX(v->Mtu, TCP_HEADER_SIZE + IP_HEADER_SIZE + MAC_HEADER_SIZE + 8);
		v->IpMss = ((v->Mtu - IP_HEADER_SIZE) / 8) * 8;
		v->TcpMss = ((v->IpMss - TCP_HEADER_SIZE) / 8) * 8;
		v->UdpMss = ((v->IpMss - UDP_HEADER_SIZE) / 8) * 8;

		if (vo->NatTcpTimeout != 0)
		{
			v->NatTcpTimeout = MIN(vo->NatTcpTimeout, 4000000) * 1000;
		}
		if (vo->NatUdpTimeout != 0)
		{
			v->NatUdpTimeout = MIN(vo->NatUdpTimeout, 4000000) * 1000;
		}
		v->NatTcpTimeout = MAKESURE(v->NatTcpTimeout, NAT_TCP_MIN_TIMEOUT, NAT_TCP_MAX_TIMEOUT);
		v->NatUdpTimeout = MAKESURE(v->NatUdpTimeout, NAT_UDP_MIN_TIMEOUT, NAT_UDP_MAX_TIMEOUT);
		Debug("Timeout: %d , %d\n", v->NatTcpTimeout, v->NatUdpTimeout);

		// NAT using flag
		v->UseNat = vo->UseNat;

		// DHCP using flag
		v->UseDhcp = vo->UseDhcp;

		// Expiration date
		if (vo->DhcpExpireTimeSpan == 0 || vo->DhcpExpireTimeSpan == INFINITE)
		{
			v->DhcpExpire = INFINITE;
		}
		else
		{
			v->DhcpExpire = MAKESURE(DHCP_MIN_EXPIRE_TIMESPAN,
				MIN(vo->DhcpExpireTimeSpan * 1000, 2000000000),
				INFINITE);
		}

		// Address range to be distributed
		v->DhcpIpStart = IPToUINT(&vo->DhcpLeaseIPStart);
		v->DhcpIpEnd = IPToUINT(&vo->DhcpLeaseIPEnd);
		if (Endian32(v->DhcpIpEnd) < Endian32(v->DhcpIpStart))
		{
			v->DhcpIpEnd = v->DhcpIpStart;
		}

		// Subnet mask
		v->DhcpMask = IPToUINT(&vo->DhcpSubnetMask);

		// Gateway address
		v->DhcpGateway = IPToUINT(&vo->DhcpGatewayAddress);

		// DNS server address
		v->DhcpDns = IPToUINT(&vo->DhcpDnsServerAddress);
		v->DhcpDns2 = IPToUINT(&vo->DhcpDnsServerAddress2);

		// Domain name
		StrCpy(v->DhcpDomain, sizeof(v->DhcpDomain), vo->DhcpDomainName);

		// Save a log
		v->SaveLog = vo->SaveLog;

		// DHCP routing table pushing setting
		if (vo->ApplyDhcpPushRoutes)
		{
			DHCP_CLASSLESS_ROUTE_TABLE rt;

			Zero(&rt, sizeof(rt));

			if (ParseClasslessRouteTableStr(&rt, vo->DhcpPushRoutes))
			{
				Copy(&v->PushRoute, &rt, sizeof(DHCP_CLASSLESS_ROUTE_TABLE));
			}
		}
	}
	UnlockVirtual(v);
}