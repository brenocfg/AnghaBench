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
 int FALSE ; 
 int /*<<< orphan*/  MAX_FILES_PER_DIR ; 
 int TRUE ; 
 int /*<<< orphan*/  Util_splitpath (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dir_i ; 
 scalar_t__ dir_n ; 
 int /*<<< orphan*/  dir_path ; 
 int /*<<< orphan*/  mcDir ; 
 scalar_t__ mcGetDir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcSync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int Atari_OpenDir(const char *filename)
{
	// TODO: support other devices
	if (strncmp(filename, "mc0:/", 5) != 0)
		return FALSE;
	dir_n = mcGetDir(0, 0, filename + 4, 0 /* followup flag */, MAX_FILES_PER_DIR, mcDir);
	mcSync(0,NULL,&dir_n);
	if (dir_n < 0)
		return FALSE;
	dir_i = 0;
	// XXX: does it know (and needs to know) that "mc0:/" is a root directory?
	Util_splitpath(filename, dir_path, NULL);
	return TRUE;
}