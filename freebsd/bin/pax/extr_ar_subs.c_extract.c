#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct stat {scalar_t__ st_mtime; scalar_t__ st_ctime; } ;
typedef  scalar_t__ off_t ;
struct TYPE_18__ {scalar_t__ st_mtime; scalar_t__ st_ctime; } ;
struct TYPE_20__ {scalar_t__ type; TYPE_2__* pat; scalar_t__ pad; scalar_t__ skip; int /*<<< orphan*/  name; TYPE_1__ sb; } ;
struct TYPE_19__ {int /*<<< orphan*/ * chdname; } ;
struct TYPE_17__ {scalar_t__ (* options ) () ;scalar_t__ (* st_rd ) () ;int (* rd_data ) (TYPE_3__*,int,scalar_t__*) ;int /*<<< orphan*/  (* end_rd ) () ;} ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
 scalar_t__ Dflag ; 
 scalar_t__ PAX_CTG ; 
 scalar_t__ PAX_HLK ; 
 scalar_t__ PAX_HRG ; 
 scalar_t__ PAX_REG ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 scalar_t__ Yflag ; 
 scalar_t__ Zflag ; 
 int /*<<< orphan*/  ar_close () ; 
 scalar_t__ chdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cwdfd ; 
 scalar_t__ dir_start () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fchdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_close (TYPE_3__*,int) ; 
 int file_creat (TYPE_3__*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_14__* frmt ; 
 scalar_t__ get_arc () ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  listf ; 
 int lnk_creat (TYPE_3__*) ; 
 int /*<<< orphan*/  ls_list (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int mod_name (TYPE_3__*) ; 
 scalar_t__ name_start () ; 
 scalar_t__ next_head (TYPE_3__*) ; 
 int node_creat (TYPE_3__*) ; 
 int /*<<< orphan*/  pat_chk () ; 
 int pat_match (TYPE_3__*) ; 
 scalar_t__ pat_sel (TYPE_3__*) ; 
 int /*<<< orphan*/  proc_dir () ; 
 int /*<<< orphan*/  purg_lnk (TYPE_3__*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd_skip (scalar_t__) ; 
 int /*<<< orphan*/  s_mask ; 
 scalar_t__ sel_chk (TYPE_3__*) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 () ; 
 scalar_t__ stub2 () ; 
 int stub3 (TYPE_3__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ uflag ; 
 int vflag ; 
 int vfpart ; 

void
extract(void)
{
	ARCHD *arcn;
	int res;
	off_t cnt;
	ARCHD archd;
	struct stat sb;
	int fd;
	time_t now;

	arcn = &archd;
	/*
	 * figure out archive type; pass any format specific options to the
	 * archive option processing routine; call the format init routine;
	 * start up the directory modification time and access mode database
	 */
	if ((get_arc() < 0) || ((*frmt->options)() < 0) ||
	    ((*frmt->st_rd)() < 0) || (dir_start() < 0))
		return;

	/*
	 * When we are doing interactive rename, we store the mapping of names
	 * so we can fix up hard links files later in the archive.
	 */
	if (iflag && (name_start() < 0))
		return;

	now = time(NULL);

	/*
	 * step through each entry on the archive until the format read routine
	 * says it is done
	 */
	while (next_head(arcn) == 0) {

		/*
		 * check for pattern, and user specified options match. When
		 * all the patterns are matched we are done
		 */
		if ((res = pat_match(arcn)) < 0)
			break;

		if ((res > 0) || (sel_chk(arcn) != 0)) {
			/*
			 * file is not selected. skip past any file data and
			 * padding and go back for the next archive member
			 */
			(void)rd_skip(arcn->skip + arcn->pad);
			continue;
		}

		/*
		 * with -u or -D only extract when the archive member is newer
		 * than the file with the same name in the file system (nos
		 * test of being the same type is required).
		 * NOTE: this test is done BEFORE name modifications as
		 * specified by pax. this operation can be confusing to the
		 * user who might expect the test to be done on an existing
		 * file AFTER the name mod. In honesty the pax spec is probably
		 * flawed in this respect.
		 */
		if ((uflag || Dflag) && ((lstat(arcn->name, &sb) == 0))) {
			if (uflag && Dflag) {
				if ((arcn->sb.st_mtime <= sb.st_mtime) &&
				    (arcn->sb.st_ctime <= sb.st_ctime)) {
					(void)rd_skip(arcn->skip + arcn->pad);
					continue;
				}
			} else if (Dflag) {
				if (arcn->sb.st_ctime <= sb.st_ctime) {
					(void)rd_skip(arcn->skip + arcn->pad);
					continue;
				}
			} else if (arcn->sb.st_mtime <= sb.st_mtime) {
				(void)rd_skip(arcn->skip + arcn->pad);
				continue;
			}
		}

		/*
		 * this archive member is now been selected. modify the name.
		 */
		if ((pat_sel(arcn) < 0) || ((res = mod_name(arcn)) < 0))
			break;
		if (res > 0) {
			/*
			 * a bad name mod, skip and purge name from link table
			 */
			purg_lnk(arcn);
			(void)rd_skip(arcn->skip + arcn->pad);
			continue;
		}

		/*
		 * Non standard -Y and -Z flag. When the existing file is
		 * same age or newer skip
		 */
		if ((Yflag || Zflag) && ((lstat(arcn->name, &sb) == 0))) {
			if (Yflag && Zflag) {
				if ((arcn->sb.st_mtime <= sb.st_mtime) &&
				    (arcn->sb.st_ctime <= sb.st_ctime)) {
					(void)rd_skip(arcn->skip + arcn->pad);
					continue;
				}
			} else if (Yflag) {
				if (arcn->sb.st_ctime <= sb.st_ctime) {
					(void)rd_skip(arcn->skip + arcn->pad);
					continue;
				}
			} else if (arcn->sb.st_mtime <= sb.st_mtime) {
				(void)rd_skip(arcn->skip + arcn->pad);
				continue;
			}
		}

		if (vflag) {
			if (vflag > 1)
				ls_list(arcn, now, listf);
			else {
				(void)fputs(arcn->name, listf);
				vfpart = 1;
			}
		}

		/*
		 * if required, chdir around.
		 */
		if ((arcn->pat != NULL) && (arcn->pat->chdname != NULL))
			if (chdir(arcn->pat->chdname) != 0)
				syswarn(1, errno, "Cannot chdir to %s",
				    arcn->pat->chdname);

		/*
		 * all ok, extract this member based on type
		 */
		if ((arcn->type != PAX_REG) && (arcn->type != PAX_CTG)) {
			/*
			 * process archive members that are not regular files.
			 * throw out padding and any data that might follow the
			 * header (as determined by the format).
			 */
			if ((arcn->type == PAX_HLK) || (arcn->type == PAX_HRG))
				res = lnk_creat(arcn);
			else
				res = node_creat(arcn);

			(void)rd_skip(arcn->skip + arcn->pad);
			if (res < 0)
				purg_lnk(arcn);

			if (vflag && vfpart) {
				(void)putc('\n', listf);
				vfpart = 0;
			}
			continue;
		}
		/*
		 * we have a file with data here. If we can not create it, skip
		 * over the data and purge the name from hard link table
		 */
		if ((fd = file_creat(arcn)) < 0) {
			(void)rd_skip(arcn->skip + arcn->pad);
			purg_lnk(arcn);
			continue;
		}
		/*
		 * extract the file from the archive and skip over padding and
		 * any unprocessed data
		 */
		res = (*frmt->rd_data)(arcn, fd, &cnt);
		file_close(arcn, fd);
		if (vflag && vfpart) {
			(void)putc('\n', listf);
			vfpart = 0;
		}
		if (!res)
			(void)rd_skip(cnt + arcn->pad);

		/*
		 * if required, chdir around.
		 */
		if ((arcn->pat != NULL) && (arcn->pat->chdname != NULL))
			if (fchdir(cwdfd) != 0)
				syswarn(1, errno,
				    "Can't fchdir to starting directory");
	}

	/*
	 * all done, restore directory modes and times as required; make sure
	 * all patterns supplied by the user were matched; block off signals
	 * to avoid chance for multiple entry into the cleanup code.
	 */
	(void)(*frmt->end_rd)();
	(void)sigprocmask(SIG_BLOCK, &s_mask, NULL);
	ar_close();
	proc_dir();
	pat_chk();
}