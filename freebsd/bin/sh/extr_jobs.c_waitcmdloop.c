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
struct job {scalar_t__ state; scalar_t__ used; scalar_t__ remembered; int /*<<< orphan*/  changed; } ;

/* Variables and functions */
 int DOWAIT_BLOCK ; 
 int DOWAIT_SIG ; 
 scalar_t__ JOBDONE ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int WTERMSIG (int) ; 
 struct job* bgjob ; 
 int dowait (int,struct job*) ; 
 int /*<<< orphan*/  freejob (struct job*) ; 
 int getjobstatus (struct job*) ; 
 int /*<<< orphan*/  iflag ; 
 struct job* jobtab ; 
 int njobs ; 
 int pendingsig_waitcmd ; 

__attribute__((used)) static int
waitcmdloop(struct job *job)
{
	int status, retval, sig;
	struct job *jp;

	/*
	 * Loop until a process is terminated or stopped, or a SIGINT is
	 * received.
	 */

	do {
		if (job != NULL) {
			if (job->state == JOBDONE) {
				status = getjobstatus(job);
				if (WIFEXITED(status))
					retval = WEXITSTATUS(status);
				else
					retval = WTERMSIG(status) + 128;
				if (! iflag || ! job->changed)
					freejob(job);
				else {
					job->remembered = 0;
					if (job == bgjob)
						bgjob = NULL;
				}
				return retval;
			}
		} else {
			for (jp = jobtab ; jp < jobtab + njobs; jp++)
				if (jp->used && jp->state == JOBDONE) {
					if (! iflag || ! jp->changed)
						freejob(jp);
					else {
						jp->remembered = 0;
						if (jp == bgjob)
							bgjob = NULL;
					}
				}
			for (jp = jobtab ; ; jp++) {
				if (jp >= jobtab + njobs) {	/* no running procs */
					return 0;
				}
				if (jp->used && jp->state == 0)
					break;
			}
		}
	} while (dowait(DOWAIT_BLOCK | DOWAIT_SIG, (struct job *)NULL) != -1);

	sig = pendingsig_waitcmd;
	pendingsig_waitcmd = 0;
	return sig + 128;
}