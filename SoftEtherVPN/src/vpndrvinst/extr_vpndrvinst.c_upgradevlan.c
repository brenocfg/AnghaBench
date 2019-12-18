#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  MS_DRIVER_VER ;
typedef  int /*<<< orphan*/  KAKUSHI ;

/* Variables and functions */
 int /*<<< orphan*/  CiInitDriverVerStruct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeKakushi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeWinUi () ; 
 int /*<<< orphan*/ * InitKakushi () ; 
 int /*<<< orphan*/  InitWinUi (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MsIsNt () ; 
 int MsUpgradeVLan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLAN_ADAPTER_NAME_TAG ; 
 int /*<<< orphan*/  VLAN_CONNECTION_NAME ; 
 int /*<<< orphan*/  _II (char*) ; 
 int /*<<< orphan*/  _SS (char*) ; 
 int /*<<< orphan*/  _exit (int) ; 

void upgradevlan(UINT num, char **arg)
{
	bool ok;
	KAKUSHI *k = NULL;
	MS_DRIVER_VER ver;
	if (num < 1)
	{
		return;
	}

	InitWinUi(L"VPN", _SS("DEFAULT_FONT"), _II("DEFAULT_FONT_SIZE"));

	if (MsIsNt())
	{
		k = InitKakushi();
	}

	CiInitDriverVerStruct(&ver);

	ok = MsUpgradeVLan(VLAN_ADAPTER_NAME_TAG, VLAN_CONNECTION_NAME, arg[0], &ver);

	FreeKakushi(k);

	FreeWinUi();

	if (ok == false)
	{
		_exit(1);
	}
	else
	{
		_exit(0);
	}
}