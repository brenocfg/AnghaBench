#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  TYPE_2__* task_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  mach_exception_data_type_t ;
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_27__ {int /*<<< orphan*/  active_thread_count; scalar_t__ corpse_info; int /*<<< orphan*/ * bsd_info; } ;
struct TYPE_26__ {int sched_flags; scalar_t__ depress_timer_active; scalar_t__ wait_timer_active; scalar_t__ reserved_stack; scalar_t__ promotions; scalar_t__ was_promoted_on_wakeup; scalar_t__ rwlock_count; int /*<<< orphan*/ * waiting_for_mutex; int /*<<< orphan*/  state; int /*<<< orphan*/  wait_timer; scalar_t__ wait_timer_is_set; int /*<<< orphan*/  uthread; TYPE_2__* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_PROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXC_RESOURCE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KDBG_RELEASE (int /*<<< orphan*/ ,long,long,...) ; 
 int MAXTHREADNAMESIZE ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int TH_SFLAG_DEPRESSED_MASK ; 
 int TH_SFLAG_EXEC_PROMOTED ; 
 int TH_SFLAG_PROMOTED ; 
 int TH_SFLAG_RW_PROMOTED ; 
 int TH_SFLAG_WAITQ_PROMOTED ; 
 int /*<<< orphan*/  TH_TERMINATE ; 
 int /*<<< orphan*/  TRACE_DATA_THREAD_TERMINATE_PID ; 
 int /*<<< orphan*/  TRACE_STRING_PROC_EXIT ; 
 int /*<<< orphan*/  TRACE_STRING_THREADNAME_PREV ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bank_swap_thread_bank_ledger (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsd_getthreadname (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bsd_hasthreadname (int /*<<< orphan*/ ) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  delay (int /*<<< orphan*/ ) ; 
 int hw_atomic_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ipc_thread_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  kdbg_trace_data (int /*<<< orphan*/ *,long*,long*) ; 
 int /*<<< orphan*/  kdbg_trace_string (int /*<<< orphan*/ *,long*,long*,long*,long*) ; 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  kernel_debug_string_simple (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lwp__exit ; 
 int /*<<< orphan*/  pal_thread_terminate_self (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  proc_encode_exit_exception_code (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_free_reserved (TYPE_1__*) ; 
 int /*<<< orphan*/  task_deliver_crash_notification (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ task_is_a_corpse_fork (TYPE_2__*) ; 
 int /*<<< orphan*/  task_is_exec_copy (TYPE_2__*) ; 
 int /*<<< orphan*/  task_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  thead_remove_taskwatch (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_depress_abort_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mark_wait_locked (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_policy_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_sched_call (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ thread_terminate_continue ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_call_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uthread_cleanup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uthread_cred_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_interval_thread_terminate (TYPE_1__*) ; 

void
thread_terminate_self(void)
{
	thread_t		thread = current_thread();
	task_t			task;
	int threadcnt;

	pal_thread_terminate_self(thread);

	DTRACE_PROC(lwp__exit);

	thread_mtx_lock(thread);

	ipc_thread_disable(thread);

	thread_mtx_unlock(thread);

	thread_sched_call(thread, NULL);

	spl_t s = splsched();
	thread_lock(thread);

	thread_depress_abort_locked(thread);

	thread_unlock(thread);
	splx(s);

#if CONFIG_EMBEDDED
	thead_remove_taskwatch(thread);
#endif /* CONFIG_EMBEDDED */

	work_interval_thread_terminate(thread);

	thread_mtx_lock(thread);

	thread_policy_reset(thread);

	thread_mtx_unlock(thread);

	bank_swap_thread_bank_ledger(thread, NULL);

	if (kdebug_enable && bsd_hasthreadname(thread->uthread)) {
		char threadname[MAXTHREADNAMESIZE];
		bsd_getthreadname(thread->uthread, threadname);
		kernel_debug_string_simple(TRACE_STRING_THREADNAME_PREV, threadname);
	}

	task = thread->task;
	uthread_cleanup(task, thread->uthread, task->bsd_info);

	if (kdebug_enable && task->bsd_info && !task_is_exec_copy(task)) {
		/* trace out pid before we sign off */
		long dbg_arg1 = 0;
		long dbg_arg2 = 0;

		kdbg_trace_data(thread->task->bsd_info, &dbg_arg1, &dbg_arg2);
		KDBG_RELEASE(TRACE_DATA_THREAD_TERMINATE_PID, dbg_arg1, dbg_arg2);
	}

	/*
	 * After this subtraction, this thread should never access
	 * task->bsd_info unless it got 0 back from the hw_atomic_sub.  It
	 * could be racing with other threads to be the last thread in the
	 * process, and the last thread in the process will tear down the proc
	 * structure and zero-out task->bsd_info.
	 */
	threadcnt = hw_atomic_sub(&task->active_thread_count, 1);

	/*
	 * If we are the last thread to terminate and the task is
	 * associated with a BSD process, perform BSD process exit.
	 */
	if (threadcnt == 0 && task->bsd_info != NULL && !task_is_exec_copy(task)) {
		mach_exception_data_type_t subcode = 0;
		if (kdebug_enable) {
			/* since we're the last thread in this process, trace out the command name too */
			long args[4] = {};
			kdbg_trace_string(thread->task->bsd_info, &args[0], &args[1], &args[2], &args[3]);
			KDBG_RELEASE(TRACE_STRING_PROC_EXIT, args[0], args[1], args[2], args[3]);
		}

		/* Get the exit reason before proc_exit */
		subcode = proc_encode_exit_exception_code(task->bsd_info);
		proc_exit(task->bsd_info);
		/*
		 * if there is crash info in task
		 * then do the deliver action since this is
		 * last thread for this task.
		 */
		if (task->corpse_info) {
			task_deliver_crash_notification(task, current_thread(), EXC_RESOURCE, subcode);
		}
	}

	if (threadcnt == 0) {
		task_lock(task);
		if (task_is_a_corpse_fork(task)) {
			thread_wakeup((event_t)&task->active_thread_count);
		}
		task_unlock(task);
	}

	uthread_cred_free(thread->uthread);

	s = splsched();
	thread_lock(thread);

	/*
	 * Ensure that the depress timer is no longer enqueued,
	 * so the timer (stored in the thread) can be safely deallocated
	 *
	 * TODO: build timer_call_cancel_wait
	 */

	assert((thread->sched_flags & TH_SFLAG_DEPRESSED_MASK) == 0);

	uint32_t delay_us = 1;

	while (thread->depress_timer_active > 0) {
		thread_unlock(thread);
		splx(s);

		delay(delay_us++);

		if (delay_us > USEC_PER_SEC)
			panic("depress timer failed to inactivate!"
			      "thread: %p depress_timer_active: %d",
			      thread, thread->depress_timer_active);

		s = splsched();
		thread_lock(thread);
	}

	/*
	 *	Cancel wait timer, and wait for
	 *	concurrent expirations.
	 */
	if (thread->wait_timer_is_set) {
		thread->wait_timer_is_set = FALSE;

		if (timer_call_cancel(&thread->wait_timer))
			thread->wait_timer_active--;
	}

	delay_us = 1;

	while (thread->wait_timer_active > 0) {
		thread_unlock(thread);
		splx(s);

		delay(delay_us++);

		if (delay_us > USEC_PER_SEC)
			panic("wait timer failed to inactivate!"
			      "thread: %p wait_timer_active: %d",
			      thread, thread->wait_timer_active);

		s = splsched();
		thread_lock(thread);
	}

	/*
	 *	If there is a reserved stack, release it.
	 */
	if (thread->reserved_stack != 0) {
		stack_free_reserved(thread);
		thread->reserved_stack = 0;
	}

	/*
	 *	Mark thread as terminating, and block.
	 */
	thread->state |= TH_TERMINATE;
	thread_mark_wait_locked(thread, THREAD_UNINT);

	assert((thread->sched_flags & TH_SFLAG_WAITQ_PROMOTED) == 0);
	assert((thread->sched_flags & TH_SFLAG_RW_PROMOTED) == 0);
	assert((thread->sched_flags & TH_SFLAG_EXEC_PROMOTED) == 0);
	assert((thread->sched_flags & TH_SFLAG_PROMOTED) == 0);
	assert(thread->promotions == 0);
	assert(thread->was_promoted_on_wakeup == 0);
	assert(thread->waiting_for_mutex == NULL);
	assert(thread->rwlock_count == 0);

	thread_unlock(thread);
	/* splsched */

	thread_block((thread_continue_t)thread_terminate_continue);
	/*NOTREACHED*/
}