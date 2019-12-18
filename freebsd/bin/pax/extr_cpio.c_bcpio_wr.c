#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int time_t ;
typedef  int off_t ;
typedef  scalar_t__ nlink_t ;
typedef  scalar_t__ mode_t ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ gid_t ;
typedef  scalar_t__ dev_t ;
struct TYPE_6__ {scalar_t__ st_rdev; int st_size; int st_dev; int st_ino; int st_mode; int st_uid; int st_gid; int st_nlink; int st_mtime; } ;
struct TYPE_8__ {int type; long pad; int ln_nlen; int nlen; char* name; char* ln_name; int /*<<< orphan*/  org_name; TYPE_1__ sb; } ;
struct TYPE_7__ {char* h_filesize_1; char* h_filesize_2; char* h_dev; char* h_ino; char* h_mode; char* h_uid; char* h_gid; char* h_nlink; char* h_rdev; char* h_mtime_1; char* h_mtime_2; char* h_namesize; void** h_magic; } ;
typedef  TYPE_2__ HD_BCPIO ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
 scalar_t__ BCPIO_MASK ; 
 long BCPIO_PAD (int) ; 
 void* CHR_WR_0 (int) ; 
 void* CHR_WR_1 (int) ; 
 void* CHR_WR_2 (int) ; 
 void* CHR_WR_3 (int) ; 
 int MAGIC ; 
 int PAX_BLK ; 
 int PAX_CHR ; 
#define  PAX_CTG 131 
#define  PAX_HRG 130 
#define  PAX_REG 129 
#define  PAX_SLK 128 
 scalar_t__ SHRT_EXT (char*) ; 
 scalar_t__ map_dev (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paxwarn (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wr_rdbuf (char*,int) ; 
 scalar_t__ wr_skip (int) ; 

int
bcpio_wr(ARCHD *arcn)
{
	HD_BCPIO *hd;
	int nsz;
	HD_BCPIO hdblk;
	off_t t_offt;
	int t_int;
	time_t t_timet;

	/*
	 * check and repair truncated device and inode fields in the cpio
	 * header
	 */
	if (map_dev(arcn, (u_long)BCPIO_MASK, (u_long)BCPIO_MASK) < 0)
		return(-1);

	if ((arcn->type != PAX_BLK) && (arcn->type != PAX_CHR))
		arcn->sb.st_rdev = 0;
	hd = &hdblk;

	switch(arcn->type) {
	case PAX_CTG:
	case PAX_REG:
	case PAX_HRG:
		/*
		 * caller will copy file data to the archive. tell him how
		 * much to pad.
		 */
		arcn->pad = BCPIO_PAD(arcn->sb.st_size);
		hd->h_filesize_1[0] = CHR_WR_0(arcn->sb.st_size);
		hd->h_filesize_1[1] = CHR_WR_1(arcn->sb.st_size);
		hd->h_filesize_2[0] = CHR_WR_2(arcn->sb.st_size);
		hd->h_filesize_2[1] = CHR_WR_3(arcn->sb.st_size);
		t_offt = (off_t)(SHRT_EXT(hd->h_filesize_1));
		t_offt = (t_offt<<16) | ((off_t)(SHRT_EXT(hd->h_filesize_2)));
		if (arcn->sb.st_size != t_offt) {
			paxwarn(1,"File is too large for bcpio format %s",
			    arcn->org_name);
			return(1);
		}
		break;
	case PAX_SLK:
		/*
		 * no file data for the caller to process, the file data has
		 * the size of the link
		 */
		arcn->pad = 0L;
		hd->h_filesize_1[0] = CHR_WR_0(arcn->ln_nlen);
		hd->h_filesize_1[1] = CHR_WR_1(arcn->ln_nlen);
		hd->h_filesize_2[0] = CHR_WR_2(arcn->ln_nlen);
		hd->h_filesize_2[1] = CHR_WR_3(arcn->ln_nlen);
		t_int = (int)(SHRT_EXT(hd->h_filesize_1));
		t_int = (t_int << 16) | ((int)(SHRT_EXT(hd->h_filesize_2)));
		if (arcn->ln_nlen != t_int)
			goto out;
		break;
	default:
		/*
		 * no file data for the caller to process
		 */
		arcn->pad = 0L;
		hd->h_filesize_1[0] = (char)0;
		hd->h_filesize_1[1] = (char)0;
		hd->h_filesize_2[0] = (char)0;
		hd->h_filesize_2[1] = (char)0;
		break;
	}

	/*
	 * build up the rest of the fields
	 */
	hd->h_magic[0] = CHR_WR_2(MAGIC);
	hd->h_magic[1] = CHR_WR_3(MAGIC);
	hd->h_dev[0] = CHR_WR_2(arcn->sb.st_dev);
	hd->h_dev[1] = CHR_WR_3(arcn->sb.st_dev);
	if (arcn->sb.st_dev != (dev_t)(SHRT_EXT(hd->h_dev)))
		goto out;
	hd->h_ino[0] = CHR_WR_2(arcn->sb.st_ino);
	hd->h_ino[1] = CHR_WR_3(arcn->sb.st_ino);
	if (arcn->sb.st_ino != (ino_t)(SHRT_EXT(hd->h_ino)))
		goto out;
	hd->h_mode[0] = CHR_WR_2(arcn->sb.st_mode);
	hd->h_mode[1] = CHR_WR_3(arcn->sb.st_mode);
	if (arcn->sb.st_mode != (mode_t)(SHRT_EXT(hd->h_mode)))
		goto out;
	hd->h_uid[0] = CHR_WR_2(arcn->sb.st_uid);
	hd->h_uid[1] = CHR_WR_3(arcn->sb.st_uid);
	if (arcn->sb.st_uid != (uid_t)(SHRT_EXT(hd->h_uid)))
		goto out;
	hd->h_gid[0] = CHR_WR_2(arcn->sb.st_gid);
	hd->h_gid[1] = CHR_WR_3(arcn->sb.st_gid);
	if (arcn->sb.st_gid != (gid_t)(SHRT_EXT(hd->h_gid)))
		goto out;
	hd->h_nlink[0] = CHR_WR_2(arcn->sb.st_nlink);
	hd->h_nlink[1] = CHR_WR_3(arcn->sb.st_nlink);
	if (arcn->sb.st_nlink != (nlink_t)(SHRT_EXT(hd->h_nlink)))
		goto out;
	hd->h_rdev[0] = CHR_WR_2(arcn->sb.st_rdev);
	hd->h_rdev[1] = CHR_WR_3(arcn->sb.st_rdev);
	if (arcn->sb.st_rdev != (dev_t)(SHRT_EXT(hd->h_rdev)))
		goto out;
	hd->h_mtime_1[0] = CHR_WR_0(arcn->sb.st_mtime);
	hd->h_mtime_1[1] = CHR_WR_1(arcn->sb.st_mtime);
	hd->h_mtime_2[0] = CHR_WR_2(arcn->sb.st_mtime);
	hd->h_mtime_2[1] = CHR_WR_3(arcn->sb.st_mtime);
	t_timet = (time_t)(SHRT_EXT(hd->h_mtime_1));
	t_timet =  (t_timet << 16) | ((time_t)(SHRT_EXT(hd->h_mtime_2)));
	if (arcn->sb.st_mtime != t_timet)
		goto out;
	nsz = arcn->nlen + 1;
	hd->h_namesize[0] = CHR_WR_2(nsz);
	hd->h_namesize[1] = CHR_WR_3(nsz);
	if (nsz != (int)(SHRT_EXT(hd->h_namesize)))
		goto out;

	/*
	 * write the header, the file name and padding as required.
	 */
	if ((wr_rdbuf((char *)&hdblk, (int)sizeof(HD_BCPIO)) < 0) ||
	    (wr_rdbuf(arcn->name, nsz) < 0) ||
	    (wr_skip((off_t)(BCPIO_PAD(sizeof(HD_BCPIO) + nsz))) < 0)) {
		paxwarn(1, "Could not write bcpio header for %s", arcn->org_name);
		return(-1);
	}

	/*
	 * if we have file data, tell the caller we are done
	 */
	if ((arcn->type == PAX_CTG) || (arcn->type == PAX_REG) ||
	    (arcn->type == PAX_HRG))
		return(0);

	/*
	 * if we are not a link, tell the caller we are done, go to next file
	 */
	if (arcn->type != PAX_SLK)
		return(1);

	/*
	 * write the link name, tell the caller we are done.
	 */
	if ((wr_rdbuf(arcn->ln_name, arcn->ln_nlen) < 0) ||
	    (wr_skip((off_t)(BCPIO_PAD(arcn->ln_nlen))) < 0)) {
		paxwarn(1,"Could not write bcpio link name for %s",arcn->org_name);
		return(-1);
	}
	return(1);

    out:
	/*
	 * header field is out of range
	 */
	paxwarn(1,"Bcpio header field is too small for file %s", arcn->org_name);
	return(1);
}