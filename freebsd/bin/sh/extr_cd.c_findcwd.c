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
 int /*<<< orphan*/  STACKSTRNUL (char*) ; 
 int /*<<< orphan*/  STARTSTACKSTR (char*) ; 
 int /*<<< orphan*/  STPUTC (char,char*) ; 
 int /*<<< orphan*/  STPUTS (char*,char*) ; 
 char STTOPC (char*) ; 
 char STUNPUTC (char*) ; 
 char* curdir ; 
 scalar_t__ equal (char*,char*) ; 
 char* getcomponent (char**) ; 
 char* getpwd2 () ; 
 char* stackblock () ; 
 char* stsavestr (char*) ; 

__attribute__((used)) static char *
findcwd(char *dir)
{
	char *new;
	char *p;
	char *path;

	/*
	 * If our argument is NULL, we don't know the current directory
	 * any more because we traversed a symbolic link or something
	 * we couldn't stat().
	 */
	if (dir == NULL || curdir == NULL)
		return getpwd2();
	path = stsavestr(dir);
	STARTSTACKSTR(new);
	if (*dir != '/') {
		STPUTS(curdir, new);
		if (STTOPC(new) == '/')
			STUNPUTC(new);
	}
	while ((p = getcomponent(&path)) != NULL) {
		if (equal(p, "..")) {
			while (new > stackblock() && (STUNPUTC(new), *new) != '/');
		} else if (*p != '\0' && ! equal(p, ".")) {
			STPUTC('/', new);
			STPUTS(p, new);
		}
	}
	if (new == stackblock())
		STPUTC('/', new);
	STACKSTRNUL(new);
	return stackblock();
}