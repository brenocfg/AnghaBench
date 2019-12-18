#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
struct TYPE_6__ {int t_flags; } ;

/* Variables and functions */
 int TF_LRETURNWAIT ; 
 int TF_LRETURNWAITER ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_proc () ; 
 TYPE_1__* current_task () ; 
 int /*<<< orphan*/  mac_proc_notify_exec_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_get_return_wait_event (TYPE_1__*) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_bootstrap_return () ; 

void __attribute__((noreturn))
task_wait_to_return(void)
{
	task_t task;

	task = current_task();
	task_lock(task);

	if (task->t_flags & TF_LRETURNWAIT) {
		do {
			task->t_flags |= TF_LRETURNWAITER;
			assert_wait(task_get_return_wait_event(task), THREAD_UNINT);
			task_unlock(task);

			thread_block(THREAD_CONTINUE_NULL);

			task_lock(task);
		} while (task->t_flags & TF_LRETURNWAIT);
	}

	task_unlock(task);

#if CONFIG_MACF
	/*
	 * Before jumping to userspace and allowing this process to execute any code,
	 * notify any interested parties.
	 */
	mac_proc_notify_exec_complete(current_proc());
#endif

	thread_bootstrap_return();
}