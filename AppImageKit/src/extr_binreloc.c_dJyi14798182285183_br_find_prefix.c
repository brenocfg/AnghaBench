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
 char* br_dirname (char*) ; 
 char* exe ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 

char *
br_find_prefix (const char *default_prefix)
{
	char *dir1, *dir2;

	if (exe == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_prefix != (const char *) NULL)
			return strdup (default_prefix);
		else
			return (char *) NULL;
	}

	dir1 = br_dirname (exe);
	dir2 = br_dirname (dir1);
	free (dir1);
	return dir2;
}