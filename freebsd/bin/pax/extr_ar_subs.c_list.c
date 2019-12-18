#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_10__ {scalar_t__ (* options ) () ;scalar_t__ (* st_rd ) () ;int /*<<< orphan*/  (* end_rd ) () ;} ;
struct TYPE_9__ {scalar_t__ pad; scalar_t__ skip; } ;
typedef  TYPE_1__ ARCHD ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  ar_close () ; 
 TYPE_8__* frmt ; 
 scalar_t__ get_arc () ; 
 scalar_t__ gidtb_start () ; 
 int /*<<< orphan*/  ls_list (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mod_name (TYPE_1__*) ; 
 scalar_t__ next_head (TYPE_1__*) ; 
 int /*<<< orphan*/  pat_chk () ; 
 int pat_match (TYPE_1__*) ; 
 scalar_t__ pat_sel (TYPE_1__*) ; 
 int rd_skip (scalar_t__) ; 
 int /*<<< orphan*/  s_mask ; 
 scalar_t__ sel_chk (TYPE_1__*) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ stub1 () ; 
 scalar_t__ stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ uidtb_start () ; 
 scalar_t__ vflag ; 

void
list(void)
{
	ARCHD *arcn;
	int res;
	ARCHD archd;
	time_t now;

	arcn = &archd;
	/*
	 * figure out archive type; pass any format specific options to the
	 * archive option processing routine; call the format init routine. We
	 * also save current time for ls_list() so we do not make a system
	 * call for each file we need to print. If verbose (vflag) start up
	 * the name and group caches.
	 */
	if ((get_arc() < 0) || ((*frmt->options)() < 0) ||
	    ((*frmt->st_rd)() < 0))
		return;

	if (vflag && ((uidtb_start() < 0) || (gidtb_start() < 0)))
		return;

	now = time(NULL);

	/*
	 * step through the archive until the format says it is done
	 */
	while (next_head(arcn) == 0) {
		/*
		 * check for pattern, and user specified options match.
		 * When all patterns are matched we are done.
		 */
		if ((res = pat_match(arcn)) < 0)
			break;

		if ((res == 0) && (sel_chk(arcn) == 0)) {
			/*
			 * pattern resulted in a selected file
			 */
			if (pat_sel(arcn) < 0)
				break;

			/*
			 * modify the name as requested by the user if name
			 * survives modification, do a listing of the file
			 */
			if ((res = mod_name(arcn)) < 0)
				break;
			if (res == 0)
				ls_list(arcn, now, stdout);
		}

		/*
		 * skip to next archive format header using values calculated
		 * by the format header read routine
		 */
		if (rd_skip(arcn->skip + arcn->pad) == 1)
			break;
	}

	/*
	 * all done, let format have a chance to cleanup, and make sure that
	 * the patterns supplied by the user were all matched
	 */
	(void)(*frmt->end_rd)();
	(void)sigprocmask(SIG_BLOCK, &s_mask, NULL);
	ar_close();
	pat_chk();
}