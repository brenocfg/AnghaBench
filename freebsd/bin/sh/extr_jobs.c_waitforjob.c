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
struct job {scalar_t__ state; scalar_t__ jobctl; scalar_t__ foreground; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PENDING_INT ; 
 int DOWAIT_BLOCK ; 
 int DOWAIT_SIG ; 
 int DOWAIT_SIG_TRAP ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 scalar_t__ JOBDONE ; 
 int /*<<< orphan*/  JOBS ; 
 scalar_t__ JOBSTOPPED ; 
 int SIGINT ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ Tflag ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int WIFSIGNALED (int) ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int WSTOPSIG (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  dotrap () ; 
 int dowait (int,struct job*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freejob (struct job*) ; 
 int getjobstatus (struct job*) ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ int_pending () ; 
 struct job* jobtab ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rootpid ; 
 scalar_t__ rootshell ; 
 int /*<<< orphan*/  setcurjob (struct job*) ; 
 scalar_t__ tcsetpgrp (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ttyfd ; 

int
waitforjob(struct job *jp, int *signaled)
{
#if JOBS
	int propagate_int = jp->jobctl && jp->foreground;
#endif
	int status;
	int st;

	INTOFF;
	TRACE(("waitforjob(%%%td) called\n", jp - jobtab + 1));
	while (jp->state == 0)
		if (dowait(DOWAIT_BLOCK | (Tflag ? DOWAIT_SIG |
		    DOWAIT_SIG_TRAP : 0), jp) == -1)
			dotrap();
#if JOBS
	if (jp->jobctl) {
		if (ttyfd >= 0 && tcsetpgrp(ttyfd, rootpid) < 0)
			error("tcsetpgrp failed, errno=%d\n", errno);
	}
	if (jp->state == JOBSTOPPED)
		setcurjob(jp);
#endif
	status = getjobstatus(jp);
	if (signaled != NULL)
		*signaled = WIFSIGNALED(status);
	/* convert to 8 bits */
	if (WIFEXITED(status))
		st = WEXITSTATUS(status);
#if JOBS
	else if (WIFSTOPPED(status))
		st = WSTOPSIG(status) + 128;
#endif
	else
		st = WTERMSIG(status) + 128;
	if (! JOBS || jp->state == JOBDONE)
		freejob(jp);
	if (int_pending()) {
		if (!WIFSIGNALED(status) || WTERMSIG(status) != SIGINT)
			CLEAR_PENDING_INT;
	}
#if JOBS
	else if (rootshell && propagate_int &&
			WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		kill(getpid(), SIGINT);
#endif
	INTON;
	return st;
}