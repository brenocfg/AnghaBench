#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uthread_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  scalar_t__ task_t ;
typedef  TYPE_2__* proc_t ;
typedef  int boolean_t ;
struct TYPE_16__ {int p_lflag; int /*<<< orphan*/  p_uthlist; scalar_t__ p_return_to_kernel_offset; scalar_t__ p_dispatchqueue_serialno_offset; scalar_t__ p_dispatchqueue_offset; scalar_t__ task; } ;
struct TYPE_15__ {scalar_t__ uu_siglist; int /*<<< orphan*/ * uu_exit_reason; int /*<<< orphan*/ * t_dtrace_scratch; scalar_t__ t_dtrace_resumepid; scalar_t__ t_dtrace_stop; scalar_t__ t_dtrace_sig; int /*<<< orphan*/  uu_vforkmask; int /*<<< orphan*/  uu_oldmask; int /*<<< orphan*/  uu_sigmask; int /*<<< orphan*/  uu_sigwait; } ;

/* Variables and functions */
 int P_LEXIT ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  act_set_astbsd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_1__* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 scalar_t__ get_threadtask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_lock (TYPE_2__*) ; 
 TYPE_2__* proc_refdrain_with_refwait (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_refwake (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_transend (TYPE_2__*,int) ; 
 int proc_transstart (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  task_clear_exec_copy_flag (scalar_t__) ; 
 int /*<<< orphan*/  task_copy_fields_for_exec (scalar_t__,scalar_t__) ; 
 int task_is_active (scalar_t__) ; 
 int /*<<< orphan*/  task_set_did_exec_flag (scalar_t__) ; 
 int /*<<< orphan*/  task_terminate_internal (scalar_t__) ; 
 int /*<<< orphan*/  thread_clear_exec_promotion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_copy_resource_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thread_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_set_exec_promotion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_list ; 

proc_t
proc_exec_switch_task(proc_t p, task_t old_task, task_t new_task, thread_t new_thread)
{
	int error = 0;
	boolean_t task_active;
	boolean_t proc_active;
	boolean_t thread_active;
	thread_t old_thread = current_thread();

	/*
	 * Switch the task pointer of proc to new task.
	 * Before switching the task, wait for proc_refdrain.
	 * After the switch happens, the proc can disappear,
	 * take a ref before it disappears. Waiting for
	 * proc_refdrain in exec will block all other threads
	 * trying to take a proc ref, boost the current thread
	 * to avoid priority inversion.
	 */
	thread_set_exec_promotion(old_thread);
	p = proc_refdrain_with_refwait(p, TRUE);
	/* extra proc ref returned to the caller */

	assert(get_threadtask(new_thread) == new_task);
	task_active = task_is_active(new_task);

	/* Take the proc_translock to change the task ptr */
	proc_lock(p);
	proc_active = !(p->p_lflag & P_LEXIT);

	/* Check if the current thread is not aborted due to SIGKILL */
	thread_active = thread_is_active(old_thread);

	/*
	 * Do not switch the task if the new task or proc is already terminated
	 * as a result of error in exec past point of no return
	 */
	if (proc_active && task_active && thread_active) {
		error = proc_transstart(p, 1, 0);
		if (error == 0) {
			uthread_t new_uthread = get_bsdthread_info(new_thread);
			uthread_t old_uthread = get_bsdthread_info(current_thread());

			/*
			 * bsd_info of old_task will get cleared in execve and posix_spawn
			 * after firing exec-success/error dtrace probe.
			 */
			p->task = new_task;

			/* Clear dispatchqueue and workloop ast offset */
			p->p_dispatchqueue_offset = 0;
			p->p_dispatchqueue_serialno_offset = 0;
			p->p_return_to_kernel_offset = 0;

			/* Copy the signal state, dtrace state and set bsd ast on new thread */
			act_set_astbsd(new_thread);
			new_uthread->uu_siglist = old_uthread->uu_siglist;
			new_uthread->uu_sigwait = old_uthread->uu_sigwait;
			new_uthread->uu_sigmask = old_uthread->uu_sigmask;
			new_uthread->uu_oldmask = old_uthread->uu_oldmask;
			new_uthread->uu_vforkmask = old_uthread->uu_vforkmask;
			new_uthread->uu_exit_reason = old_uthread->uu_exit_reason;
#if CONFIG_DTRACE
			new_uthread->t_dtrace_sig = old_uthread->t_dtrace_sig;
			new_uthread->t_dtrace_stop = old_uthread->t_dtrace_stop;
			new_uthread->t_dtrace_resumepid = old_uthread->t_dtrace_resumepid;
			assert(new_uthread->t_dtrace_scratch == NULL);
			new_uthread->t_dtrace_scratch = old_uthread->t_dtrace_scratch;

			old_uthread->t_dtrace_sig = 0;
			old_uthread->t_dtrace_stop = 0;
			old_uthread->t_dtrace_resumepid = 0;
			old_uthread->t_dtrace_scratch = NULL;
#endif
			/* Copy the resource accounting info */
			thread_copy_resource_info(new_thread, current_thread());

			/* Clear the exit reason and signal state on old thread */
			old_uthread->uu_exit_reason = NULL;
			old_uthread->uu_siglist = 0;

			/* Add the new uthread to proc uthlist and remove the old one */
			TAILQ_INSERT_TAIL(&p->p_uthlist, new_uthread, uu_list);
			TAILQ_REMOVE(&p->p_uthlist, old_uthread, uu_list);

			task_set_did_exec_flag(old_task);
			task_clear_exec_copy_flag(new_task);

			task_copy_fields_for_exec(new_task, old_task);

			proc_transend(p, 1);
		}
	}

	proc_unlock(p);
	proc_refwake(p);
	thread_clear_exec_promotion(old_thread);

	if (error != 0 || !task_active || !proc_active || !thread_active) {
		task_terminate_internal(new_task);
	}

	return p;
}