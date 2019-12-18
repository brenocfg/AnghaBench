#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct job {scalar_t__ nprocs; scalar_t__ state; int /*<<< orphan*/  remembered; scalar_t__ changed; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 scalar_t__ JOBDONE ; 
 int SHOWJOBS_DEFAULT ; 
 int SHOWJOBS_VERBOSE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 struct job* bgjob ; 
 int /*<<< orphan*/  checkzombies () ; 
 int /*<<< orphan*/  freejob (struct job*) ; 
 scalar_t__ iflag ; 
 struct job* jobtab ; 
 int njobs ; 
 int /*<<< orphan*/  showjob (struct job*,int) ; 

void
showjobs(int change, int mode)
{
	int jobno;
	struct job *jp;

	TRACE(("showjobs(%d) called\n", change));
	checkzombies();
	for (jobno = 1, jp = jobtab ; jobno <= njobs ; jobno++, jp++) {
		if (! jp->used)
			continue;
		if (jp->nprocs == 0) {
			freejob(jp);
			continue;
		}
		if (change && ! jp->changed)
			continue;
		showjob(jp, mode);
		if (mode == SHOWJOBS_DEFAULT || mode == SHOWJOBS_VERBOSE) {
			jp->changed = 0;
			/* Hack: discard jobs for which $! has not been
			 * referenced in interactive mode when they terminate.
			 */
			if (jp->state == JOBDONE && !jp->remembered &&
					(iflag || jp != bgjob)) {
				freejob(jp);
			}
		}
	}
}