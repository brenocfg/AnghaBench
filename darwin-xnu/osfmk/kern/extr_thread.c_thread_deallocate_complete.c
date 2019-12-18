#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  task_t ;
struct io_stat_info {int dummy; } ;
struct TYPE_11__ {scalar_t__ ref_count; int state; scalar_t__ runq; scalar_t__ turnstile; scalar_t__ ith_voucher; scalar_t__ kernel_stack; scalar_t__ thread_magic; int /*<<< orphan*/  mutex; scalar_t__ thread_io_stats; scalar_t__ t_threadledger; scalar_t__ t_ledger; int /*<<< orphan*/ * uthread; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 scalar_t__ IPC_VOUCHER_NULL ; 
 scalar_t__ PROCESSOR_NULL ; 
 int TH_TERMINATE2 ; 
 scalar_t__ TURNSTILE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_thread_magic (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_thread_terminate (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_voucher_release (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__,int) ; 
 int /*<<< orphan*/  kpc_thread_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ledger_dereference (scalar_t__) ; 
 int /*<<< orphan*/  machine_thread_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  proc_thread_qos_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  stack_free (TYPE_1__*) ; 
 int /*<<< orphan*/  task_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lck_grp ; 
 scalar_t__ thread_owned_workloops_count (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_zone ; 
 int /*<<< orphan*/  turnstile_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  uthread_zone_free (void*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
thread_deallocate_complete(
	thread_t			thread)
{
	task_t				task;

	assert_thread_magic(thread);

	assert(thread->ref_count == 0);

	assert(thread_owned_workloops_count(thread) == 0);

	if (!(thread->state & TH_TERMINATE2))
		panic("thread_deallocate: thread not properly terminated\n");

	assert(thread->runq == PROCESSOR_NULL);

#if KPC
	kpc_thread_destroy(thread);
#endif

	ipc_thread_terminate(thread);

	proc_thread_qos_deallocate(thread);

	task = thread->task;

#ifdef MACH_BSD
	{
		void *ut = thread->uthread;

		thread->uthread = NULL;
		uthread_zone_free(ut);
	}
#endif /* MACH_BSD */

	if (thread->t_ledger)
		ledger_dereference(thread->t_ledger);
	if (thread->t_threadledger)
		ledger_dereference(thread->t_threadledger);

	assert(thread->turnstile != TURNSTILE_NULL);
	if (thread->turnstile)
		turnstile_deallocate(thread->turnstile);

	if (IPC_VOUCHER_NULL != thread->ith_voucher)
		ipc_voucher_release(thread->ith_voucher);

	if (thread->thread_io_stats)
		kfree(thread->thread_io_stats, sizeof(struct io_stat_info));

	if (thread->kernel_stack != 0)
		stack_free(thread);

	lck_mtx_destroy(&thread->mutex, &thread_lck_grp);
	machine_thread_destroy(thread);

	task_deallocate(task);

#if MACH_ASSERT
	assert_thread_magic(thread);
	thread->thread_magic = 0;
#endif /* MACH_ASSERT */

	zfree(thread_zone, thread);
}