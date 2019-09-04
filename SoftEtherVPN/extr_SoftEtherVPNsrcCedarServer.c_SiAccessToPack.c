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
typedef  int /*<<< orphan*/  zero ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int SrcIpAddress; int SrcSubnetMask; int DestIpAddress; int DestSubnetMask; int /*<<< orphan*/  DestSubnetMask6; int /*<<< orphan*/  DestIpAddress6; int /*<<< orphan*/  SrcSubnetMask6; int /*<<< orphan*/  SrcIpAddress6; scalar_t__ IsIPv6; int /*<<< orphan*/  RedirectUrl; int /*<<< orphan*/  Loss; int /*<<< orphan*/  Jitter; int /*<<< orphan*/  Delay; scalar_t__ Established; scalar_t__ CheckTcpState; int /*<<< orphan*/  DstMacMask; int /*<<< orphan*/  DstMacAddress; scalar_t__ CheckDstMac; int /*<<< orphan*/  SrcMacMask; int /*<<< orphan*/  SrcMacAddress; scalar_t__ CheckSrcMac; int /*<<< orphan*/  DestUsername; int /*<<< orphan*/  SrcUsername; int /*<<< orphan*/  DestPortEnd; int /*<<< orphan*/  DestPortStart; int /*<<< orphan*/  SrcPortEnd; int /*<<< orphan*/  SrcPortStart; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  Discard; int /*<<< orphan*/  Priority; int /*<<< orphan*/  Active; int /*<<< orphan*/  Note; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  IPV6_ADDR ;
typedef  TYPE_1__ ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddDataEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIp32Ex (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIp6AddrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void SiAccessToPack(PACK *p, ACCESS *a, UINT i, UINT total)
{
	// Validate arguments
	if (p == NULL || a == NULL)
	{
		return;
	}

	PackAddUniStrEx(p, "Note", a->Note, i, total);
	PackAddIntEx(p, "Active", a->Active, i, total);
	PackAddIntEx(p, "Priority", a->Priority, i, total);
	PackAddIntEx(p, "Discard", a->Discard, i, total);
	if (a->IsIPv6)
	{
		PackAddIp32Ex(p, "SrcIpAddress", 0xFDFFFFDF, i, total);
		PackAddIp32Ex(p, "SrcSubnetMask", 0xFFFFFFFF, i, total);
		PackAddIp32Ex(p, "DestIpAddress", 0xFDFFFFDF, i, total);
		PackAddIp32Ex(p, "DestSubnetMask", 0xFFFFFFFF, i, total);
	}
	else
	{
		PackAddIp32Ex(p, "SrcIpAddress", a->SrcIpAddress, i, total);
		PackAddIp32Ex(p, "SrcSubnetMask", a->SrcSubnetMask, i, total);
		PackAddIp32Ex(p, "DestIpAddress", a->DestIpAddress, i, total);
		PackAddIp32Ex(p, "DestSubnetMask", a->DestSubnetMask, i, total);
	}
	PackAddIntEx(p, "Protocol", a->Protocol, i, total);
	PackAddIntEx(p, "SrcPortStart", a->SrcPortStart, i, total);
	PackAddIntEx(p, "SrcPortEnd", a->SrcPortEnd, i, total);
	PackAddIntEx(p, "DestPortStart", a->DestPortStart, i, total);
	PackAddIntEx(p, "DestPortEnd", a->DestPortEnd, i, total);
	PackAddStrEx(p, "SrcUsername", a->SrcUsername, i, total);
	PackAddStrEx(p, "DestUsername", a->DestUsername, i, total);
	PackAddBoolEx(p, "CheckSrcMac", a->CheckSrcMac, i, total);
	PackAddDataEx(p, "SrcMacAddress", a->SrcMacAddress, sizeof(a->SrcMacAddress), i, total);
	PackAddDataEx(p, "SrcMacMask", a->SrcMacMask, sizeof(a->SrcMacMask), i, total);
	PackAddBoolEx(p, "CheckDstMac", a->CheckDstMac, i, total);
	PackAddDataEx(p, "DstMacAddress", a->DstMacAddress, sizeof(a->DstMacAddress), i, total);
	PackAddDataEx(p, "DstMacMask", a->DstMacMask, sizeof(a->DstMacMask), i, total);
	PackAddBoolEx(p, "CheckTcpState", a->CheckTcpState, i, total);
	PackAddBoolEx(p, "Established", a->Established, i, total);
	PackAddIntEx(p, "Delay", a->Delay, i, total);
	PackAddIntEx(p, "Jitter", a->Jitter, i, total);
	PackAddIntEx(p, "Loss", a->Loss, i, total);
	PackAddStrEx(p, "RedirectUrl", a->RedirectUrl, i, total);
	PackAddBoolEx(p, "IsIPv6", a->IsIPv6, i, total);
	if (a->IsIPv6)
	{
		PackAddIp6AddrEx(p, "SrcIpAddress6", &a->SrcIpAddress6, i, total);
		PackAddIp6AddrEx(p, "SrcSubnetMask6", &a->SrcSubnetMask6, i, total);
		PackAddIp6AddrEx(p, "DestIpAddress6", &a->DestIpAddress6, i, total);
		PackAddIp6AddrEx(p, "DestSubnetMask6", &a->DestSubnetMask6, i, total);
	}
	else
	{
		IPV6_ADDR zero;

		Zero(&zero, sizeof(zero));

		PackAddIp6AddrEx(p, "SrcIpAddress6", &zero, i, total);
		PackAddIp6AddrEx(p, "SrcSubnetMask6", &zero, i, total);
		PackAddIp6AddrEx(p, "DestIpAddress6", &zero, i, total);
		PackAddIp6AddrEx(p, "DestSubnetMask6", &zero, i, total);
	}
}