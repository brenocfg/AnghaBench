#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mac_address ;
struct TYPE_8__ {char* DhcpDomainName; void* SaveLog; int /*<<< orphan*/  DhcpDnsServerAddress2; int /*<<< orphan*/  DhcpDnsServerAddress; int /*<<< orphan*/  DhcpGatewayAddress; void* DhcpExpireTimeSpan; int /*<<< orphan*/  DhcpSubnetMask; int /*<<< orphan*/  DhcpLeaseIPEnd; int /*<<< orphan*/  DhcpLeaseIPStart; void* UseDhcp; void* NatUdpTimeout; void* NatTcpTimeout; void* Mtu; void* UseNat; int /*<<< orphan*/  Mask; int /*<<< orphan*/  Ip; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ VH_OPTION ;
struct TYPE_10__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_9__ {TYPE_1__ Option; } ;
typedef  TYPE_2__ NAT ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  GenMacAddress (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 TYPE_3__* StrToBin (char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void NiLoadVhOption(NAT *n, FOLDER *root)
{
	VH_OPTION *o;
	FOLDER *host, *nat, *dhcp;
	char mac_address[MAX_SIZE];
	// Validate arguments
	if (n == NULL || root == NULL)
	{
		return;
	}

	host = CfgGetFolder(root, "VirtualHost");
	nat = CfgGetFolder(root, "VirtualRouter");
	dhcp = CfgGetFolder(root, "VirtualDhcpServer");

	o = &n->Option;
	Zero(o, sizeof(VH_OPTION));

	GenMacAddress(o->MacAddress);
	if (CfgGetStr(host, "VirtualHostMacAddress", mac_address, sizeof(mac_address)))
	{
		BUF *b = StrToBin(mac_address);
		if (b != NULL)
		{
			if (b->Size == 6)
			{
				Copy(o->MacAddress, b->Buf, 6);
			}
		}
		FreeBuf(b);
	}
	CfgGetIp(host, "VirtualHostIp", &o->Ip);
	CfgGetIp(host, "VirtualHostIpSubnetMask", &o->Mask);

	o->UseNat = CfgGetBool(nat, "NatEnabled");
	o->Mtu = CfgGetInt(nat, "NatMtu");
	o->NatTcpTimeout = CfgGetInt(nat, "NatTcpTimeout");
	o->NatUdpTimeout = CfgGetInt(nat, "NatUdpTimeout");

	o->UseDhcp = CfgGetBool(dhcp, "DhcpEnabled");
	CfgGetIp(dhcp, "DhcpLeaseIPStart", &o->DhcpLeaseIPStart);
	CfgGetIp(dhcp, "DhcpLeaseIPEnd", &o->DhcpLeaseIPEnd);
	CfgGetIp(dhcp, "DhcpSubnetMask", &o->DhcpSubnetMask);
	o->DhcpExpireTimeSpan = CfgGetInt(dhcp, "DhcpExpireTimeSpan");
	CfgGetIp(dhcp, "DhcpGatewayAddress", &o->DhcpGatewayAddress);
	CfgGetIp(dhcp, "DhcpDnsServerAddress", &o->DhcpDnsServerAddress);
	CfgGetIp(dhcp, "DhcpDnsServerAddress2", &o->DhcpDnsServerAddress2);
	CfgGetStr(dhcp, "DhcpDomainName", o->DhcpDomainName, sizeof(o->DhcpDomainName));

	o->SaveLog = CfgGetBool(root, "SaveLog");
}