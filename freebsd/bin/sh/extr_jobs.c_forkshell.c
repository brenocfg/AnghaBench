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
typedef  union node {int dummy; } node ;
struct procstat {int pid; int status; int /*<<< orphan*/  cmd; } ;
struct job {scalar_t__ nprocs; scalar_t__ state; int foreground; struct procstat* ps; int /*<<< orphan*/  remembered; scalar_t__ used; } ;
typedef  int pid_t ;

/* Variables and functions */
 int FORK_BG ; 
 int FORK_FG ; 
 int FORK_NOJOB ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 scalar_t__ JOBDONE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int backgndpid ; 
 struct job* bgjob ; 
 int /*<<< orphan*/  checkzombies () ; 
 int /*<<< orphan*/  clear_traps () ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closescript () ; 
 int /*<<< orphan*/  commandtext (union node*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 int /*<<< orphan*/  fd0_redirected_p () ; 
 int /*<<< orphan*/  flushall () ; 
 scalar_t__ forcelocal ; 
 int fork () ; 
 int /*<<< orphan*/  freejob (struct job*) ; 
 int getpid () ; 
 int /*<<< orphan*/ * handler ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  ignoresig (int /*<<< orphan*/ ) ; 
 scalar_t__ jobctl ; 
 struct job* jobtab ; 
 int /*<<< orphan*/  main_handler ; 
 scalar_t__ mflag ; 
 int njobs ; 
 int /*<<< orphan*/  nullstr ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rootshell ; 
 int /*<<< orphan*/  setcurjob (struct job*) ; 
 scalar_t__ setpgid (int,int) ; 
 int /*<<< orphan*/  setsignal (int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ tcsetpgrp (scalar_t__,int) ; 
 scalar_t__ ttyfd ; 

pid_t
forkshell(struct job *jp, union node *n, int mode)
{
	pid_t pid;
	pid_t pgrp;

	TRACE(("forkshell(%%%td, %p, %d) called\n", jp - jobtab, (void *)n,
	    mode));
	INTOFF;
	if (mode == FORK_BG && (jp == NULL || jp->nprocs == 0))
		checkzombies();
	flushall();
	pid = fork();
	if (pid == -1) {
		TRACE(("Fork failed, errno=%d\n", errno));
		INTON;
		error("Cannot fork: %s", strerror(errno));
	}
	if (pid == 0) {
		struct job *p;
		int wasroot;
		int i;

		TRACE(("Child shell %d\n", (int)getpid()));
		wasroot = rootshell;
		rootshell = 0;
		handler = &main_handler;
		closescript();
		INTON;
		forcelocal = 0;
		clear_traps();
#if JOBS
		jobctl = 0;		/* do job control only in root shell */
		if (wasroot && mode != FORK_NOJOB && mflag) {
			if (jp == NULL || jp->nprocs == 0)
				pgrp = getpid();
			else
				pgrp = jp->ps[0].pid;
			if (setpgid(0, pgrp) == 0 && mode == FORK_FG &&
			    ttyfd >= 0) {
				/*** this causes superfluous TIOCSPGRPS ***/
				if (tcsetpgrp(ttyfd, pgrp) < 0)
					error("tcsetpgrp failed, errno=%d", errno);
			}
			setsignal(SIGTSTP);
			setsignal(SIGTTOU);
		} else if (mode == FORK_BG) {
			ignoresig(SIGINT);
			ignoresig(SIGQUIT);
			if ((jp == NULL || jp->nprocs == 0) &&
			    ! fd0_redirected_p ()) {
				close(0);
				if (open(_PATH_DEVNULL, O_RDONLY) != 0)
					error("cannot open %s: %s",
					    _PATH_DEVNULL, strerror(errno));
			}
		}
#else
		if (mode == FORK_BG) {
			ignoresig(SIGINT);
			ignoresig(SIGQUIT);
			if ((jp == NULL || jp->nprocs == 0) &&
			    ! fd0_redirected_p ()) {
				close(0);
				if (open(_PATH_DEVNULL, O_RDONLY) != 0)
					error("cannot open %s: %s",
					    _PATH_DEVNULL, strerror(errno));
			}
		}
#endif
		INTOFF;
		for (i = njobs, p = jobtab ; --i >= 0 ; p++)
			if (p->used)
				freejob(p);
		INTON;
		if (wasroot && iflag) {
			setsignal(SIGINT);
			setsignal(SIGQUIT);
			setsignal(SIGTERM);
		}
		return pid;
	}
	if (rootshell && mode != FORK_NOJOB && mflag) {
		if (jp == NULL || jp->nprocs == 0)
			pgrp = pid;
		else
			pgrp = jp->ps[0].pid;
		setpgid(pid, pgrp);
	}
	if (mode == FORK_BG) {
		if (bgjob != NULL && bgjob->state == JOBDONE &&
		    !bgjob->remembered && !iflag)
			freejob(bgjob);
		backgndpid = pid;		/* set $! */
		bgjob = jp;
	}
	if (jp) {
		struct procstat *ps = &jp->ps[jp->nprocs++];
		ps->pid = pid;
		ps->status = -1;
		ps->cmd = nullstr;
		if (iflag && rootshell && n)
			ps->cmd = commandtext(n);
		jp->foreground = mode == FORK_FG;
#if JOBS
		setcurjob(jp);
#endif
	}
	INTON;
	TRACE(("In parent shell:  child = %d\n", (int)pid));
	return pid;
}