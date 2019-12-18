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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  a ;
struct TYPE_4__ {int IsIPv6; char* SrcUsername; char* DestUsername; int CheckSrcMac; int CheckDstMac; char* RedirectUrl; void* Loss; void* Jitter; void* Delay; void* Established; void* CheckTcpState; int /*<<< orphan*/  DstMacMask; int /*<<< orphan*/  DstMacAddress; int /*<<< orphan*/  SrcMacMask; int /*<<< orphan*/  SrcMacAddress; void* DestPortEnd; void* DestPortStart; void* SrcPortEnd; void* SrcPortStart; void* Protocol; int /*<<< orphan*/  DestSubnetMask6; int /*<<< orphan*/  DestIpAddress6; int /*<<< orphan*/  SrcSubnetMask6; int /*<<< orphan*/  SrcIpAddress6; void* DestSubnetMask; void* DestIpAddress; void* SrcSubnetMask; void* SrcIpAddress; void* Discard; void* Priority; void* Active; int /*<<< orphan*/  Note; } ;
typedef  int /*<<< orphan*/  HUB ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/  AddAccessList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ CfgGetByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 void* CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetIp32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetIp6Addr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  CfgGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HUB_ACCESSLIST_DELAY_MAX ; 
 int /*<<< orphan*/  HUB_ACCESSLIST_JITTER_MAX ; 
 int /*<<< orphan*/  HUB_ACCESSLIST_LOSS_MAX ; 
 void* MAKESURE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int StrToMac (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void SiLoadHubAccessCfg(HUB *h, FOLDER *f)
{
	ACCESS a;
	char tmp[MAX_PATH];
	// Validate arguments
	if (h == NULL || f == NULL)
	{
		return;
	}

	Zero(&a, sizeof(a));

	CfgGetUniStr(f, "Note", a.Note, sizeof(a.Note));
	a.Active = CfgGetBool(f, "Active");
	a.Priority = CfgGetInt(f, "Priority");
	a.Discard = CfgGetBool(f, "Discard");
	a.IsIPv6 = CfgGetBool(f, "IsIPv6");

	if (a.IsIPv6 == false)
	{
		a.SrcIpAddress = CfgGetIp32(f, "SrcIpAddress");
		a.SrcSubnetMask = CfgGetIp32(f, "SrcSubnetMask");
		a.DestIpAddress = CfgGetIp32(f, "DestIpAddress");
		a.DestSubnetMask = CfgGetIp32(f, "DestSubnetMask");
	}
	else
	{
		CfgGetIp6Addr(f, "SrcIpAddress6", &a.SrcIpAddress6);
		CfgGetIp6Addr(f, "SrcSubnetMask6", &a.SrcSubnetMask6);
		CfgGetIp6Addr(f, "DestIpAddress6", &a.DestIpAddress6);
		CfgGetIp6Addr(f, "DestSubnetMask6", &a.DestSubnetMask6);
	}

	a.Protocol = CfgGetInt(f, "Protocol");
	a.SrcPortStart = CfgGetInt(f, "SrcPortStart");
	a.SrcPortEnd = CfgGetInt(f, "SrcPortEnd");
	a.DestPortStart = CfgGetInt(f, "DestPortStart");
	a.DestPortEnd = CfgGetInt(f, "DestPortEnd");
	CfgGetStr(f, "SrcUsername", a.SrcUsername, sizeof(a.SrcUsername));
	CfgGetStr(f, "DestUsername", a.DestUsername, sizeof(a.DestUsername));
	a.CheckSrcMac = CfgGetBool(f, "CheckSrcMac");

	if (CfgGetByte(f, "SrcMacAddress", a.SrcMacAddress, sizeof(a.SrcMacAddress)) == 0)
	{
		CfgGetStr(f, "SrcMacAddress", tmp, sizeof(tmp));
		if (StrToMac(a.SrcMacAddress, tmp) == false)
		{
			a.CheckSrcMac = false;
		}
	}

	if (CfgGetByte(f, "SrcMacMask", a.SrcMacMask, sizeof(a.SrcMacMask)) == 0)
	{
		CfgGetStr(f, "SrcMacMask", tmp, sizeof(tmp));
		if (StrToMac(a.SrcMacMask, tmp) == false)
		{
			a.CheckSrcMac = false;
		}
	}

	a.CheckDstMac = CfgGetBool(f, "CheckDstMac");

	if (CfgGetByte(f, "DstMacAddress", a.DstMacAddress, sizeof(a.DstMacAddress)) == 0)
	{
		CfgGetStr(f, "DstMacAddress", tmp, sizeof(tmp));
		if (StrToMac(a.DstMacAddress, tmp) == false)
		{
			a.CheckDstMac = false;
		}
	}

	if (CfgGetByte(f, "DstMacMask", a.DstMacMask, sizeof(a.DstMacMask)) == 0)
	{
		CfgGetStr(f, "DstMacMask", tmp, sizeof(tmp));
		if (StrToMac(a.DstMacMask, tmp) == false)
		{
			a.CheckDstMac = false;
		}
	}

	a.CheckTcpState = CfgGetBool(f, "CheckTcpState");
	a.Established = CfgGetBool(f, "Established");
	a.Delay = MAKESURE(CfgGetInt(f, "Delay"), 0, HUB_ACCESSLIST_DELAY_MAX);
	a.Jitter = MAKESURE(CfgGetInt(f, "Jitter"), 0, HUB_ACCESSLIST_JITTER_MAX);
	a.Loss = MAKESURE(CfgGetInt(f, "Loss"), 0, HUB_ACCESSLIST_LOSS_MAX);

	CfgGetStr(f, "RedirectUrl", a.RedirectUrl, sizeof(a.RedirectUrl));

	AddAccessList(h, &a);
}