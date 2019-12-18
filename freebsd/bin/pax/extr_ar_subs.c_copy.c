#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_mtime; scalar_t__ st_ctime; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  dirbuf ;
struct TYPE_18__ {scalar_t__ st_mtime; scalar_t__ st_ctime; } ;
struct TYPE_19__ {char* name; int nlen; scalar_t__ type; char* org_name; TYPE_1__ sb; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 scalar_t__ Dflag ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PAXPATHLEN ; 
 scalar_t__ PAX_CTG ; 
 scalar_t__ PAX_HLK ; 
 scalar_t__ PAX_HRG ; 
 scalar_t__ PAX_REG ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ Yflag ; 
 scalar_t__ Zflag ; 
 int /*<<< orphan*/  ar_close () ; 
 scalar_t__ chk_lnk (TYPE_2__*) ; 
 int chk_same (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_file (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  cp_start () ; 
 int cross_lnk (TYPE_2__*) ; 
 scalar_t__ dir_start () ; 
 char* dirptr ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  file_close (TYPE_2__*,int) ; 
 int file_creat (TYPE_2__*) ; 
 int /*<<< orphan*/  flcnt ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftree_chk () ; 
 int /*<<< orphan*/  ftree_notsel () ; 
 int /*<<< orphan*/  ftree_sel (TYPE_2__*) ; 
 scalar_t__ ftree_start () ; 
 scalar_t__ iflag ; 
 int l_strncpy (char*,char*,int) ; 
 scalar_t__ lflag ; 
 int /*<<< orphan*/  listf ; 
 int lnk_creat (TYPE_2__*) ; 
 scalar_t__ lnk_start () ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int mod_name (TYPE_2__*) ; 
 scalar_t__ name_start () ; 
 scalar_t__ next_file (TYPE_2__*) ; 
 int node_creat (TYPE_2__*) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paxwarn (int,char*,char*) ; 
 int /*<<< orphan*/  proc_dir () ; 
 int /*<<< orphan*/  purg_lnk (TYPE_2__*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdfile_close (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  s_mask ; 
 scalar_t__ sel_chk (TYPE_2__*) ; 
 scalar_t__ set_dest (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ uflag ; 
 scalar_t__ vflag ; 
 int vfpart ; 

void
copy(void)
{
	ARCHD *arcn;
	int res;
	int fddest;
	char *dest_pt;
	int dlen;
	int drem;
	int fdsrc = -1;
	struct stat sb;
	ARCHD archd;
	char dirbuf[PAXPATHLEN+1];

	arcn = &archd;
	/*
	 * set up the destination dir path and make sure it is a directory. We
	 * make sure we have a trailing / on the destination
	 */
	dlen = l_strncpy(dirbuf, dirptr, sizeof(dirbuf) - 1);
	dest_pt = dirbuf + dlen;
	if (*(dest_pt-1) != '/') {
		*dest_pt++ = '/';
		++dlen;
	}
	*dest_pt = '\0';
	drem = PAXPATHLEN - dlen;

	if (stat(dirptr, &sb) < 0) {
		syswarn(1, errno, "Cannot access destination directory %s",
			dirptr);
		return;
	}
	if (!S_ISDIR(sb.st_mode)) {
		paxwarn(1, "Destination is not a directory %s", dirptr);
		return;
	}

	/*
	 * start up the hard link table; file traversal routines and the
	 * modification time and access mode database
	 */
	if ((lnk_start() < 0) || (ftree_start() < 0) || (dir_start() < 0))
		return;

	/*
	 * When we are doing interactive rename, we store the mapping of names
	 * so we can fix up hard links files later in the archive.
	 */
	if (iflag && (name_start() < 0))
		return;

	/*
	 * set up to cp file trees
	 */
	cp_start();

	/*
	 * while there are files to archive, process them
	 */
	while (next_file(arcn) == 0) {
		fdsrc = -1;

		/*
		 * check if this file meets user specified options
		 */
		if (sel_chk(arcn) != 0) {
			ftree_notsel();
			continue;
		}

		/*
		 * if there is already a file in the destination directory with
		 * the same name and it is newer, skip the one stored on the
		 * archive.
		 * NOTE: this test is done BEFORE name modifications as
		 * specified by pax. this can be confusing to the user who
		 * might expect the test to be done on an existing file AFTER
		 * the name mod. In honesty the pax spec is probably flawed in
		 * this respect
		 */
		if (uflag || Dflag) {
			/*
			 * create the destination name
			 */
			if (*(arcn->name) == '/')
				res = 1;
			else
				res = 0;
			if ((arcn->nlen - res) > drem) {
				paxwarn(1, "Destination pathname too long %s",
					arcn->name);
				continue;
			}
			(void)strncpy(dest_pt, arcn->name + res, drem);
			dirbuf[PAXPATHLEN] = '\0';

			/*
			 * if existing file is same age or newer skip
			 */
			res = lstat(dirbuf, &sb);
			*dest_pt = '\0';

		    	if (res == 0) {
				if (uflag && Dflag) {
					if ((arcn->sb.st_mtime<=sb.st_mtime) &&
			    		    (arcn->sb.st_ctime<=sb.st_ctime))
						continue;
				} else if (Dflag) {
					if (arcn->sb.st_ctime <= sb.st_ctime)
						continue;
				} else if (arcn->sb.st_mtime <= sb.st_mtime)
					continue;
			}
		}

		/*
		 * this file is considered selected. See if this is a hard link
		 * to a previous file; modify the name as requested by the
		 * user; set the final destination.
		 */
		ftree_sel(arcn);
		if ((chk_lnk(arcn) < 0) || ((res = mod_name(arcn)) < 0))
			break;
		if ((res > 0) || (set_dest(arcn, dirbuf, dlen) < 0)) {
			/*
			 * skip file, purge from link table
			 */
			purg_lnk(arcn);
			continue;
		}

		/*
		 * Non standard -Y and -Z flag. When the existing file is
		 * same age or newer skip
		 */
		if ((Yflag || Zflag) && ((lstat(arcn->name, &sb) == 0))) {
			if (Yflag && Zflag) {
				if ((arcn->sb.st_mtime <= sb.st_mtime) &&
				    (arcn->sb.st_ctime <= sb.st_ctime))
					continue;
			} else if (Yflag) {
				if (arcn->sb.st_ctime <= sb.st_ctime)
					continue;
			} else if (arcn->sb.st_mtime <= sb.st_mtime)
				continue;
		}

		if (vflag) {
			(void)fputs(arcn->name, listf);
			vfpart = 1;
		}
		++flcnt;

		/*
		 * try to create a hard link to the src file if requested
		 * but make sure we are not trying to overwrite ourselves.
		 */
		if (lflag)
			res = cross_lnk(arcn);
		else
			res = chk_same(arcn);
		if (res <= 0) {
			if (vflag && vfpart) {
				(void)putc('\n', listf);
				vfpart = 0;
			}
			continue;
		}

		/*
		 * have to create a new file
		 */
		if ((arcn->type != PAX_REG) && (arcn->type != PAX_CTG)) {
			/*
			 * create a link or special file
			 */
			if ((arcn->type == PAX_HLK) || (arcn->type == PAX_HRG))
				res = lnk_creat(arcn);
			else
				res = node_creat(arcn);
			if (res < 0)
				purg_lnk(arcn);
			if (vflag && vfpart) {
				(void)putc('\n', listf);
				vfpart = 0;
			}
			continue;
		}

		/*
		 * have to copy a regular file to the destination directory.
		 * first open source file and then create the destination file
		 */
		if ((fdsrc = open(arcn->org_name, O_RDONLY, 0)) < 0) {
			syswarn(1, errno, "Unable to open %s to read",
			    arcn->org_name);
			purg_lnk(arcn);
			continue;
		}
		if ((fddest = file_creat(arcn)) < 0) {
			rdfile_close(arcn, &fdsrc);
			purg_lnk(arcn);
			continue;
		}

		/*
		 * copy source file data to the destination file
		 */
		cp_file(arcn, fdsrc, fddest);
		file_close(arcn, fddest);
		rdfile_close(arcn, &fdsrc);

		if (vflag && vfpart) {
			(void)putc('\n', listf);
			vfpart = 0;
		}
	}

	/*
	 * restore directory modes and times as required; make sure all
	 * patterns were selected block off signals to avoid chance for
	 * multiple entry into the cleanup code.
	 */
	(void)sigprocmask(SIG_BLOCK, &s_mask, NULL);
	ar_close();
	proc_dir();
	ftree_chk();
}