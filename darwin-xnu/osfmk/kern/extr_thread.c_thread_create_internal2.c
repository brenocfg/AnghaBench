#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  TYPE_2__* task_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_13__ {scalar_t__ suspend_count; } ;
struct TYPE_12__ {int user_stop_count; } ;

/* Variables and functions */
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 TYPE_2__* TASK_NULL ; 
 int /*<<< orphan*/  TH_OPTION_NONE ; 
 int /*<<< orphan*/  extmod_statistics_incr_thread_create (TYPE_2__*) ; 
 TYPE_2__* kernel_task ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  tasks_threads_lock ; 
 scalar_t__ thread_create_internal (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  thread_hold (TYPE_1__*) ; 

__attribute__((used)) static kern_return_t
thread_create_internal2(
	task_t				task,
	thread_t			*new_thread,
	boolean_t			from_user,
	thread_continue_t		continuation)
{
	kern_return_t		result;
	thread_t			thread;

	if (task == TASK_NULL || task == kernel_task)
		return (KERN_INVALID_ARGUMENT);

	result = thread_create_internal(task, -1, continuation, NULL, TH_OPTION_NONE, &thread);
	if (result != KERN_SUCCESS)
		return (result);

	thread->user_stop_count = 1;
	thread_hold(thread);
	if (task->suspend_count > 0)
		thread_hold(thread);

	if (from_user)
		extmod_statistics_incr_thread_create(task);

	task_unlock(task);
	lck_mtx_unlock(&tasks_threads_lock);
	
	*new_thread = thread;

	return (KERN_SUCCESS);
}