#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mac_address ;
struct TYPE_4__ {char* DhcpDomainName; int /*<<< orphan*/  SaveLog; int /*<<< orphan*/  DhcpDnsServerAddress2; int /*<<< orphan*/  DhcpDnsServerAddress; int /*<<< orphan*/  DhcpGatewayAddress; int /*<<< orphan*/  DhcpExpireTimeSpan; int /*<<< orphan*/  DhcpSubnetMask; int /*<<< orphan*/  DhcpLeaseIPEnd; int /*<<< orphan*/  DhcpLeaseIPStart; int /*<<< orphan*/  UseDhcp; int /*<<< orphan*/  NatUdpTimeout; int /*<<< orphan*/  NatTcpTimeout; int /*<<< orphan*/  Mtu; int /*<<< orphan*/  UseNat; int /*<<< orphan*/  Mask; int /*<<< orphan*/  Ip; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ VH_OPTION ;
struct TYPE_5__ {TYPE_1__ Option; } ;
typedef  TYPE_2__ NAT ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MacToStr (char*,int,int /*<<< orphan*/ ) ; 

void NiWriteVhOption(NAT *n, FOLDER *root)
{
	VH_OPTION *o;
	FOLDER *host, *nat, *dhcp;
	char mac_address[MAX_SIZE];
	// Validate arguments
	if (n == NULL || root == NULL)
	{
		return;
	}

	host = CfgCreateFolder(root, "VirtualHost");
	nat = CfgCreateFolder(root, "VirtualRouter");
	dhcp = CfgCreateFolder(root, "VirtualDhcpServer");

	o = &n->Option;

	MacToStr(mac_address, sizeof(mac_address), o->MacAddress);
	CfgAddStr(host, "VirtualHostMacAddress", mac_address);
	CfgAddIp(host, "VirtualHostIp", &o->Ip);
	CfgAddIp(host, "VirtualHostIpSubnetMask", &o->Mask);

	CfgAddBool(nat, "NatEnabled", o->UseNat);
	CfgAddInt(nat, "NatMtu", o->Mtu);
	CfgAddInt(nat, "NatTcpTimeout", o->NatTcpTimeout);
	CfgAddInt(nat, "NatUdpTimeout", o->NatUdpTimeout);

	CfgAddBool(dhcp, "DhcpEnabled", o->UseDhcp);
	CfgAddIp(dhcp, "DhcpLeaseIPStart", &o->DhcpLeaseIPStart);
	CfgAddIp(dhcp, "DhcpLeaseIPEnd", &o->DhcpLeaseIPEnd);
	CfgAddIp(dhcp, "DhcpSubnetMask", &o->DhcpSubnetMask);
	CfgAddInt(dhcp, "DhcpExpireTimeSpan", o->DhcpExpireTimeSpan);
	CfgAddIp(dhcp, "DhcpGatewayAddress", &o->DhcpGatewayAddress);
	CfgAddIp(dhcp, "DhcpDnsServerAddress", &o->DhcpDnsServerAddress);
	CfgAddIp(dhcp, "DhcpDnsServerAddress2", &o->DhcpDnsServerAddress2);
	CfgAddStr(dhcp, "DhcpDomainName", o->DhcpDomainName);

	CfgAddBool(root, "SaveLog", o->SaveLog);
}