#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {scalar_t__ t_dtrace_resumepid; scalar_t__ t_dtrace_stop; scalar_t__ t_dtrace_sig; } ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_24__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_22__ {TYPE_2__ it_value; } ;
struct TYPE_23__ {int p_flag; int p_dtrace_stop; int /*<<< orphan*/  task; TYPE_2__ p_rlim_cpu; TYPE_16__ p_vtimer_prof; TYPE_16__ p_vtimer_user; } ;

/* Variables and functions */
 scalar_t__ CHECK_SIGNALS (TYPE_1__*,int /*<<< orphan*/ ,struct uthread*) ; 
 int /*<<< orphan*/  OSBitAndAtomic (int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* PROC_NULL ; 
 int P_OWEUPC ; 
 int P_PROFIL ; 
 int /*<<< orphan*/  SIGPROF ; 
 int /*<<< orphan*/  SIGVTALRM ; 
 int /*<<< orphan*/  SIGXCPU ; 
 int /*<<< orphan*/  TASK_VTIMER_PROF ; 
 int /*<<< orphan*/  TASK_VTIMER_RLIM ; 
 int /*<<< orphan*/  TASK_VTIMER_USER ; 
 int /*<<< orphan*/  addupc_task (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bsdinit_task () ; 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_useraddr () ; 
 int issignal_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  itimerdecr (TYPE_1__*,TYPE_16__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  postsig_locked (int) ; 
 TYPE_1__* proc_find (scalar_t__) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_log_32bit_telemetry (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_spinlock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_spinunlock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  psignal (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  psignal_try_thread (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ task_consume_32bit_log_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ task_did_exec (int /*<<< orphan*/ ) ; 
 scalar_t__ task_is_exec_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_resume_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_suspend_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_vtimer_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_vtimer_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_vtimer_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timerclear (TYPE_2__*) ; 
 scalar_t__ timerisset (TYPE_2__*) ; 
 int /*<<< orphan*/  timersub (TYPE_2__*,struct timeval*,TYPE_2__*) ; 

void
bsd_ast(thread_t thread)
{
	proc_t p = current_proc();
	struct uthread *ut = get_bsdthread_info(thread);
	int	signum;
	user_addr_t pc;
	static int bsd_init_done = 0;

	if (p == NULL)
		return;

	/* don't run bsd ast on exec copy or exec'ed tasks */
	if (task_did_exec(current_task()) || task_is_exec_copy(current_task())) {
		return;
	}

	if ((p->p_flag & P_OWEUPC) && (p->p_flag & P_PROFIL)) {
		pc = get_useraddr();
		addupc_task(p, pc, 1);
		OSBitAndAtomic(~((uint32_t)P_OWEUPC), &p->p_flag);
	}

	if (timerisset(&p->p_vtimer_user.it_value)) {
		uint32_t	microsecs;

		task_vtimer_update(p->task, TASK_VTIMER_USER, &microsecs);

		if (!itimerdecr(p, &p->p_vtimer_user, microsecs)) {
			if (timerisset(&p->p_vtimer_user.it_value))
				task_vtimer_set(p->task, TASK_VTIMER_USER);
			else
				task_vtimer_clear(p->task, TASK_VTIMER_USER);

			psignal_try_thread(p, thread, SIGVTALRM);
		}
	}

	if (timerisset(&p->p_vtimer_prof.it_value)) {
		uint32_t	microsecs;

		task_vtimer_update(p->task, TASK_VTIMER_PROF, &microsecs);

		if (!itimerdecr(p, &p->p_vtimer_prof, microsecs)) {
			if (timerisset(&p->p_vtimer_prof.it_value))
				task_vtimer_set(p->task, TASK_VTIMER_PROF);
			else
				task_vtimer_clear(p->task, TASK_VTIMER_PROF);

			psignal_try_thread(p, thread, SIGPROF);
		}
	}

	if (timerisset(&p->p_rlim_cpu)) {
		struct timeval		tv;

		task_vtimer_update(p->task, TASK_VTIMER_RLIM, (uint32_t *) &tv.tv_usec);

		proc_spinlock(p);
		if (p->p_rlim_cpu.tv_sec > 0 || p->p_rlim_cpu.tv_usec > tv.tv_usec) {
			tv.tv_sec = 0;
			timersub(&p->p_rlim_cpu, &tv, &p->p_rlim_cpu);
			proc_spinunlock(p);
		} else {

			timerclear(&p->p_rlim_cpu);
			proc_spinunlock(p);

			task_vtimer_clear(p->task, TASK_VTIMER_RLIM);

			psignal_try_thread(p, thread, SIGXCPU);
		}
	}

#if CONFIG_DTRACE
	if (ut->t_dtrace_sig) {
	    uint8_t dt_action_sig = ut->t_dtrace_sig;
	    ut->t_dtrace_sig = 0;
	    psignal(p, dt_action_sig);
	}

	if (ut->t_dtrace_stop) {
		ut->t_dtrace_stop = 0;
		proc_lock(p);
		p->p_dtrace_stop = 1;
		proc_unlock(p);
		(void)task_suspend_internal(p->task);
	}

	if (ut->t_dtrace_resumepid) {
		proc_t resumeproc = proc_find(ut->t_dtrace_resumepid);
		ut->t_dtrace_resumepid = 0;
		if (resumeproc != PROC_NULL) {
			proc_lock(resumeproc);
			/* We only act on processes stopped by dtrace */
			if (resumeproc->p_dtrace_stop) {
				resumeproc->p_dtrace_stop = 0;
				proc_unlock(resumeproc);
				task_resume_internal(resumeproc->task);
			}
			else {
				proc_unlock(resumeproc);
			}
			proc_rele(resumeproc);
		}
	}
		    
#endif /* CONFIG_DTRACE */

	proc_lock(p);
	if (CHECK_SIGNALS(p, current_thread(), ut)) {
		while ( (signum = issignal_locked(p)) )
			postsig_locked(signum);
	}
	proc_unlock(p);

#ifdef CONFIG_32BIT_TELEMETRY
	if (task_consume_32bit_log_flag(p->task)) {
		proc_log_32bit_telemetry(p);
	}
#endif /* CONFIG_32BIT_TELEMETRY */

	if (!bsd_init_done) {
		bsd_init_done = 1;
		bsdinit_task();
	}
}