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
typedef  void* time_t ;
struct timeval {long member_0; long member_1; void* tv_sec; } ;
struct stat {void* st_mtime; void* st_atime; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ lutimes (char*,struct timeval*) ; 
 int /*<<< orphan*/  patime ; 
 int /*<<< orphan*/  pmtime ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,char*) ; 

void
set_ftime(char *fnm, time_t mtime, time_t atime, int frc)
{
	static struct timeval tv[2] = {{0L, 0L}, {0L, 0L}};
	struct stat sb;

	tv[0].tv_sec = atime;
	tv[1].tv_sec = mtime;
	if (!frc && (!patime || !pmtime)) {
		/*
		 * if we are not forcing, only set those times the user wants
		 * set. We get the current values of the times if we need them.
		 */
		if (lstat(fnm, &sb) == 0) {
			if (!patime)
				tv[0].tv_sec = sb.st_atime;
			if (!pmtime)
				tv[1].tv_sec = sb.st_mtime;
		} else
			syswarn(0,errno,"Unable to obtain file stats %s", fnm);
	}

	/*
	 * set the times
	 */
	if (lutimes(fnm, tv) < 0)
		syswarn(1, errno, "Access/modification time set failed on: %s",
		    fnm);
	return;
}