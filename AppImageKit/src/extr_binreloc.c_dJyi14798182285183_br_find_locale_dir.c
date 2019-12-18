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
 char* br_find_data_dir (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 

char *
br_find_locale_dir (const char *default_locale_dir)
{
	char *data_dir, *dir;

	data_dir = br_find_data_dir ((const char *) NULL);
	if (data_dir == (char *) NULL) {
		/* BinReloc not initialized. */
		if (default_locale_dir != (const char *) NULL)
			return strdup (default_locale_dir);
		else
			return (char *) NULL;
	}

	dir = br_build_path (data_dir, "locale");
	free (data_dir);
	return dir;
}