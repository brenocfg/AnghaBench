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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  DestSubnetMask6; int /*<<< orphan*/  DestIpAddress6; int /*<<< orphan*/  SrcSubnetMask6; int /*<<< orphan*/  SrcIpAddress6; void* IsIPv6; int /*<<< orphan*/  RedirectUrl; void* UniqueId; void* Loss; void* Jitter; void* Delay; void* Established; void* CheckTcpState; int /*<<< orphan*/  DstMacMask; int /*<<< orphan*/  DstMacAddress; void* CheckDstMac; int /*<<< orphan*/  SrcMacMask; int /*<<< orphan*/  SrcMacAddress; void* CheckSrcMac; int /*<<< orphan*/  DestUsername; int /*<<< orphan*/  SrcUsername; void* DestPortEnd; void* DestPortStart; void* SrcPortEnd; void* SrcPortStart; void* Protocol; void* DestSubnetMask; void* DestIpAddress; void* SrcSubnetMask; void* SrcIpAddress; void* Discard; void* Priority; void* Active; int /*<<< orphan*/  Note; void* Id; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ ACCESS ;

/* Variables and functions */
 void* PackGetBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackGetDataEx2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* PackGetIp32Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackGetIp6AddrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackGetUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcAccessEx(ACCESS *a, PACK *p, UINT index)
{
	// Validate arguments
	if (a == NULL || p == NULL)
	{
		return;
	}

	Zero(a, sizeof(ACCESS));
	a->Id = PackGetIntEx(p, "Id", index);
	PackGetUniStrEx(p, "Note", a->Note, sizeof(a->Note), index);
	a->Active = PackGetBoolEx(p, "Active", index);
	a->Priority = PackGetIntEx(p, "Priority", index);
	a->Discard = PackGetBoolEx(p, "Discard", index);
	a->SrcIpAddress = PackGetIp32Ex(p, "SrcIpAddress", index);
	a->SrcSubnetMask = PackGetIp32Ex(p, "SrcSubnetMask", index);
	a->DestIpAddress = PackGetIp32Ex(p, "DestIpAddress", index);
	a->DestSubnetMask = PackGetIp32Ex(p, "DestSubnetMask", index);
	a->Protocol = PackGetIntEx(p, "Protocol", index);
	a->SrcPortStart = PackGetIntEx(p, "SrcPortStart", index);
	a->SrcPortEnd = PackGetIntEx(p, "SrcPortEnd", index);
	a->DestPortStart = PackGetIntEx(p, "DestPortStart", index);
	a->DestPortEnd = PackGetIntEx(p, "DestPortEnd", index);
	//a->SrcUsernameHash = PackGetIntEx(p, "SrcUsernameHash", index);
	PackGetStrEx(p, "SrcUsername", a->SrcUsername, sizeof(a->SrcUsername), index);
	//a->DestUsernameHash = PackGetIntEx(p, "DestUsernameHash", index);
	PackGetStrEx(p, "DestUsername", a->DestUsername, sizeof(a->DestUsername), index);
	a->CheckSrcMac = PackGetBoolEx(p, "CheckSrcMac", index);
	PackGetDataEx2(p, "SrcMacAddress", a->SrcMacAddress, sizeof(a->SrcMacAddress), index);
	PackGetDataEx2(p, "SrcMacMask", a->SrcMacMask, sizeof(a->SrcMacMask), index);
	a->CheckDstMac = PackGetBoolEx(p, "CheckDstMac", index);
	PackGetDataEx2(p, "DstMacAddress", a->DstMacAddress, sizeof(a->DstMacAddress), index);
	PackGetDataEx2(p, "DstMacMask", a->DstMacMask, sizeof(a->DstMacMask), index);
	a->CheckTcpState = PackGetBoolEx(p, "CheckTcpState", index);
	a->Established = PackGetBoolEx(p, "Established", index);
	a->Delay = PackGetIntEx(p, "Delay", index);
	a->Jitter = PackGetIntEx(p, "Jitter", index);
	a->Loss = PackGetIntEx(p, "Loss", index);
	a->IsIPv6 = PackGetBoolEx(p, "IsIPv6", index);
	a->UniqueId = PackGetIntEx(p, "UniqueId", index);
	PackGetStrEx(p, "RedirectUrl", a->RedirectUrl, sizeof(a->RedirectUrl), index);
	if (a->IsIPv6)
	{
		PackGetIp6AddrEx(p, "SrcIpAddress6", &a->SrcIpAddress6, index);
		PackGetIp6AddrEx(p, "SrcSubnetMask6", &a->SrcSubnetMask6, index);
		PackGetIp6AddrEx(p, "DestIpAddress6", &a->DestIpAddress6, index);
		PackGetIp6AddrEx(p, "DestSubnetMask6", &a->DestSubnetMask6, index);
	}
}