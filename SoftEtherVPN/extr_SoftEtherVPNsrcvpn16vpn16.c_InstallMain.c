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
typedef  int /*<<< orphan*/  sysdir ;

/* Variables and functions */
 scalar_t__ DiInstallClass (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetDirFromPath (char*,char*) ; 
 int /*<<< orphan*/  GetSystemDirectory (char*,int) ; 
 scalar_t__ InstallNDIDevice (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IsFile (char*) ; 
 int MAX_PATH ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  Print (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int strlen (char*) ; 

void InstallMain(char *name)
{
	char sysdir[MAX_PATH];
	char windir[MAX_PATH];
	char infdir[MAX_PATH];
	char otherdir[MAX_PATH];
	char infname[MAX_PATH];
	char deviceid[MAX_PATH];
	char sysname[MAX_PATH];
	if (name == NULL)
	{
		return;
	}
	if (strlen(name) == 0 || strlen(name) >= 5)
	{
		return;
	}

	GetSystemDirectory(sysdir, sizeof(sysdir));

	GetDirFromPath(windir, sysdir);

	sprintf(infdir, "%s\\inf", windir);

	sprintf(otherdir, "%s\\other", infdir);

	sprintf(infname, "%s\\Neo_%s.inf", infdir, name);

	sprintf(sysname, "%s\\Neo_%s.sys", sysdir, name);

	sprintf(deviceid, "NeoAdapter_%s", name);

	if (IsFile(infname) == FALSE)
	{
		Print("Failed to open %s.", infname);
		return;
	}
	if (IsFile(sysname) == FALSE)
	{
		Print("Failed to open %s.", sysname);
		return;
	}

	if (DiInstallClass(infname, 0) != OK)
	{
		Print("Failed to register %s.\n", infname);
		return;
	}

	if (InstallNDIDevice("Net", deviceid, NULL, NULL) != OK)
	{
		return;
	}
}