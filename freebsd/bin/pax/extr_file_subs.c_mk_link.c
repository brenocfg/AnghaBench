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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ chk_path (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ kflag ; 
 scalar_t__ link (char*,char*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  nodirs ; 
 int /*<<< orphan*/  paxwarn (int,char*,char*) ; 
 scalar_t__ rmdir (char*) ; 
 int /*<<< orphan*/  syswarn (int,int,char*,char*,...) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static int
mk_link(char *to, struct stat *to_sb, char *from,
	int ign)
{
	struct stat sb;
	int oerrno;

	/*
	 * if from file exists, it has to be unlinked to make the link. If the
	 * file exists and -k is set, skip it quietly
	 */
	if (lstat(from, &sb) == 0) {
		if (kflag)
			return(0);

		/*
		 * make sure it is not the same file, protect the user
		 */
		if ((to_sb->st_dev==sb.st_dev)&&(to_sb->st_ino == sb.st_ino)) {
			paxwarn(1, "Unable to link file %s to itself", to);
			return(-1);
		}

		/*
		 * try to get rid of the file, based on the type
		 */
		if (S_ISDIR(sb.st_mode)) {
			if (rmdir(from) < 0) {
				syswarn(1, errno, "Unable to remove %s", from);
				return(-1);
			}
		} else if (unlink(from) < 0) {
			if (!ign) {
				syswarn(1, errno, "Unable to remove %s", from);
				return(-1);
			}
			return(1);
		}
	}

	/*
	 * from file is gone (or did not exist), try to make the hard link.
	 * if it fails, check the path and try it again (if chk_path() says to
	 * try again)
	 */
	for (;;) {
		if (link(to, from) == 0)
			break;
		oerrno = errno;
		if (!nodirs && chk_path(from, to_sb->st_uid, to_sb->st_gid) == 0)
			continue;
		if (!ign) {
			syswarn(1, oerrno, "Could not link to %s from %s", to,
			    from);
			return(-1);
		}
		return(1);
	}

	/*
	 * all right the link was made
	 */
	return(0);
}