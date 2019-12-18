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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int Supported; int CurrentInstalled; int /*<<< orphan*/  CurrentInstalledPathW; scalar_t__ CurrentInstalledBuild; } ;
typedef  TYPE_1__ VI_SETTING_ARCH ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 scalar_t__ MsRegReadIntEx2 (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/ * MsRegReadStrEx2W (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  REG_LOCAL_MACHINE ; 
 int /*<<< orphan*/  SW_REG_KEY ; 
 scalar_t__ UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void ViLoadCurrentInstalledStatusForArch(VI_SETTING_ARCH *a)
{
	char tmp[MAX_SIZE];
	UINT build;
	wchar_t *dir;
	// Validate arguments
	if (a == NULL)
	{
		return;
	}
	if (a->Supported == false)
	{
		// Unsupported
		return;
	}

	// Read from the registry
	Format(tmp, sizeof(tmp), "%s\\%s", SW_REG_KEY, "vpnclient");

	build = MsRegReadIntEx2(REG_LOCAL_MACHINE, tmp, "InstalledBuild", false, true);

	dir = MsRegReadStrEx2W(REG_LOCAL_MACHINE, tmp, "InstalledDir", false, true);

	if (build == 0 || UniIsEmptyStr(dir))
	{
		// Not installed
		a->CurrentInstalled = false;
	}
	else
	{
		// Installed
		a->CurrentInstalled = true;
		a->CurrentInstalledBuild = build;

		UniStrCpy(a->CurrentInstalledPathW, sizeof(a->CurrentInstalledPathW), dir);
	}

	Free(dir);
}