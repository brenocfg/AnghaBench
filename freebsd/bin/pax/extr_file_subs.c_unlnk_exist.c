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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int PAX_DIR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ kflag ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ rmdir (char*) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ unlink (char*) ; 

int
unlnk_exist(char *name, int type)
{
	struct stat sb;

	/*
	 * the file does not exist, or -k we are done
	 */
	if (lstat(name, &sb) < 0)
		return(0);
	if (kflag)
		return(-1);

	if (S_ISDIR(sb.st_mode)) {
		/*
		 * try to remove a directory, if it fails and we were going to
		 * create a directory anyway, tell the caller (return a 1)
		 */
		if (rmdir(name) < 0) {
			if (type == PAX_DIR)
				return(1);
			syswarn(1,errno,"Unable to remove directory %s", name);
			return(-1);
		}
		return(0);
	}

	/*
	 * try to get rid of all non-directory type nodes
	 */
	if (unlink(name) < 0) {
		syswarn(1, errno, "Could not unlink %s", name);
		return(-1);
	}
	return(0);
}