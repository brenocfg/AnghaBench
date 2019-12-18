#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_8__ {int pr_wstat; } ;
typedef  TYPE_1__ psinfo_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_9__ {int dpr_stop; int dpr_pid; int /*<<< orphan*/  dpr_lock; int /*<<< orphan*/  dpr_hdl; int /*<<< orphan*/  dpr_proc; scalar_t__ dpr_done; int /*<<< orphan*/  dpr_cv; int /*<<< orphan*/  dpr_tid; } ;
typedef  TYPE_2__ dt_proc_t ;
struct TYPE_10__ {TYPE_2__* dpcd_proc; int /*<<< orphan*/ * dpcd_hdl; } ;
typedef  TYPE_3__ dt_proc_control_data_t ;

/* Variables and functions */
 int DT_PROC_STOP_IDLE ; 
 int ESRCH ; 
 scalar_t__ PS_LOST ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 TYPE_1__* Ppsinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGCANCEL ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  dt_proc_control ; 
 int /*<<< orphan*/  dt_proc_error (int /*<<< orphan*/ ,TYPE_2__*,char*,int,...) ; 
 int proc_getpid (int /*<<< orphan*/ ) ; 
 int proc_getwstat (int /*<<< orphan*/ ) ; 
 scalar_t__ proc_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int
dt_proc_create_thread(dtrace_hdl_t *dtp, dt_proc_t *dpr, uint_t stop)
{
	dt_proc_control_data_t data;
	sigset_t nset, oset;
	pthread_attr_t a;
	int err;

	(void) pthread_mutex_lock(&dpr->dpr_lock);
	dpr->dpr_stop |= stop; /* set bit for initial rendezvous */

	(void) pthread_attr_init(&a);
	(void) pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);

	(void) sigfillset(&nset);
	(void) sigdelset(&nset, SIGABRT);	/* unblocked for assert() */
#ifdef illumos
	(void) sigdelset(&nset, SIGCANCEL);	/* see dt_proc_destroy() */
#else
	(void) sigdelset(&nset, SIGUSR1);	/* see dt_proc_destroy() */
#endif

	data.dpcd_hdl = dtp;
	data.dpcd_proc = dpr;

	(void) pthread_sigmask(SIG_SETMASK, &nset, &oset);
	err = pthread_create(&dpr->dpr_tid, &a, dt_proc_control, &data);
	(void) pthread_sigmask(SIG_SETMASK, &oset, NULL);

	/*
	 * If the control thread was created, then wait on dpr_cv for either
	 * dpr_done to be set (the victim died or the control thread failed)
	 * or DT_PROC_STOP_IDLE to be set, indicating that the victim is now
	 * stopped by /proc and the control thread is at the rendezvous event.
	 * On success, we return with the process and control thread stopped:
	 * the caller can then apply dt_proc_continue() to resume both.
	 */
	if (err == 0) {
		while (!dpr->dpr_done && !(dpr->dpr_stop & DT_PROC_STOP_IDLE))
			(void) pthread_cond_wait(&dpr->dpr_cv, &dpr->dpr_lock);

		/*
		 * If dpr_done is set, the control thread aborted before it
		 * reached the rendezvous event.  This is either due to PS_LOST
		 * or PS_UNDEAD (i.e. the process died).  We try to provide a
		 * small amount of useful information to help figure it out.
		 */
		if (dpr->dpr_done) {
#ifdef illumos
			const psinfo_t *prp = Ppsinfo(dpr->dpr_proc);
			int stat = prp ? prp->pr_wstat : 0;
			int pid = dpr->dpr_pid;
#else
			int stat = proc_getwstat(dpr->dpr_proc);
			int pid = proc_getpid(dpr->dpr_proc);
#endif
			if (proc_state(dpr->dpr_proc) == PS_LOST) {
				(void) dt_proc_error(dpr->dpr_hdl, dpr,
				    "failed to control pid %d: process exec'd "
				    "set-id or unobservable program\n", pid);
			} else if (WIFSIGNALED(stat)) {
				(void) dt_proc_error(dpr->dpr_hdl, dpr,
				    "failed to control pid %d: process died "
				    "from signal %d\n", pid, WTERMSIG(stat));
			} else {
				(void) dt_proc_error(dpr->dpr_hdl, dpr,
				    "failed to control pid %d: process exited "
				    "with status %d\n", pid, WEXITSTATUS(stat));
			}

			err = ESRCH; /* cause grab() or create() to fail */
		}
	} else {
		(void) dt_proc_error(dpr->dpr_hdl, dpr,
		    "failed to create control thread for process-id %d: %s\n",
		    (int)dpr->dpr_pid, strerror(err));
	}

	if (err == 0)
		(void) pthread_mutex_unlock(&dpr->dpr_lock);
	(void) pthread_attr_destroy(&a);

	return (err);
}