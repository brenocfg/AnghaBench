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
 char* br_build_path (char*,char*) ; 
 char* br_find_prefix (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 

char *
br_find_etc_dir (const char *default_etc_dir)
{
	char *prefix, *dir;

	prefix = br_find_prefix ((const char *) NULL);
	if (prefix == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_etc_dir != (const char *) NULL)
			return strdup (default_etc_dir);
		else
			return (char *) NULL;
	}

	dir = br_build_path (prefix, "etc");
	free (prefix);
	return dir;
}