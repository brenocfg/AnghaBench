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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int Active; int Discard; int IsIPv6; char* SrcUsername; char* DestUsername; int CheckSrcMac; int CheckDstMac; int CheckTcpState; int Established; char* RedirectUrl; int /*<<< orphan*/  Loss; int /*<<< orphan*/  Jitter; int /*<<< orphan*/  Delay; int /*<<< orphan*/  DstMacMask; int /*<<< orphan*/  DstMacAddress; int /*<<< orphan*/  SrcMacMask; int /*<<< orphan*/  SrcMacAddress; int /*<<< orphan*/  DestPortEnd; int /*<<< orphan*/  DestPortStart; int /*<<< orphan*/  SrcPortEnd; int /*<<< orphan*/  SrcPortStart; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  DestSubnetMask6; int /*<<< orphan*/  DestIpAddress6; int /*<<< orphan*/  SrcSubnetMask6; int /*<<< orphan*/  SrcIpAddress6; int /*<<< orphan*/  DestSubnetMask; int /*<<< orphan*/  DestIpAddress; int /*<<< orphan*/  SrcSubnetMask; int /*<<< orphan*/  SrcIpAddress; int /*<<< orphan*/  Priority; int /*<<< orphan*/  Note; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddIp32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddIp6Addr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  CfgAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MacToStr (char*,int,int /*<<< orphan*/ ) ; 

void SiWriteHubAccessCfg(FOLDER *f, ACCESS *a)
{
	// Validate arguments
	if (f == NULL || a == NULL)
	{
		return;
	}

	CfgAddUniStr(f, "Note", a->Note);
	CfgAddBool(f, "Active", a->Active);
	CfgAddInt(f, "Priority", a->Priority);
	CfgAddBool(f, "Discard", a->Discard);
	CfgAddBool(f, "IsIPv6", a->IsIPv6);

	if (a->IsIPv6 == false)
	{
		CfgAddIp32(f, "SrcIpAddress", a->SrcIpAddress);
		CfgAddIp32(f, "SrcSubnetMask", a->SrcSubnetMask);
		CfgAddIp32(f, "DestIpAddress", a->DestIpAddress);
		CfgAddIp32(f, "DestSubnetMask", a->DestSubnetMask);
	}
	else
	{
		CfgAddIp6Addr(f, "SrcIpAddress6", &a->SrcIpAddress6);
		CfgAddIp6Addr(f, "SrcSubnetMask6", &a->SrcSubnetMask6);
		CfgAddIp6Addr(f, "DestIpAddress6", &a->DestIpAddress6);
		CfgAddIp6Addr(f, "DestSubnetMask6", &a->DestSubnetMask6);
	}

	CfgAddInt(f, "Protocol", a->Protocol);
	CfgAddInt(f, "SrcPortStart", a->SrcPortStart);
	CfgAddInt(f, "SrcPortEnd", a->SrcPortEnd);
	CfgAddInt(f, "DestPortStart", a->DestPortStart);
	CfgAddInt(f, "DestPortEnd", a->DestPortEnd);
	CfgAddStr(f, "SrcUsername", a->SrcUsername);
	CfgAddStr(f, "DestUsername", a->DestUsername);
	CfgAddBool(f, "CheckSrcMac", a->CheckSrcMac);

	if (a->CheckSrcMac)
	{
		char tmp[MAX_PATH];

		MacToStr(tmp, sizeof(tmp), a->SrcMacAddress);
		CfgAddStr(f, "SrcMacAddress", tmp);

		MacToStr(tmp, sizeof(tmp), a->SrcMacMask);
		CfgAddStr(f, "SrcMacMask", tmp);
	}

	CfgAddBool(f, "CheckDstMac", a->CheckDstMac);

	if (a->CheckDstMac)
	{
		char tmp[MAX_PATH];

		MacToStr(tmp, sizeof(tmp), a->DstMacAddress);
		CfgAddStr(f, "DstMacAddress", tmp);

		MacToStr(tmp, sizeof(tmp), a->DstMacMask);
		CfgAddStr(f, "DstMacMask", tmp);
	}

	CfgAddBool(f, "CheckTcpState", a->CheckTcpState);
	CfgAddBool(f, "Established", a->Established);

	CfgAddStr(f, "RedirectUrl", a->RedirectUrl);

	CfgAddInt(f, "Delay", a->Delay);
	CfgAddInt(f, "Jitter", a->Jitter);
	CfgAddInt(f, "Loss", a->Loss);
}