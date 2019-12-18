#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ps_prochandle {int dummy; } ;
typedef  int /*<<< orphan*/  psinfo_t ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int pr_pid; } ;

/* Variables and functions */
#define  PS_LOST 129 
#define  PS_UNDEAD 128 
 int /*<<< orphan*/ * Ppsinfo (struct ps_prochandle*) ; 
 int Pstate (struct ps_prochandle*) ; 
 TYPE_1__* Pstatus (struct ps_prochandle*) ; 
 int SIG2STR_MAX ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int g_exited ; 
 int /*<<< orphan*/  notice (char*,int,...) ; 
 int proc_getpid (struct ps_prochandle*) ; 
 int proc_getwstat (struct ps_prochandle*) ; 
 int /*<<< orphan*/  proc_signame (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
prochandler(struct ps_prochandle *P, const char *msg, void *arg)
{
#ifdef illumos
	const psinfo_t *prp = Ppsinfo(P);
	int pid = Pstatus(P)->pr_pid;
#else
	int pid = proc_getpid(P);
	int wstat = proc_getwstat(P);
#endif
	char name[SIG2STR_MAX];

	if (msg != NULL) {
		notice("pid %d: %s\n", pid, msg);
		return;
	}

	switch (Pstate(P)) {
	case PS_UNDEAD:
		/*
		 * Ideally we would like to always report pr_wstat here, but it
		 * isn't possible given current /proc semantics.  If we grabbed
		 * the process, Ppsinfo() will either fail or return a zeroed
		 * psinfo_t depending on how far the parent is in reaping it.
		 * When /proc provides a stable pr_wstat in the status file,
		 * this code can be improved by examining this new pr_wstat.
		 */
		if (WIFSIGNALED(wstat)) {
			notice("pid %d terminated by %s\n", pid,
			    proc_signame(WTERMSIG(wstat),
			    name, sizeof (name)));
		} else if (WEXITSTATUS(wstat) != 0) {
			notice("pid %d exited with status %d\n",
			    pid, WEXITSTATUS(wstat));
		} else {
			notice("pid %d has exited\n", pid);
		}
		g_exited = 1;
		break;

	case PS_LOST:
		notice("pid %d exec'd a set-id or unobservable program\n", pid);
		g_exited = 1;
		break;
	}
}