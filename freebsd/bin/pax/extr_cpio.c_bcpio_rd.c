#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uid_t ;
typedef  int time_t ;
typedef  int off_t ;
typedef  void* nlink_t ;
typedef  void* mode_t ;
typedef  void* ino_t ;
typedef  void* gid_t ;
typedef  void* dev_t ;
struct TYPE_8__ {int st_mode; int st_mtime; int st_size; int st_ctime; int st_atime; void* st_rdev; void* st_nlink; void* st_gid; void* st_uid; void* st_ino; void* st_dev; } ;
struct TYPE_10__ {long pad; int nlen; char* ln_name; TYPE_1__ sb; scalar_t__ ln_nlen; } ;
struct TYPE_9__ {int /*<<< orphan*/  h_namesize; int /*<<< orphan*/  h_filesize_2; int /*<<< orphan*/  h_filesize_1; int /*<<< orphan*/  h_mtime_2; int /*<<< orphan*/  h_mtime_1; int /*<<< orphan*/  h_rdev; int /*<<< orphan*/  h_nlink; int /*<<< orphan*/  h_gid; int /*<<< orphan*/  h_uid; int /*<<< orphan*/  h_mode; int /*<<< orphan*/  h_ino; int /*<<< orphan*/  h_dev; } ;
typedef  TYPE_2__ HD_BCPIO ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
 long BCPIO_PAD (int) ; 
 int C_IFMT ; 
 int C_ISLNK ; 
 scalar_t__ RSHRT_EXT (int /*<<< orphan*/ ) ; 
 scalar_t__ SHRT_EXT (int /*<<< orphan*/ ) ; 
 scalar_t__ bcpio_id (char*,int) ; 
 int com_rd (TYPE_3__*) ; 
 scalar_t__ rd_ln_nm (TYPE_3__*) ; 
 scalar_t__ rd_nm (TYPE_3__*,int) ; 
 scalar_t__ rd_skip (int) ; 
 scalar_t__ swp_head ; 

int
bcpio_rd(ARCHD *arcn, char *buf)
{
	HD_BCPIO *hd;
	int nsz;

	/*
	 * check the header
	 */
	if (bcpio_id(buf, sizeof(HD_BCPIO)) < 0)
		return(-1);

	arcn->pad = 0L;
	hd = (HD_BCPIO *)buf;
	if (swp_head) {
		/*
		 * header has swapped bytes on 16 bit boundaries
		 */
		arcn->sb.st_dev = (dev_t)(RSHRT_EXT(hd->h_dev));
		arcn->sb.st_ino = (ino_t)(RSHRT_EXT(hd->h_ino));
		arcn->sb.st_mode = (mode_t)(RSHRT_EXT(hd->h_mode));
		arcn->sb.st_uid = (uid_t)(RSHRT_EXT(hd->h_uid));
		arcn->sb.st_gid = (gid_t)(RSHRT_EXT(hd->h_gid));
		arcn->sb.st_nlink = (nlink_t)(RSHRT_EXT(hd->h_nlink));
		arcn->sb.st_rdev = (dev_t)(RSHRT_EXT(hd->h_rdev));
		arcn->sb.st_mtime = (time_t)(RSHRT_EXT(hd->h_mtime_1));
		arcn->sb.st_mtime =  (arcn->sb.st_mtime << 16) |
			((time_t)(RSHRT_EXT(hd->h_mtime_2)));
		arcn->sb.st_size = (off_t)(RSHRT_EXT(hd->h_filesize_1));
		arcn->sb.st_size = (arcn->sb.st_size << 16) |
			((off_t)(RSHRT_EXT(hd->h_filesize_2)));
		nsz = (int)(RSHRT_EXT(hd->h_namesize));
	} else {
		arcn->sb.st_dev = (dev_t)(SHRT_EXT(hd->h_dev));
		arcn->sb.st_ino = (ino_t)(SHRT_EXT(hd->h_ino));
		arcn->sb.st_mode = (mode_t)(SHRT_EXT(hd->h_mode));
		arcn->sb.st_uid = (uid_t)(SHRT_EXT(hd->h_uid));
		arcn->sb.st_gid = (gid_t)(SHRT_EXT(hd->h_gid));
		arcn->sb.st_nlink = (nlink_t)(SHRT_EXT(hd->h_nlink));
		arcn->sb.st_rdev = (dev_t)(SHRT_EXT(hd->h_rdev));
		arcn->sb.st_mtime = (time_t)(SHRT_EXT(hd->h_mtime_1));
		arcn->sb.st_mtime =  (arcn->sb.st_mtime << 16) |
			((time_t)(SHRT_EXT(hd->h_mtime_2)));
		arcn->sb.st_size = (off_t)(SHRT_EXT(hd->h_filesize_1));
		arcn->sb.st_size = (arcn->sb.st_size << 16) |
			((off_t)(SHRT_EXT(hd->h_filesize_2)));
		nsz = (int)(SHRT_EXT(hd->h_namesize));
	}
	arcn->sb.st_ctime = arcn->sb.st_atime = arcn->sb.st_mtime;

	/*
	 * check the file name size, if bogus give up. otherwise read the file
	 * name
	 */
	if (nsz < 2)
		return(-1);
	arcn->nlen = nsz - 1;
	if (rd_nm(arcn, nsz) < 0)
		return(-1);

	/*
	 * header + file name are aligned to 2 byte boundaries, skip if needed
	 */
	if (rd_skip((off_t)(BCPIO_PAD(sizeof(HD_BCPIO) + nsz))) < 0)
		return(-1);

	/*
	 * if not a link (or a file with no data), calculate pad size (for
	 * padding which follows the file data), clear the link name and return
	 */
	if (((arcn->sb.st_mode & C_IFMT) != C_ISLNK)||(arcn->sb.st_size == 0)){
		/*
		 * we have a valid header (not a link)
		 */
		arcn->ln_nlen = 0;
		arcn->ln_name[0] = '\0';
		arcn->pad = BCPIO_PAD(arcn->sb.st_size);
		return(com_rd(arcn));
	}

	if ((rd_ln_nm(arcn) < 0) ||
	    (rd_skip((off_t)(BCPIO_PAD(arcn->sb.st_size))) < 0))
		return(-1);

	/*
	 * we have a valid header (with a link)
	 */
	return(com_rd(arcn));
}