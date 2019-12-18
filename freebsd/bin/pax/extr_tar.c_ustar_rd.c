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
typedef  int /*<<< orphan*/  uid_t ;
typedef  void* time_t ;
typedef  void* off_t ;
typedef  scalar_t__ mode_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  scalar_t__ dev_t ;
struct TYPE_5__ {int st_nlink; scalar_t__ st_mode; void* st_size; scalar_t__ st_rdev; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_gid; void* st_mtime; void* st_atime; void* st_ctime; } ;
struct TYPE_7__ {char* org_name; char* name; int nlen; char* ln_name; int ln_nlen; TYPE_1__ sb; void* skip; scalar_t__ pad; int /*<<< orphan*/  type; int /*<<< orphan*/ * pat; } ;
struct TYPE_6__ {char* prefix; char* name; char* gname; char* uname; int typeflag; char* linkname; int /*<<< orphan*/  devminor; int /*<<< orphan*/  devmajor; int /*<<< orphan*/  uid; int /*<<< orphan*/  gid; int /*<<< orphan*/  mtime; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; } ;
typedef  TYPE_2__ HD_USTAR ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
#define  AREGTYPE 136 
 int /*<<< orphan*/  BLKMULT ; 
#define  BLKTYPE 135 
#define  CHRTYPE 134 
#define  CONTTYPE 133 
#define  DIRTYPE 132 
#define  FIFOTYPE 131 
#define  LNKTYPE 130 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  OCT ; 
 int /*<<< orphan*/  PAX_BLK ; 
 int /*<<< orphan*/  PAX_CHR ; 
 int /*<<< orphan*/  PAX_DIR ; 
 int /*<<< orphan*/  PAX_FIF ; 
 int /*<<< orphan*/  PAX_HLK ; 
 int /*<<< orphan*/  PAX_REG ; 
 int /*<<< orphan*/  PAX_SLK ; 
#define  REGTYPE 129 
#define  SYMTYPE 128 
 scalar_t__ S_IFBLK ; 
 scalar_t__ S_IFCHR ; 
 scalar_t__ S_IFDIR ; 
 scalar_t__ S_IFIFO ; 
 scalar_t__ S_IFLNK ; 
 scalar_t__ S_IFREG ; 
 scalar_t__ TAR_PAD (void*) ; 
 scalar_t__ TODEV (scalar_t__,scalar_t__) ; 
 int asc_ul (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ asc_uqd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gid_name (char*,int /*<<< orphan*/ *) ; 
 int l_strncpy (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_name (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ustar_id (char*,int /*<<< orphan*/ ) ; 

int
ustar_rd(ARCHD *arcn, char *buf)
{
	HD_USTAR *hd;
	char *dest;
	int cnt = 0;
	dev_t devmajor;
	dev_t devminor;

	/*
	 * we only get proper sized buffers
	 */
	if (ustar_id(buf, BLKMULT) < 0)
		return(-1);
	arcn->org_name = arcn->name;
	arcn->sb.st_nlink = 1;
	arcn->pat = NULL;
	arcn->nlen = 0;
	hd = (HD_USTAR *)buf;

	/*
	 * see if the filename is split into two parts. if, so joint the parts.
	 * we copy the prefix first and add a / between the prefix and name.
	 */
	dest = arcn->name;
	if (*(hd->prefix) != '\0') {
		cnt = l_strncpy(dest, hd->prefix,
		    MIN(sizeof(hd->prefix), sizeof(arcn->name) - 2));
		dest += cnt;
		*dest++ = '/';
		cnt++;
	}
	/*
	 * ustar format specifies the name may be unterminated
	 * if it fills the entire field.  this also applies to
	 * the prefix and the linkname.
	 */
	arcn->nlen = cnt + l_strncpy(dest, hd->name,
	    MIN(sizeof(hd->name), sizeof(arcn->name) - cnt - 1));
	arcn->name[arcn->nlen] = '\0';

	/*
	 * follow the spec to the letter. we should only have mode bits, strip
	 * off all other crud we may be passed.
	 */
	arcn->sb.st_mode = (mode_t)(asc_ul(hd->mode, sizeof(hd->mode), OCT) &
	    0xfff);
#ifdef NET2_STAT
	arcn->sb.st_size = (off_t)asc_ul(hd->size, sizeof(hd->size), OCT);
	arcn->sb.st_mtime = (time_t)asc_ul(hd->mtime, sizeof(hd->mtime), OCT);
#else
	arcn->sb.st_size = (off_t)asc_uqd(hd->size, sizeof(hd->size), OCT);
	arcn->sb.st_mtime = (time_t)asc_uqd(hd->mtime, sizeof(hd->mtime), OCT);
#endif
	arcn->sb.st_ctime = arcn->sb.st_atime = arcn->sb.st_mtime;

	/*
	 * If we can find the ascii names for gname and uname in the password
	 * and group files we will use the uid's and gid they bind. Otherwise
	 * we use the uid and gid values stored in the header. (This is what
	 * the POSIX spec wants).
	 */
	hd->gname[sizeof(hd->gname) - 1] = '\0';
	if (gid_name(hd->gname, &(arcn->sb.st_gid)) < 0)
		arcn->sb.st_gid = (gid_t)asc_ul(hd->gid, sizeof(hd->gid), OCT);
	hd->uname[sizeof(hd->uname) - 1] = '\0';
	if (uid_name(hd->uname, &(arcn->sb.st_uid)) < 0)
		arcn->sb.st_uid = (uid_t)asc_ul(hd->uid, sizeof(hd->uid), OCT);

	/*
	 * set the defaults, these may be changed depending on the file type
	 */
	arcn->ln_name[0] = '\0';
	arcn->ln_nlen = 0;
	arcn->pad = 0;
	arcn->skip = 0;
	arcn->sb.st_rdev = (dev_t)0;

	/*
	 * set the mode and PAX type according to the typeflag in the header
	 */
	switch(hd->typeflag) {
	case FIFOTYPE:
		arcn->type = PAX_FIF;
		arcn->sb.st_mode |= S_IFIFO;
		break;
	case DIRTYPE:
		arcn->type = PAX_DIR;
		arcn->sb.st_mode |= S_IFDIR;
		arcn->sb.st_nlink = 2;

		/*
		 * Some programs that create ustar archives append a '/'
		 * to the pathname for directories. This clearly violates
		 * ustar specs, but we will silently strip it off anyway.
		 */
		if (arcn->name[arcn->nlen - 1] == '/')
			arcn->name[--arcn->nlen] = '\0';
		break;
	case BLKTYPE:
	case CHRTYPE:
		/*
		 * this type requires the rdev field to be set.
		 */
		if (hd->typeflag == BLKTYPE) {
			arcn->type = PAX_BLK;
			arcn->sb.st_mode |= S_IFBLK;
		} else {
			arcn->type = PAX_CHR;
			arcn->sb.st_mode |= S_IFCHR;
		}
		devmajor = (dev_t)asc_ul(hd->devmajor,sizeof(hd->devmajor),OCT);
		devminor = (dev_t)asc_ul(hd->devminor,sizeof(hd->devminor),OCT);
		arcn->sb.st_rdev = TODEV(devmajor, devminor);
		break;
	case SYMTYPE:
	case LNKTYPE:
		if (hd->typeflag == SYMTYPE) {
			arcn->type = PAX_SLK;
			arcn->sb.st_mode |= S_IFLNK;
		} else {
			arcn->type = PAX_HLK;
			/*
			 * so printing looks better
			 */
			arcn->sb.st_mode |= S_IFREG;
			arcn->sb.st_nlink = 2;
		}
		/*
		 * copy the link name
		 */
		arcn->ln_nlen = l_strncpy(arcn->ln_name, hd->linkname,
		    MIN(sizeof(hd->linkname), sizeof(arcn->ln_name) - 1));
		arcn->ln_name[arcn->ln_nlen] = '\0';
		break;
	case CONTTYPE:
	case AREGTYPE:
	case REGTYPE:
	default:
		/*
		 * these types have file data that follows. Set the skip and
		 * pad fields.
		 */
		arcn->type = PAX_REG;
		arcn->pad = TAR_PAD(arcn->sb.st_size);
		arcn->skip = arcn->sb.st_size;
		arcn->sb.st_mode |= S_IFREG;
		break;
	}
	return(0);
}