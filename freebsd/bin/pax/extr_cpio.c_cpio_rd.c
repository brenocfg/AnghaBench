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
typedef  scalar_t__ uid_t ;
typedef  void* time_t ;
typedef  void* off_t ;
typedef  scalar_t__ nlink_t ;
typedef  int mode_t ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ gid_t ;
typedef  void* dev_t ;
struct TYPE_8__ {int st_mode; scalar_t__ st_size; void* st_mtime; void* st_atime; void* st_ctime; void* st_rdev; scalar_t__ st_nlink; scalar_t__ st_gid; scalar_t__ st_uid; scalar_t__ st_ino; void* st_dev; } ;
struct TYPE_10__ {long pad; int nlen; char* ln_name; scalar_t__ ln_nlen; TYPE_1__ sb; } ;
struct TYPE_9__ {int /*<<< orphan*/  c_namesize; int /*<<< orphan*/  c_filesize; int /*<<< orphan*/  c_mtime; int /*<<< orphan*/  c_rdev; int /*<<< orphan*/  c_nlink; int /*<<< orphan*/  c_gid; int /*<<< orphan*/  c_uid; int /*<<< orphan*/  c_mode; int /*<<< orphan*/  c_ino; int /*<<< orphan*/  c_dev; } ;
typedef  TYPE_2__ HD_CPIO ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
 int C_IFMT ; 
 int C_ISLNK ; 
 int /*<<< orphan*/  OCT ; 
 scalar_t__ asc_ul (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ asc_uqd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int com_rd (TYPE_3__*) ; 
 scalar_t__ cpio_id (char*,int) ; 
 scalar_t__ rd_ln_nm (TYPE_3__*) ; 
 scalar_t__ rd_nm (TYPE_3__*,int) ; 

int
cpio_rd(ARCHD *arcn, char *buf)
{
	int nsz;
	HD_CPIO *hd;

	/*
	 * check that this is a valid header, if not return -1
	 */
	if (cpio_id(buf, sizeof(HD_CPIO)) < 0)
		return(-1);
	hd = (HD_CPIO *)buf;

	/*
	 * byte oriented cpio (posix) does not have padding! extract the octal
	 * ascii fields from the header
	 */
	arcn->pad = 0L;
	arcn->sb.st_dev = (dev_t)asc_ul(hd->c_dev, sizeof(hd->c_dev), OCT);
	arcn->sb.st_ino = (ino_t)asc_ul(hd->c_ino, sizeof(hd->c_ino), OCT);
	arcn->sb.st_mode = (mode_t)asc_ul(hd->c_mode, sizeof(hd->c_mode), OCT);
	arcn->sb.st_uid = (uid_t)asc_ul(hd->c_uid, sizeof(hd->c_uid), OCT);
	arcn->sb.st_gid = (gid_t)asc_ul(hd->c_gid, sizeof(hd->c_gid), OCT);
	arcn->sb.st_nlink = (nlink_t)asc_ul(hd->c_nlink, sizeof(hd->c_nlink),
	    OCT);
	arcn->sb.st_rdev = (dev_t)asc_ul(hd->c_rdev, sizeof(hd->c_rdev), OCT);
#ifdef NET2_STAT
	arcn->sb.st_mtime = (time_t)asc_ul(hd->c_mtime, sizeof(hd->c_mtime),
	    OCT);
#else
	arcn->sb.st_mtime = (time_t)asc_uqd(hd->c_mtime, sizeof(hd->c_mtime),
	    OCT);
#endif
	arcn->sb.st_ctime = arcn->sb.st_atime = arcn->sb.st_mtime;
#ifdef NET2_STAT
	arcn->sb.st_size = (off_t)asc_ul(hd->c_filesize,sizeof(hd->c_filesize),
	    OCT);
#else
	arcn->sb.st_size = (off_t)asc_uqd(hd->c_filesize,sizeof(hd->c_filesize),
	    OCT);
#endif

	/*
	 * check name size and if valid, read in the name of this entry (name
	 * follows header in the archive)
	 */
	if ((nsz = (int)asc_ul(hd->c_namesize,sizeof(hd->c_namesize),OCT)) < 2)
		return(-1);
	arcn->nlen = nsz - 1;
	if (rd_nm(arcn, nsz) < 0)
		return(-1);

	if (((arcn->sb.st_mode&C_IFMT) != C_ISLNK)||(arcn->sb.st_size == 0)) {
		/*
	 	 * no link name to read for this file
	 	 */
		arcn->ln_nlen = 0;
		arcn->ln_name[0] = '\0';
		return(com_rd(arcn));
	}

	/*
	 * check link name size and read in the link name. Link names are
	 * stored like file data.
	 */
	if (rd_ln_nm(arcn) < 0)
		return(-1);

	/*
	 * we have a valid header (with a link)
	 */
	return(com_rd(arcn));
}