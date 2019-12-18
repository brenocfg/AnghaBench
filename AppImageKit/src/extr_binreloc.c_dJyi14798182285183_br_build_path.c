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
 char* br_strcat (char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t strlen (char const*) ; 

char *
br_build_path (const char *dir, const char *file)
{
	char *dir2, *result;
	size_t len;
	int must_free = 0;

	len = strlen (dir);
	if (len > 0 && dir[len - 1] != '/') {
		dir2 = br_strcat (dir, "/");
		must_free = 1;
	} else
		dir2 = (char *) dir;

	result = br_strcat (dir2, file);
	if (must_free)
		free (dir2);
	return result;
}