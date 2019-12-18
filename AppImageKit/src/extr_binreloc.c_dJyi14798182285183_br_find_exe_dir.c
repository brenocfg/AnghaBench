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
 char* br_dirname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * exe ; 
 char* strdup (char const*) ; 

char *
br_find_exe_dir (const char *default_dir)
{
	if (exe == NULL) {
		/* BinReloc not initialized. */
		if (default_dir != NULL)
			return strdup (default_dir);
		else
			return NULL;
	}

	return br_dirname (exe);
}