#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
typedef  void* time_t ;
typedef  void* off_t ;
typedef  scalar_t__ mode_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_5__ {int st_nlink; void* st_size; scalar_t__ st_mode; void* st_mtime; void* st_atime; void* st_ctime; scalar_t__ st_gid; scalar_t__ st_uid; } ;
struct TYPE_7__ {char* org_name; char* name; size_t nlen; size_t ln_nlen; char* ln_name; TYPE_1__ sb; void* skip; scalar_t__ pad; void* type; int /*<<< orphan*/ * pat; } ;
struct TYPE_6__ {int linkflag; int /*<<< orphan*/  linkname; int /*<<< orphan*/  mtime; int /*<<< orphan*/  size; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ HD_TAR ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
#define  AREGTYPE 132 
 int /*<<< orphan*/  BLKMULT ; 
#define  DIRTYPE 131 
#define  LNKTYPE 130 
 scalar_t__ MIN (int,int) ; 
 int /*<<< orphan*/  OCT ; 
 void* PAX_DIR ; 
 void* PAX_HLK ; 
 void* PAX_REG ; 
 void* PAX_SLK ; 
#define  REGTYPE 129 
#define  SYMTYPE 128 
 scalar_t__ S_IFDIR ; 
 scalar_t__ S_IFLNK ; 
 scalar_t__ S_IFREG ; 
 scalar_t__ TAR_PAD (void*) ; 
 int asc_ul (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ asc_uqd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* l_strncpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tar_id (char*,int /*<<< orphan*/ ) ; 

int
tar_rd(ARCHD *arcn, char *buf)
{
	HD_TAR *hd;
	char *pt;

	/*
	 * we only get proper sized buffers passed to us
	 */
	if (tar_id(buf, BLKMULT) < 0)
		return(-1);
	arcn->org_name = arcn->name;
	arcn->sb.st_nlink = 1;
	arcn->pat = NULL;

	/*
	 * copy out the name and values in the stat buffer
	 */
	hd = (HD_TAR *)buf;
	/*
	 * old tar format specifies the name always be null-terminated,
	 * but let's be robust to broken archives.
	 * the same applies to handling links below.
	 */
	arcn->nlen = l_strncpy(arcn->name, hd->name,
	    MIN(sizeof(hd->name), sizeof(arcn->name)) - 1);
	arcn->name[arcn->nlen] = '\0';
	arcn->sb.st_mode = (mode_t)(asc_ul(hd->mode,sizeof(hd->mode),OCT) &
	    0xfff);
	arcn->sb.st_uid = (uid_t)asc_ul(hd->uid, sizeof(hd->uid), OCT);
	arcn->sb.st_gid = (gid_t)asc_ul(hd->gid, sizeof(hd->gid), OCT);
#ifdef NET2_STAT
	arcn->sb.st_size = (off_t)asc_ul(hd->size, sizeof(hd->size), OCT);
	arcn->sb.st_mtime = (time_t)asc_ul(hd->mtime, sizeof(hd->mtime), OCT);
#else
	arcn->sb.st_size = (off_t)asc_uqd(hd->size, sizeof(hd->size), OCT);
	arcn->sb.st_mtime = (time_t)asc_uqd(hd->mtime, sizeof(hd->mtime), OCT);
#endif
	arcn->sb.st_ctime = arcn->sb.st_atime = arcn->sb.st_mtime;

	/*
	 * have to look at the last character, it may be a '/' and that is used
	 * to encode this as a directory
	 */
	pt = &(arcn->name[arcn->nlen - 1]);
	arcn->pad = 0;
	arcn->skip = 0;
	switch(hd->linkflag) {
	case SYMTYPE:
		/*
		 * symbolic link, need to get the link name and set the type in
		 * the st_mode so -v printing will look correct.
		 */
		arcn->type = PAX_SLK;
		arcn->ln_nlen = l_strncpy(arcn->ln_name, hd->linkname,
		    MIN(sizeof(hd->linkname), sizeof(arcn->ln_name)) - 1);
		arcn->ln_name[arcn->ln_nlen] = '\0';
		arcn->sb.st_mode |= S_IFLNK;
		break;
	case LNKTYPE:
		/*
		 * hard link, need to get the link name, set the type in the
		 * st_mode and st_nlink so -v printing will look better.
		 */
		arcn->type = PAX_HLK;
		arcn->sb.st_nlink = 2;
		arcn->ln_nlen = l_strncpy(arcn->ln_name, hd->linkname,
		    MIN(sizeof(hd->linkname), sizeof(arcn->ln_name)) - 1);
		arcn->ln_name[arcn->ln_nlen] = '\0';

		/*
		 * no idea of what type this thing really points at, but
		 * we set something for printing only.
		 */
		arcn->sb.st_mode |= S_IFREG;
		break;
	case DIRTYPE:
		/*
		 * It is a directory, set the mode for -v printing
		 */
		arcn->type = PAX_DIR;
		arcn->sb.st_mode |= S_IFDIR;
		arcn->sb.st_nlink = 2;
		arcn->ln_name[0] = '\0';
		arcn->ln_nlen = 0;
		break;
	case AREGTYPE:
	case REGTYPE:
	default:
		/*
		 * If we have a trailing / this is a directory and NOT a file.
		 */
		arcn->ln_name[0] = '\0';
		arcn->ln_nlen = 0;
		if (*pt == '/') {
			/*
			 * it is a directory, set the mode for -v printing
			 */
			arcn->type = PAX_DIR;
			arcn->sb.st_mode |= S_IFDIR;
			arcn->sb.st_nlink = 2;
		} else {
			/*
			 * have a file that will be followed by data. Set the
			 * skip value to the size field and calculate the size
			 * of the padding.
			 */
			arcn->type = PAX_REG;
			arcn->sb.st_mode |= S_IFREG;
			arcn->pad = TAR_PAD(arcn->sb.st_size);
			arcn->skip = arcn->sb.st_size;
		}
		break;
	}

	/*
	 * strip off any trailing slash.
	 */
	if (*pt == '/') {
		*pt = '\0';
		--arcn->nlen;
	}
	return(0);
}