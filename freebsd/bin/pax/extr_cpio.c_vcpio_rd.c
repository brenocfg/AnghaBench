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
typedef  scalar_t__ dev_t ;
struct TYPE_8__ {int st_mode; int st_size; void* st_rdev; void* st_dev; scalar_t__ st_nlink; void* st_mtime; void* st_atime; void* st_ctime; scalar_t__ st_gid; scalar_t__ st_uid; scalar_t__ st_ino; } ;
struct TYPE_10__ {long pad; int nlen; char* ln_name; TYPE_1__ sb; scalar_t__ ln_nlen; scalar_t__ crc; } ;
struct TYPE_9__ {int /*<<< orphan*/  c_namesize; int /*<<< orphan*/  c_chksum; int /*<<< orphan*/  c_rmin; int /*<<< orphan*/  c_rmaj; int /*<<< orphan*/  c_min; int /*<<< orphan*/  c_maj; int /*<<< orphan*/  c_nlink; int /*<<< orphan*/  c_filesize; int /*<<< orphan*/  c_mtime; int /*<<< orphan*/  c_gid; int /*<<< orphan*/  c_uid; int /*<<< orphan*/  c_mode; int /*<<< orphan*/  c_ino; } ;
typedef  TYPE_2__ HD_VCPIO ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
 int C_IFMT ; 
 int C_ISLNK ; 
 int /*<<< orphan*/  HEX ; 
 void* TODEV (scalar_t__,scalar_t__) ; 
 long VCPIO_PAD (int) ; 
 scalar_t__ asc_ul (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ asc_uqd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int com_rd (TYPE_3__*) ; 
 scalar_t__ crc_id (char*,int) ; 
 scalar_t__ docrc ; 
 scalar_t__ rd_ln_nm (TYPE_3__*) ; 
 scalar_t__ rd_nm (TYPE_3__*,int) ; 
 scalar_t__ rd_skip (void*) ; 
 scalar_t__ vcpio_id (char*,int) ; 

int
vcpio_rd(ARCHD *arcn, char *buf)
{
	HD_VCPIO *hd;
	dev_t devminor;
	dev_t devmajor;
	int nsz;

	/*
	 * during the id phase it was determined if we were using CRC, use the
	 * proper id routine.
	 */
	if (docrc) {
		if (crc_id(buf, sizeof(HD_VCPIO)) < 0)
			return(-1);
	} else {
		if (vcpio_id(buf, sizeof(HD_VCPIO)) < 0)
			return(-1);
	}

	hd = (HD_VCPIO *)buf;
	arcn->pad = 0L;

	/*
	 * extract the hex ascii fields from the header
	 */
	arcn->sb.st_ino = (ino_t)asc_ul(hd->c_ino, sizeof(hd->c_ino), HEX);
	arcn->sb.st_mode = (mode_t)asc_ul(hd->c_mode, sizeof(hd->c_mode), HEX);
	arcn->sb.st_uid = (uid_t)asc_ul(hd->c_uid, sizeof(hd->c_uid), HEX);
	arcn->sb.st_gid = (gid_t)asc_ul(hd->c_gid, sizeof(hd->c_gid), HEX);
#ifdef NET2_STAT
	arcn->sb.st_mtime = (time_t)asc_ul(hd->c_mtime,sizeof(hd->c_mtime),HEX);
#else
	arcn->sb.st_mtime = (time_t)asc_uqd(hd->c_mtime,sizeof(hd->c_mtime),HEX);
#endif
	arcn->sb.st_ctime = arcn->sb.st_atime = arcn->sb.st_mtime;
#ifdef NET2_STAT
	arcn->sb.st_size = (off_t)asc_ul(hd->c_filesize,
	    sizeof(hd->c_filesize), HEX);
#else
	arcn->sb.st_size = (off_t)asc_uqd(hd->c_filesize,
	    sizeof(hd->c_filesize), HEX);
#endif
	arcn->sb.st_nlink = (nlink_t)asc_ul(hd->c_nlink, sizeof(hd->c_nlink),
	    HEX);
	devmajor = (dev_t)asc_ul(hd->c_maj, sizeof(hd->c_maj), HEX);
	devminor = (dev_t)asc_ul(hd->c_min, sizeof(hd->c_min), HEX);
	arcn->sb.st_dev = TODEV(devmajor, devminor);
	devmajor = (dev_t)asc_ul(hd->c_rmaj, sizeof(hd->c_maj), HEX);
	devminor = (dev_t)asc_ul(hd->c_rmin, sizeof(hd->c_min), HEX);
	arcn->sb.st_rdev = TODEV(devmajor, devminor);
	arcn->crc = asc_ul(hd->c_chksum, sizeof(hd->c_chksum), HEX);

	/*
	 * check the length of the file name, if ok read it in, return -1 if
	 * bogus
	 */
	if ((nsz = (int)asc_ul(hd->c_namesize,sizeof(hd->c_namesize),HEX)) < 2)
		return(-1);
	arcn->nlen = nsz - 1;
	if (rd_nm(arcn, nsz) < 0)
		return(-1);

	/*
	 * skip padding. header + filename is aligned to 4 byte boundaries
	 */
	if (rd_skip((off_t)(VCPIO_PAD(sizeof(HD_VCPIO) + nsz))) < 0)
		return(-1);

	/*
	 * if not a link (or a file with no data), calculate pad size (for
	 * padding which follows the file data), clear the link name and return
	 */
	if (((arcn->sb.st_mode&C_IFMT) != C_ISLNK)||(arcn->sb.st_size == 0)) {
		/*
		 * we have a valid header (not a link)
		 */
		arcn->ln_nlen = 0;
		arcn->ln_name[0] = '\0';
		arcn->pad = VCPIO_PAD(arcn->sb.st_size);
		return(com_rd(arcn));
	}

	/*
	 * read in the link name and skip over the padding
	 */
	if ((rd_ln_nm(arcn) < 0) ||
	    (rd_skip((off_t)(VCPIO_PAD(arcn->sb.st_size))) < 0))
		return(-1);

	/*
	 * we have a valid header (with a link)
	 */
	return(com_rd(arcn));
}