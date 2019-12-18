#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  scalar_t__ off_t ;
struct TYPE_18__ {scalar_t__ type; scalar_t__ pad; int /*<<< orphan*/  name; int /*<<< orphan*/  org_name; } ;
struct TYPE_17__ {int hlk; scalar_t__ (* st_wr ) () ;int (* wr ) (TYPE_1__*) ;int (* wr_data ) (TYPE_1__*,int,scalar_t__*) ;int /*<<< orphan*/  (* end_wr ) () ;} ;
typedef  TYPE_1__ ARCHD ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ PAX_CTG ; 
 scalar_t__ PAX_HRG ; 
 scalar_t__ PAX_REG ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  ar_close () ; 
 int chk_ftime (TYPE_1__*) ; 
 scalar_t__ chk_lnk (TYPE_1__*) ; 
 scalar_t__ docrc ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  flcnt ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_14__* frmt ; 
 int /*<<< orphan*/  ftree_chk () ; 
 int /*<<< orphan*/  ftree_notsel () ; 
 int /*<<< orphan*/  ftree_sel (TYPE_1__*) ; 
 scalar_t__ ftree_start () ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  listf ; 
 scalar_t__ lnk_start () ; 
 int /*<<< orphan*/  ls_list (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mod_name (TYPE_1__*) ; 
 scalar_t__ name_start () ; 
 scalar_t__ next_file (TYPE_1__*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_dir () ; 
 int /*<<< orphan*/  purg_lnk (TYPE_1__*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdfile_close (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  s_mask ; 
 scalar_t__ sel_chk (TYPE_1__*) ; 
 scalar_t__ set_crc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 () ; 
 int stub2 (TYPE_1__*) ; 
 int stub3 (TYPE_1__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tflag ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ uflag ; 
 int vflag ; 
 int vfpart ; 
 int /*<<< orphan*/  wr_fin () ; 
 scalar_t__ wr_skip (scalar_t__) ; 

__attribute__((used)) static void
wr_archive(ARCHD *arcn, int is_app)
{
	int res;
	int hlk;
	int wr_one;
	off_t cnt;
	int (*wrf)(ARCHD *);
	int fd = -1;
	time_t now;

	/*
	 * if this format supports hard link storage, start up the database
	 * that detects them.
	 */
	if (((hlk = frmt->hlk) == 1) && (lnk_start() < 0))
		return;

	/*
	 * start up the file traversal code and format specific write
	 */
	if ((ftree_start() < 0) || ((*frmt->st_wr)() < 0))
		return;
	wrf = frmt->wr;

	/*
	 * When we are doing interactive rename, we store the mapping of names
	 * so we can fix up hard links files later in the archive.
	 */
	if (iflag && (name_start() < 0))
		return;

	/*
	 * if this not append, and there are no files, we do no write a trailer
	 */
	wr_one = is_app;

	now = time(NULL);

	/*
	 * while there are files to archive, process them one at at time
	 */
	while (next_file(arcn) == 0) {
		/*
		 * check if this file meets user specified options match.
		 */
		if (sel_chk(arcn) != 0) {
			ftree_notsel();
			continue;
		}
		fd = -1;
		if (uflag) {
			/*
			 * only archive if this file is newer than a file with
			 * the same name that is already stored on the archive
			 */
			if ((res = chk_ftime(arcn)) < 0)
				break;
			if (res > 0)
				continue;
		}

		/*
		 * this file is considered selected now. see if this is a hard
		 * link to a file already stored
		 */
		ftree_sel(arcn);
		if (hlk && (chk_lnk(arcn) < 0))
			break;

		if ((arcn->type == PAX_REG) || (arcn->type == PAX_HRG) ||
		    (arcn->type == PAX_CTG)) {
			/*
			 * we will have to read this file. by opening it now we
			 * can avoid writing a header to the archive for a file
			 * we were later unable to read (we also purge it from
			 * the link table).
			 */
			if ((fd = open(arcn->org_name, O_RDONLY, 0)) < 0) {
				syswarn(1,errno, "Unable to open %s to read",
					arcn->org_name);
				purg_lnk(arcn);
				continue;
			}
		}

		/*
		 * Now modify the name as requested by the user
		 */
		if ((res = mod_name(arcn)) < 0) {
			/*
			 * name modification says to skip this file, close the
			 * file and purge link table entry
			 */
			rdfile_close(arcn, &fd);
			purg_lnk(arcn);
			break;
		}

		if ((res > 0) || (docrc && (set_crc(arcn, fd) < 0))) {
			/*
			 * unable to obtain the crc we need, close the file,
			 * purge link table entry
			 */
			rdfile_close(arcn, &fd);
			purg_lnk(arcn);
			continue;
		}

		if (vflag) {
			if (vflag > 1)
				ls_list(arcn, now, listf);
			else {
				(void)fputs(arcn->name, listf);
				vfpart = 1;
			}
		}
		++flcnt;

		/*
		 * looks safe to store the file, have the format specific
		 * routine write routine store the file header on the archive
		 */
		if ((res = (*wrf)(arcn)) < 0) {
			rdfile_close(arcn, &fd);
			break;
		}
		wr_one = 1;
		if (res > 0) {
			/*
			 * format write says no file data needs to be stored
			 * so we are done messing with this file
			 */
			if (vflag && vfpart) {
				(void)putc('\n', listf);
				vfpart = 0;
			}
			rdfile_close(arcn, &fd);
			continue;
		}

		/*
		 * Add file data to the archive, quit on write error. if we
		 * cannot write the entire file contents to the archive we
		 * must pad the archive to replace the missing file data
		 * (otherwise during an extract the file header for the file
		 * which FOLLOWS this one will not be where we expect it to
		 * be).
		 */
		res = (*frmt->wr_data)(arcn, fd, &cnt);
		rdfile_close(arcn, &fd);
		if (vflag && vfpart) {
			(void)putc('\n', listf);
			vfpart = 0;
		}
		if (res < 0)
			break;

		/*
		 * pad as required, cnt is number of bytes not written
		 */
		if (((cnt > 0) && (wr_skip(cnt) < 0)) ||
		    ((arcn->pad > 0) && (wr_skip(arcn->pad) < 0)))
			break;
	}

	/*
	 * tell format to write trailer; pad to block boundary; reset directory
	 * mode/access times, and check if all patterns supplied by the user
	 * were matched. block off signals to avoid chance for multiple entry
	 * into the cleanup code
	 */
	if (wr_one) {
		(*frmt->end_wr)();
		wr_fin();
	}
	(void)sigprocmask(SIG_BLOCK, &s_mask, NULL);
	ar_close();
	if (tflag)
		proc_dir();
	ftree_chk();
}