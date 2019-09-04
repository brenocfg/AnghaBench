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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;

/* Variables and functions */
 char* getcwd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 char* strdup (char*) ; 

char *get_current_dir_name(void) {
	struct stat a, b;
	char *res = getenv("PWD");
	if (res && *res && !stat(res, &a) && !stat(".", &b)
	    && (a.st_dev == b.st_dev) && (a.st_ino == b.st_ino))
		return strdup(res);
	return getcwd(0, 0);
}