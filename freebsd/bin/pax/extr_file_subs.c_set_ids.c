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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  NM_PAX ; 
 int /*<<< orphan*/  argv0 ; 
 scalar_t__ errno ; 
 scalar_t__ geteuid () ; 
 scalar_t__ lchown (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syswarn (int,scalar_t__,char*,char*) ; 
 scalar_t__ vflag ; 

int
set_ids(char *fnm, uid_t uid, gid_t gid)
{
	if (lchown(fnm, uid, gid) < 0) {
		/*
		 * ignore EPERM unless in verbose mode or being run by root.
		 * if running as pax, POSIX requires a warning.
		 */
		if (strcmp(NM_PAX, argv0) == 0 || errno != EPERM || vflag ||
		    geteuid() == 0)
			syswarn(1, errno, "Unable to set file uid/gid of %s",
			    fnm);
		return(-1);
	}
	return(0);
}