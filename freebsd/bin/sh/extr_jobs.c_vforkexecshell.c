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
struct procstat {int pid; int status; int /*<<< orphan*/  cmd; } ;
struct job {int foreground; int /*<<< orphan*/  nprocs; struct procstat* ps; } ;
struct jmploc {int /*<<< orphan*/  loc; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exitstatus ; 
 int /*<<< orphan*/  flushall () ; 
 scalar_t__ getpid () ; 
 struct jmploc* handler ; 
 int jobtab ; 
 int /*<<< orphan*/  nullstr ; 
 int /*<<< orphan*/  setcurjob (struct job*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shellexec (char**,char**,char const*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int vfork () ; 

pid_t
vforkexecshell(struct job *jp, char **argv, char **envp, const char *path, int idx, int pip[2])
{
	pid_t pid;
	struct jmploc jmploc;
	struct jmploc *savehandler;

	TRACE(("vforkexecshell(%%%td, %s, %p) called\n", jp - jobtab, argv[0],
	    (void *)pip));
	INTOFF;
	flushall();
	savehandler = handler;
	pid = vfork();
	if (pid == -1) {
		TRACE(("Vfork failed, errno=%d\n", errno));
		INTON;
		error("Cannot fork: %s", strerror(errno));
	}
	if (pid == 0) {
		TRACE(("Child shell %d\n", (int)getpid()));
		if (setjmp(jmploc.loc))
			_exit(exitstatus);
		if (pip != NULL) {
			close(pip[0]);
			if (pip[1] != 1) {
				dup2(pip[1], 1);
				close(pip[1]);
			}
		}
		handler = &jmploc;
		shellexec(argv, envp, path, idx);
	}
	handler = savehandler;
	if (jp) {
		struct procstat *ps = &jp->ps[jp->nprocs++];
		ps->pid = pid;
		ps->status = -1;
		ps->cmd = nullstr;
		jp->foreground = 1;
#if JOBS
		setcurjob(jp);
#endif
	}
	INTON;
	TRACE(("In parent shell:  child = %d\n", (int)pid));
	return pid;
}