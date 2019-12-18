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
 char* br_strndup (char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char*) ; 
 char* strrchr (char const*,char) ; 

char *
br_dirname (const char *path)
{
	char *end, *result;

	if (path == (const char *) NULL)
		return (char *) NULL;

	end = strrchr (path, '/');
	if (end == (const char *) NULL)
		return strdup (".");

	while (end > path && *end == '/')
		end--;
	result = br_strndup (path, end - path + 1);
	if (result[0] == 0) {
		free (result);
		return strdup ("/");
	} else
		return result;
}