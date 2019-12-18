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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  STACKSTRNUL (char*) ; 
 int /*<<< orphan*/  STARTSTACKSTR (char*) ; 
 int /*<<< orphan*/  STPUTC (char,char*) ; 
 int /*<<< orphan*/  STPUTS (char*,char*) ; 
 scalar_t__ chdir (char*) ; 
 scalar_t__ equal (char*,char*) ; 
 char* findcwd (char*) ; 
 char* getcomponent (char**) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  stackblock () ; 
 char* stsavestr (char*) ; 
 int /*<<< orphan*/  updatepwd (char*) ; 

__attribute__((used)) static int
cdlogical(char *dest)
{
	char *p;
	char *q;
	char *component;
	char *path;
	struct stat statb;
	int first;
	int badstat;

	/*
	 *  Check each component of the path. If we find a symlink or
	 *  something we can't stat, clear curdir to force a getcwd()
	 *  next time we get the value of the current directory.
	 */
	badstat = 0;
	path = stsavestr(dest);
	STARTSTACKSTR(p);
	if (*dest == '/') {
		STPUTC('/', p);
		path++;
	}
	first = 1;
	while ((q = getcomponent(&path)) != NULL) {
		if (q[0] == '\0' || (q[0] == '.' && q[1] == '\0'))
			continue;
		if (! first)
			STPUTC('/', p);
		first = 0;
		component = q;
		STPUTS(q, p);
		if (equal(component, ".."))
			continue;
		STACKSTRNUL(p);
		if (lstat(stackblock(), &statb) < 0) {
			badstat = 1;
			break;
		}
	}

	INTOFF;
	if ((p = findcwd(badstat ? NULL : dest)) == NULL || chdir(p) < 0) {
		INTON;
		return (-1);
	}
	updatepwd(p);
	INTON;
	return (0);
}