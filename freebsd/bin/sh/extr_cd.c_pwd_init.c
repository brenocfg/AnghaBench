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
 int /*<<< orphan*/  VEXPORT ; 
 int /*<<< orphan*/  ckfree (scalar_t__) ; 
 scalar_t__ curdir ; 
 int /*<<< orphan*/ * getpwd () ; 
 char* lookupvar (char*) ; 
 int /*<<< orphan*/  out2fmt_flush (char*) ; 
 scalar_t__ savestr (char*) ; 
 int /*<<< orphan*/  setvar (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 

void
pwd_init(int warn)
{
	char *pwd;
	struct stat stdot, stpwd;

	pwd = lookupvar("PWD");
	if (pwd && *pwd == '/' && stat(".", &stdot) != -1 &&
	    stat(pwd, &stpwd) != -1 &&
	    stdot.st_dev == stpwd.st_dev &&
	    stdot.st_ino == stpwd.st_ino) {
		if (curdir)
			ckfree(curdir);
		curdir = savestr(pwd);
	}
	if (getpwd() == NULL && warn)
		out2fmt_flush("sh: cannot determine working directory\n");
	setvar("PWD", curdir, VEXPORT);
}