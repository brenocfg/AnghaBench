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
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ rmdir (char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static int
rm_path(char *path)
{
	char *p;

	p = path + strlen(path);
	while (--p > path && *p == '/')
		;
	*++p = '\0';
	while ((p = strrchr(path, '/')) != NULL) {
		/* Delete trailing slashes. */
		while (--p >= path && *p == '/')
			;
		*++p = '\0';
		if (p == path)
			break;

		if (rmdir(path) < 0) {
			warn("%s", path);
			return (1);
		}
		if (vflag)
			printf("%s\n", path);
	}

	return (0);
}