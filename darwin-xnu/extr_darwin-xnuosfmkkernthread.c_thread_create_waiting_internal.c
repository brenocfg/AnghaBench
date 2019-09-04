#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  TYPE_2__* task_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  int /*<<< orphan*/  block_hint_t ;
struct TYPE_18__ {scalar_t__ suspend_count; } ;
struct TYPE_17__ {int static_param; } ;

/* Variables and functions */
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 TYPE_2__* TASK_NULL ; 
 int /*<<< orphan*/  THREAD_INTERRUPTIBLE ; 
 int TH_OPTION_WORKQ ; 
 TYPE_2__* kernel_task ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  tasks_threads_lock ; 
 scalar_t__ thread_create_internal (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__**) ; 
 int /*<<< orphan*/  thread_hold (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_set_pending_block_hint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_start_in_assert_wait (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_thread_init_and_wq_lock (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static kern_return_t
thread_create_waiting_internal(
	task_t                  task,
	thread_continue_t       continuation,
	event_t                 event,
	block_hint_t            block_hint,
	int                     options,
	thread_t                *new_thread)
{
	kern_return_t result;
	thread_t thread;

	if (task == TASK_NULL || task == kernel_task)
		return (KERN_INVALID_ARGUMENT);

	result = thread_create_internal(task, -1, continuation, NULL,
			options, &thread);
	if (result != KERN_SUCCESS)
		return (result);

	/* note no user_stop_count or thread_hold here */

	if (task->suspend_count > 0)
		thread_hold(thread);

	thread_mtx_lock(thread);
	thread_set_pending_block_hint(thread, block_hint);
	if (options & TH_OPTION_WORKQ) {
		thread->static_param = true;
		event = workq_thread_init_and_wq_lock(task, thread);
	}
	thread_start_in_assert_wait(thread, event, THREAD_INTERRUPTIBLE);
	thread_mtx_unlock(thread);

	task_unlock(task);
	lck_mtx_unlock(&tasks_threads_lock);

	*new_thread = thread;

	return (KERN_SUCCESS);
}