#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct sd_iterargs {int setsdstate; int countproc; scalar_t__ activecount; scalar_t__ signo; } ;
struct sd_filterargs {int delayterm; int shutdownstate; } ;
struct TYPE_4__ {struct proc* le_next; } ;
struct proc {int p_listflag; int p_shutdownstate; char* p_comm; int p_pid; int /*<<< orphan*/  task; TYPE_1__ p_list; } ;
struct TYPE_6__ {struct proc* lh_first; } ;
struct TYPE_5__ {struct proc* lh_first; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PWAIT ; 
 int P_LIST_EXITCOUNT ; 
 scalar_t__ SIGKILL ; 
 scalar_t__ SIGTERM ; 
 TYPE_3__ allproc ; 
 scalar_t__ current_proc () ; 
 struct proc* initproc ; 
 int msleep (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct timespec*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct proc* proc_find (int) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_mlock ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  proc_rebootscan (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  proc_rele (struct proc*) ; 
 scalar_t__ proc_shutdown_exitcount ; 
 int /*<<< orphan*/  psignal (struct proc*,scalar_t__) ; 
 int /*<<< orphan*/  sd_callback1 ; 
 int /*<<< orphan*/  sd_callback2 ; 
 int /*<<< orphan*/  sd_callback3 ; 
 int /*<<< orphan*/  sd_closelog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_filt1 ; 
 int /*<<< orphan*/  sd_filt2 ; 
 int /*<<< orphan*/  sd_log (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  task_suspend_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 TYPE_2__ zombproc ; 

__attribute__((used)) static void
proc_shutdown(void)
{
	vfs_context_t ctx = vfs_context_current();
	struct proc *p, *self;
	int delayterm = 0;
	struct sd_filterargs sfargs;
	struct sd_iterargs sdargs;
	int error = 0;
	struct timespec ts;

	/*
	 *	Kill as many procs as we can.  (Except ourself...)
	 */
	self = (struct proc *)current_proc();

	/*
	 * Signal the init with SIGTERM so that he does not launch
	 * new processes
	 */
	p = proc_find(1);
	if (p && p != self) {
		psignal(p, SIGTERM);
	}
	proc_rele(p);

	printf("Killing all processes ");

sigterm_loop:
	/*
	 * send SIGTERM to those procs interested in catching one
	 */
	sfargs.delayterm = delayterm;
	sfargs.shutdownstate = 0;
	sdargs.signo = SIGTERM;
	sdargs.setsdstate = 1;
	sdargs.countproc = 1;
	sdargs.activecount = 0;

	error = 0;
	/* post a SIGTERM to all that catch SIGTERM and not marked for delay */
	proc_rebootscan(sd_callback1, (void *)&sdargs, sd_filt1, (void *)&sfargs);

	if (sdargs.activecount != 0 && proc_shutdown_exitcount!= 0) {
		proc_list_lock();
		if (proc_shutdown_exitcount != 0) {
			/*
			 * now wait for up to 3 seconds to allow those procs catching SIGTERM
			 * to digest it
			 * as soon as these procs have exited, we'll continue on to the next step
			 */
			ts.tv_sec = 3;
			ts.tv_nsec = 0;
			error = msleep(&proc_shutdown_exitcount, proc_list_mlock, PWAIT, "shutdownwait", &ts);
			if (error != 0) {
				for (p = allproc.lh_first; p; p = p->p_list.le_next) {
					if ((p->p_listflag & P_LIST_EXITCOUNT) == P_LIST_EXITCOUNT)
						p->p_listflag &= ~P_LIST_EXITCOUNT;
				}
				for (p = zombproc.lh_first; p; p = p->p_list.le_next) {
					if ((p->p_listflag & P_LIST_EXITCOUNT) == P_LIST_EXITCOUNT)
						p->p_listflag &= ~P_LIST_EXITCOUNT;
				}
			}
		}
		proc_list_unlock();
	}
	if (error == ETIMEDOUT) {
		/*
		 * log the names of the unresponsive tasks
		 */

		proc_list_lock();

		for (p = allproc.lh_first; p; p = p->p_list.le_next) {
			if (p->p_shutdownstate == 1) {
				printf("%s[%d]: didn't act on SIGTERM\n", p->p_comm, p->p_pid);
				sd_log(ctx, "%s[%d]: didn't act on SIGTERM\n", p->p_comm, p->p_pid);
			}
		}

		proc_list_unlock();
	}

	/*
	 * send a SIGKILL to all the procs still hanging around
	 */
	sfargs.delayterm = delayterm;
	sfargs.shutdownstate = 2;
	sdargs.signo = SIGKILL;
	sdargs.setsdstate = 2;
	sdargs.countproc = 1;
	sdargs.activecount = 0;

	/* post a SIGKILL to all that catch SIGTERM and not marked for delay */
	proc_rebootscan(sd_callback2, (void *)&sdargs, sd_filt2, (void *)&sfargs);

	error = 0;

	if (sdargs.activecount != 0 && proc_shutdown_exitcount!= 0) {
		proc_list_lock();
		if (proc_shutdown_exitcount != 0) {
			/*
			* wait for up to 60 seconds to allow these procs to exit normally
			*
			* History:	The delay interval was changed from 100 to 200
			*		for NFS requests in particular.
			*/
			ts.tv_sec = 10;
			ts.tv_nsec = 0;
			error = msleep(&proc_shutdown_exitcount, proc_list_mlock, PWAIT, "shutdownwait", &ts);
			if (error != 0) {
				for (p = allproc.lh_first; p; p = p->p_list.le_next) {
					if ((p->p_listflag & P_LIST_EXITCOUNT) == P_LIST_EXITCOUNT)
						p->p_listflag &= ~P_LIST_EXITCOUNT;
				}
				for (p = zombproc.lh_first; p; p = p->p_list.le_next) {
					if ((p->p_listflag & P_LIST_EXITCOUNT) == P_LIST_EXITCOUNT)
						p->p_listflag &= ~P_LIST_EXITCOUNT;
				}
			}
		}
		proc_list_unlock();
	}

	if (error == ETIMEDOUT) {
		/*
		 * log the names of the unresponsive tasks
		 */

		proc_list_lock();

		for (p = allproc.lh_first; p; p = p->p_list.le_next) {
			if (p->p_shutdownstate == 2) {
				printf("%s[%d]: didn't act on SIGKILL\n", p->p_comm, p->p_pid);
				sd_log(ctx, "%s[%d]: didn't act on SIGKILL\n", p->p_comm, p->p_pid);
			}
		}

		proc_list_unlock();
	}

	/*
	 * if we still have procs that haven't exited, then brute force 'em
	 */
	sfargs.delayterm = delayterm;
	sfargs.shutdownstate = 3;
	sdargs.signo = 0;
	sdargs.setsdstate = 3;
	sdargs.countproc = 0;
	sdargs.activecount = 0;



	/* post a SIGTERM to all that catch SIGTERM and not marked for delay */
	proc_rebootscan(sd_callback3, (void *)&sdargs, sd_filt2, (void *)&sfargs);
	printf("\n");

	/* Now start the termination of processes that are marked for delayed termn */
	if (delayterm == 0) {
		delayterm = 1;
		goto  sigterm_loop;
	}

	sd_closelog(ctx);

	/*
	 * Now that all other processes have been terminated, suspend init
	 */
	task_suspend_internal(initproc->task);

	/* drop the ref on initproc */
	proc_rele(initproc);
	printf("continuing\n");
}