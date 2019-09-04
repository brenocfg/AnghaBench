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
typedef  int /*<<< orphan*/  mac_address ;
struct TYPE_7__ {char* DhcpDomainName; char* DhcpPushRoutes; int ApplyDhcpPushRoutes; void* SaveLog; int /*<<< orphan*/  DhcpDnsServerAddress2; int /*<<< orphan*/  DhcpDnsServerAddress; int /*<<< orphan*/  DhcpGatewayAddress; void* DhcpExpireTimeSpan; int /*<<< orphan*/  DhcpSubnetMask; int /*<<< orphan*/  DhcpLeaseIPEnd; int /*<<< orphan*/  DhcpLeaseIPStart; void* UseDhcp; void* NatUdpTimeout; void* NatTcpTimeout; void* Mtu; void* UseNat; int /*<<< orphan*/  Mask; int /*<<< orphan*/  Ip; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ VH_OPTION ;
struct TYPE_8__ {int Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  GenMacAddress (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NormalizeClasslessRouteTableStr (char*,int,char*) ; 
 scalar_t__ StrLen (char*) ; 
 TYPE_2__* StrToBin (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void NiLoadVhOptionEx(VH_OPTION *o, FOLDER *root)
{
	FOLDER *host, *nat, *dhcp;
	char mac_address[MAX_SIZE];
	// Validate arguments
	if (o == NULL || root == NULL)
	{
		return;
	}

	host = CfgGetFolder(root, "VirtualHost");
	nat = CfgGetFolder(root, "VirtualRouter");
	dhcp = CfgGetFolder(root, "VirtualDhcpServer");

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

	CfgGetStr(dhcp, "DhcpPushRoutes", o->DhcpPushRoutes, sizeof(o->DhcpPushRoutes));

// Test code
//	StrCpy(o->DhcpPushRoutes, sizeof(o->DhcpPushRoutes),
//		"130.158.6.0/24/192.168.9.2 130.158.80.244/255.255.255.255/192.168.9.2");

	NormalizeClasslessRouteTableStr(o->DhcpPushRoutes, sizeof(o->DhcpPushRoutes), o->DhcpPushRoutes);
	o->ApplyDhcpPushRoutes = true;

	Trim(o->DhcpDomainName);
	if (StrLen(o->DhcpDomainName) == 0)
	{
		//GetDomainName(o->DhcpDomainName, sizeof(o->DhcpDomainName));
	}

	o->SaveLog = CfgGetBool(root, "SaveLog");
}