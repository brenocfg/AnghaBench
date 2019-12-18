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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int FILEBITS ; 
 int R_OK ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int W_OK ; 
 int X_OK ; 
 scalar_t__ access (char*,int) ; 
 int /*<<< orphan*/  add_dir (char*,int,struct stat*,int) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ mkdir (char*,int) ; 
 scalar_t__ pids ; 
 int /*<<< orphan*/  set_ids (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmode (char*,int) ; 
 char* strchr (char*,char) ; 

int
chk_path( char *name, uid_t st_uid, gid_t st_gid)
{
	char *spt = name;
	struct stat sb;
	int retval = -1;

	/*
	 * watch out for paths with nodes stored directly in / (e.g. /bozo)
	 */
	if (*spt == '/')
		++spt;

	for(;;) {
		/*
		 * work forward from the first / and check each part of the path
		 */
		spt = strchr(spt, '/');
		if (spt == NULL)
			break;
		*spt = '\0';

		/*
		 * if it exists we assume it is a directory, it is not within
		 * the spec (at least it seems to read that way) to alter the
		 * file system for nodes NOT EXPLICITLY stored on the archive.
		 * If that assumption is changed, you would test the node here
		 * and figure out how to get rid of it (probably like some
		 * recursive unlink()) or fix up the directory permissions if
		 * required (do an access()).
		 */
		if (lstat(name, &sb) == 0) {
			*(spt++) = '/';
			continue;
		}

		/*
		 * the path fails at this point, see if we can create the
		 * needed directory and continue on
		 */
		if (mkdir(name, S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
			*spt = '/';
			retval = -1;
			break;
		}

		/*
		 * we were able to create the directory. We will tell the
		 * caller that we found something to fix, and it is ok to try
		 * and create the node again.
		 */
		retval = 0;
		if (pids)
			(void)set_ids(name, st_uid, st_gid);

		/*
		 * make sure the user doesn't have some strange umask that
		 * causes this newly created directory to be unusable. We fix
		 * the modes and restore them back to the creation default at
		 * the end of pax
		 */
		if ((access(name, R_OK | W_OK | X_OK) < 0) &&
		    (lstat(name, &sb) == 0)) {
			set_pmode(name, ((sb.st_mode & FILEBITS) | S_IRWXU));
			add_dir(name, spt - name, &sb, 1);
		}
		*(spt++) = '/';
		continue;
	}
	return(retval);
}