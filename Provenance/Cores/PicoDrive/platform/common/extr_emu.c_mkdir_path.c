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
 int /*<<< orphan*/  lprintf (char*,char*) ; 
 scalar_t__ mkdir (char*,int) ; 
 scalar_t__ plat_is_dir (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static void mkdir_path(char *path_with_reserve, int pos, const char *name)
{
	strcpy(path_with_reserve + pos, name);
	if (plat_is_dir(path_with_reserve))
		return;
	if (mkdir(path_with_reserve, 0777) < 0)
		lprintf("failed to create: %s\n", path_with_reserve);
}