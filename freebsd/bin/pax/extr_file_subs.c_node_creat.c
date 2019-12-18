#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; } ;
typedef  int mode_t ;
struct TYPE_5__ {int st_mode; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_rdev; } ;
struct TYPE_4__ {int type; TYPE_3__ sb; int /*<<< orphan*/  name; int /*<<< orphan*/  nlen; int /*<<< orphan*/  ln_name; } ;
typedef  TYPE_1__ ARCHD ;

/* Variables and functions */
 int FILEBITS ; 
 int /*<<< orphan*/  NM_CPIO ; 
#define  PAX_BLK 137 
#define  PAX_CHR 136 
#define  PAX_CTG 135 
#define  PAX_DIR 134 
#define  PAX_FIF 133 
#define  PAX_HLK 132 
#define  PAX_HRG 131 
#define  PAX_REG 130 
#define  PAX_SCK 129 
#define  PAX_SLK 128 
 int R_OK ; 
 int SETBITS ; 
 int S_IFBLK ; 
 int S_IFCHR ; 
 int S_IRWXU ; 
 int W_OK ; 
 int X_OK ; 
 scalar_t__ access (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  argv0 ; 
 scalar_t__ chk_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int mkdir (int /*<<< orphan*/ ,int) ; 
 int mkfifo (int /*<<< orphan*/ ,int) ; 
 int mknod (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nodirs ; 
 scalar_t__ patime ; 
 int /*<<< orphan*/  paxwarn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pids ; 
 scalar_t__ pmode ; 
 scalar_t__ pmtime ; 
 int /*<<< orphan*/  set_ftime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_ids (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmode (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syswarn (int,int,char*,int /*<<< orphan*/ ) ; 
 int unlnk_exist (int /*<<< orphan*/ ,int) ; 

int
node_creat(ARCHD *arcn)
{
	int res;
	int ign = 0;
	int oerrno;
	int pass = 0;
	mode_t file_mode;
	struct stat sb;

	/*
	 * create node based on type, if that fails try to unlink the node and
	 * try again. finally check the path and try again. As noted in the
	 * file and link creation routines, this method seems to exhibit the
	 * best performance in general use workloads.
	 */
	file_mode = arcn->sb.st_mode & FILEBITS;

	for (;;) {
		switch(arcn->type) {
		case PAX_DIR:
			res = mkdir(arcn->name, file_mode);
			if (ign)
				res = 0;
			break;
		case PAX_CHR:
			file_mode |= S_IFCHR;
			res = mknod(arcn->name, file_mode, arcn->sb.st_rdev);
			break;
		case PAX_BLK:
			file_mode |= S_IFBLK;
			res = mknod(arcn->name, file_mode, arcn->sb.st_rdev);
			break;
		case PAX_FIF:
			res = mkfifo(arcn->name, file_mode);
			break;
		case PAX_SCK:
			/*
			 * Skip sockets, operation has no meaning under BSD
			 */
			paxwarn(0,
			    "%s skipped. Sockets cannot be copied or extracted",
			    arcn->name);
			return(-1);
		case PAX_SLK:
			res = symlink(arcn->ln_name, arcn->name);
			break;
		case PAX_CTG:
		case PAX_HLK:
		case PAX_HRG:
		case PAX_REG:
		default:
			/*
			 * we should never get here
			 */
			paxwarn(0, "%s has an unknown file type, skipping",
				arcn->name);
			return(-1);
		}

		/*
		 * if we were able to create the node break out of the loop,
		 * otherwise try to unlink the node and try again. if that
		 * fails check the full path and try a final time.
		 */
		if (res == 0)
			break;

		/*
		 * we failed to make the node
		 */
		oerrno = errno;
		if ((ign = unlnk_exist(arcn->name, arcn->type)) < 0)
			return(-1);

		if (++pass <= 1)
			continue;

		if (nodirs || chk_path(arcn->name,arcn->sb.st_uid,arcn->sb.st_gid) < 0) {
			syswarn(1, oerrno, "Could not create: %s", arcn->name);
			return(-1);
		}
	}

	/*
	 * we were able to create the node. set uid/gid, modes and times
	 */
	if (pids)
		res = set_ids(arcn->name, arcn->sb.st_uid, arcn->sb.st_gid);
	else
		res = 0;

	/*
	 * IMPORTANT SECURITY NOTE:
	 * if not preserving mode or we cannot set uid/gid, then PROHIBIT any
	 * set uid/gid bits
	 */
	if (!pmode || res)
		arcn->sb.st_mode &= ~(SETBITS);
	if (pmode)
		set_pmode(arcn->name, arcn->sb.st_mode);

	if (arcn->type == PAX_DIR && strcmp(NM_CPIO, argv0) != 0) {
		/*
		 * Dirs must be processed again at end of extract to set times
		 * and modes to agree with those stored in the archive. However
		 * to allow extract to continue, we may have to also set owner
		 * rights. This allows nodes in the archive that are children
		 * of this directory to be extracted without failure. Both time
		 * and modes will be fixed after the entire archive is read and
		 * before pax exits.
		 */
		if (access(arcn->name, R_OK | W_OK | X_OK) < 0) {
			if (lstat(arcn->name, &sb) < 0) {
				syswarn(0, errno,"Could not access %s (stat)",
				    arcn->name);
				set_pmode(arcn->name,file_mode | S_IRWXU);
			} else {
				/*
				 * We have to add rights to the dir, so we make
				 * sure to restore the mode. The mode must be
				 * restored AS CREATED and not as stored if
				 * pmode is not set.
				 */
				set_pmode(arcn->name,
				    ((sb.st_mode & FILEBITS) | S_IRWXU));
				if (!pmode)
					arcn->sb.st_mode = sb.st_mode;
			}

			/*
			 * we have to force the mode to what was set here,
			 * since we changed it from the default as created.
			 */
			add_dir(arcn->name, arcn->nlen, &(arcn->sb), 1);
		} else if (pmode || patime || pmtime)
			add_dir(arcn->name, arcn->nlen, &(arcn->sb), 0);
	}

	if (patime || pmtime)
		set_ftime(arcn->name, arcn->sb.st_mtime, arcn->sb.st_atime, 0);
	return(0);
}