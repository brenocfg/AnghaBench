#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_6__ {int st_mode; scalar_t__ st_size; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct TYPE_8__ {int fts_info; int /*<<< orphan*/  fts_path; TYPE_1__* fts_statp; TYPE_1__ fts_statb; int /*<<< orphan*/  fts_errno; } ;
struct TYPE_7__ {int ln_nlen; char* ln_name; size_t nlen; char* name; int /*<<< orphan*/  org_name; int /*<<< orphan*/  type; TYPE_1__ sb; scalar_t__ skip; scalar_t__ pad; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
#define  FTS_D 145 
#define  FTS_DC 144 
#define  FTS_DEFAULT 143 
#define  FTS_DNR 142 
#define  FTS_DP 141 
#define  FTS_ERR 140 
#define  FTS_F 139 
#define  FTS_NS 138 
#define  FTS_NSOK 137 
#define  FTS_SL 136 
#define  FTS_SLNONE 135 
 int /*<<< orphan*/  PAXPATHLEN ; 
 int /*<<< orphan*/  PAX_BLK ; 
 int /*<<< orphan*/  PAX_CHR ; 
 int /*<<< orphan*/  PAX_DIR ; 
 int /*<<< orphan*/  PAX_FIF ; 
 int /*<<< orphan*/  PAX_REG ; 
 int /*<<< orphan*/  PAX_SCK ; 
 int /*<<< orphan*/  PAX_SLK ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 int /*<<< orphan*/  add_atdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_4__* ftent ; 
 scalar_t__ ftree_arg () ; 
 scalar_t__ ftree_skip ; 
 TYPE_4__* fts_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftsp ; 
 int /*<<< orphan*/  get_atdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t l_strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  paxwarn (int,char*,int /*<<< orphan*/ ) ; 
 int readlink (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ftime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  tflag ; 

int
next_file(ARCHD *arcn)
{
	int cnt;
	time_t atime;
	time_t mtime;

	/*
	 * ftree_sel() might have set the ftree_skip flag if the user has the
	 * -n option and a file was selected from this file arg tree. (-n says
	 * only one member is matched for each pattern) ftree_skip being 1
	 * forces us to go to the next arg now.
	 */
	if (ftree_skip) {
		/*
		 * clear and go to next arg
		 */
		ftree_skip = 0;
		if (ftree_arg() < 0)
			return(-1);
	}

	/*
	 * loop until we get a valid file to process
	 */
	for(;;) {
		if ((ftent = fts_read(ftsp)) == NULL) {
			/*
			 * out of files in this tree, go to next arg, if none
			 * we are done
			 */
			if (ftree_arg() < 0)
				return(-1);
			continue;
		}

		/*
		 * handle each type of fts_read() flag
		 */
		switch(ftent->fts_info) {
		case FTS_D:
		case FTS_DEFAULT:
		case FTS_F:
		case FTS_SL:
		case FTS_SLNONE:
			/*
			 * these are all ok
			 */
			break;
		case FTS_DP:
			/*
			 * already saw this directory. If the user wants file
			 * access times reset, we use this to restore the
			 * access time for this directory since this is the
			 * last time we will see it in this file subtree
			 * remember to force the time (this is -t on a read
			 * directory, not a created directory).
			 */
#			ifdef NET2_FTS
			if (!tflag || (get_atdir(ftent->fts_statb.st_dev,
			    ftent->fts_statb.st_ino, &mtime, &atime) < 0))
#			else
			if (!tflag || (get_atdir(ftent->fts_statp->st_dev,
			    ftent->fts_statp->st_ino, &mtime, &atime) < 0))
#			endif
				continue;
			set_ftime(ftent->fts_path, mtime, atime, 1);
			continue;
		case FTS_DC:
			/*
			 * fts claims a file system cycle
			 */
			paxwarn(1,"File system cycle found at %s",ftent->fts_path);
			continue;
		case FTS_DNR:
#			ifdef NET2_FTS
			syswarn(1, errno,
#			else
			syswarn(1, ftent->fts_errno,
#			endif
			    "Unable to read directory %s", ftent->fts_path);
			continue;
		case FTS_ERR:
#			ifdef NET2_FTS
			syswarn(1, errno,
#			else
			syswarn(1, ftent->fts_errno,
#			endif
			    "File system traversal error");
			continue;
		case FTS_NS:
		case FTS_NSOK:
#			ifdef NET2_FTS
			syswarn(1, errno,
#			else
			syswarn(1, ftent->fts_errno,
#			endif
			    "Unable to access %s", ftent->fts_path);
			continue;
		}

		/*
		 * ok got a file tree node to process. copy info into arcn
		 * structure (initialize as required)
		 */
		arcn->skip = 0;
		arcn->pad = 0;
		arcn->ln_nlen = 0;
		arcn->ln_name[0] = '\0';
#		ifdef NET2_FTS
		arcn->sb = ftent->fts_statb;
#		else
		arcn->sb = *(ftent->fts_statp);
#		endif

		/*
		 * file type based set up and copy into the arcn struct
		 * SIDE NOTE:
		 * we try to reset the access time on all files and directories
		 * we may read when the -t flag is specified. files are reset
		 * when we close them after copying. we reset the directories
		 * when we are done with their file tree (we also clean up at
		 * end in case we cut short a file tree traversal). However
		 * there is no way to reset access times on symlinks.
		 */
		switch(S_IFMT & arcn->sb.st_mode) {
		case S_IFDIR:
			arcn->type = PAX_DIR;
			if (!tflag)
				break;
			add_atdir(ftent->fts_path, arcn->sb.st_dev,
			    arcn->sb.st_ino, arcn->sb.st_mtime,
			    arcn->sb.st_atime);
			break;
		case S_IFCHR:
			arcn->type = PAX_CHR;
			break;
		case S_IFBLK:
			arcn->type = PAX_BLK;
			break;
		case S_IFREG:
			/*
			 * only regular files with have data to store on the
			 * archive. all others will store a zero length skip.
			 * the skip field is used by pax for actual data it has
			 * to read (or skip over).
			 */
			arcn->type = PAX_REG;
			arcn->skip = arcn->sb.st_size;
			break;
		case S_IFLNK:
			arcn->type = PAX_SLK;
			/*
			 * have to read the symlink path from the file
			 */
			if ((cnt = readlink(ftent->fts_path, arcn->ln_name,
			    PAXPATHLEN - 1)) < 0) {
				syswarn(1, errno, "Unable to read symlink %s",
				    ftent->fts_path);
				continue;
			}
			/*
			 * set link name length, watch out readlink does not
			 * always NUL terminate the link path
			 */
			arcn->ln_name[cnt] = '\0';
			arcn->ln_nlen = cnt;
			break;
		case S_IFSOCK:
			/*
			 * under BSD storing a socket is senseless but we will
			 * let the format specific write function make the
			 * decision of what to do with it.
			 */
			arcn->type = PAX_SCK;
			break;
		case S_IFIFO:
			arcn->type = PAX_FIF;
			break;
		}
		break;
	}

	/*
	 * copy file name, set file name length
	 */
	arcn->nlen = l_strncpy(arcn->name, ftent->fts_path, sizeof(arcn->name) - 1);
	arcn->name[arcn->nlen] = '\0';
	arcn->org_name = ftent->fts_path;
	return(0);
}