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
struct TYPE_8__ {scalar_t__ Build; int Supported; int /*<<< orphan*/  Path; int /*<<< orphan*/  VpnCMgrExeFileName; } ;
struct TYPE_9__ {scalar_t__ VpnInstallBuild; TYPE_1__ x86; int /*<<< orphan*/  SettingPath; int /*<<< orphan*/  NormalMode; } ;
typedef  TYPE_2__ VI_SETTING ;
struct TYPE_10__ {int NumTokens; char** Token; } ;
typedef  TYPE_3__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_3__*) ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 scalar_t__ MsIsX64 () ; 
 TYPE_3__* ParseToken (char*,char*) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int StartWith (char*,char*) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ToBool (char*) ; 
 void* ToInt (char*) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool ViLoadInfFromBuf(VI_SETTING *set, BUF *buf)
{
	bool ret;
	if (set == NULL || buf == NULL)
	{
		return false;
	}

	Zero(set, sizeof(VI_SETTING));

	SeekBuf(buf, 0, 0);
	while (true)
	{
		char *tmp = CfgReadNextLine(buf);
		TOKEN_LIST *tokens;

		if (tmp == NULL)
		{
			break;
		}

		tokens = ParseToken(tmp, " \t");

		if (tokens != NULL)
		{
			if (tokens->NumTokens >= 2)
			{
				if (StartWith(tokens->Token[0], "#") == false
					|| StartWith(tokens->Token[0], "//") == false)
				{
					char *name, *value;
					name = tokens->Token[0];
					value = tokens->Token[1];

					if (StrCmpi(name, "VpnInstallBuild") == 0)
					{
						set->VpnInstallBuild = ToInt(value);
					}
					else if (StrCmpi(name, "NormalMode") == 0)
					{
						set->NormalMode = ToBool(value);
					}
					else if (StrCmpi(name, "VpnSettingPath") == 0)
					{
						StrCpy(set->SettingPath, sizeof(set->SettingPath), value);
					}
					else if (StrCmpi(name, "VpnClientBuild") == 0)
					{
						set->x86.Build = ToInt(value);
					}
					else if (StrCmpi(name, "VpnClientPath") == 0)
					{
						StrCpy(set->x86.Path, sizeof(set->x86.Path), value);
					}
				}
			}
			FreeToken(tokens);
		}

		Free(tmp);
	}

	ret = false;

	StrCpy(set->x86.VpnCMgrExeFileName, sizeof(set->x86.VpnCMgrExeFileName), (MsIsX64() ? "vpncmgr_x64.exe" : "vpncmgr.exe"));

	if (set->VpnInstallBuild != 0)
	{
		if (set->x86.Build != 0 && IsEmptyStr(set->x86.Path) == false)
		{
			set->x86.Supported = true;
			ret = true;
		}
	}

	return ret;
}