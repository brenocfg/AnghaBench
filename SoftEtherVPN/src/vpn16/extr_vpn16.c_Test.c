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

/* Variables and functions */
 scalar_t__ DiInstallClass (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ InstallNDIDevice (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  Print (char*) ; 

void Test()
{
	char *inf = "c:\\windows\\inf\\other\\Neo_TEST.inf";

	if (DiInstallClass(inf, 0) == OK)
	{
		Print("DiInstallClass Ok.");
		if (InstallNDIDevice("Net", "NeoAdapter_TEST", NULL, NULL) == OK)
		{
			Print("InstallNDIDevice Ok.\n");
		}
		else
		{
			Print("InstallNDIDevice Failed.\n");
		}
	}
	else
	{
		Print("DiInstallClass Failed. ");
	}
}