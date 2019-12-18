#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* task_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_12__ {int /*<<< orphan*/  threads; int /*<<< orphan*/  active; } ;
struct TYPE_11__ {int sched_flags; int /*<<< orphan*/  task_threads; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_1__* THREAD_NULL ; 
 int TH_SFLAG_ABORT ; 
 int TH_SFLAG_ABORTED_MASK ; 
 int /*<<< orphan*/  act_set_astbsd (TYPE_1__*) ; 
 int /*<<< orphan*/  queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 

kern_return_t
get_signalact(
	task_t		task,
	thread_t	*result_out,
	int			setast)
{
	kern_return_t	result = KERN_SUCCESS;
	thread_t		inc, thread = THREAD_NULL;

	task_lock(task);

	if (!task->active) {
		task_unlock(task);

		return (KERN_FAILURE);
	}

	for (inc  = (thread_t)(void *)queue_first(&task->threads);
			!queue_end(&task->threads, (queue_entry_t)inc); ) {
		thread_mtx_lock(inc);
		if (inc->active &&
				(inc->sched_flags & TH_SFLAG_ABORTED_MASK) != TH_SFLAG_ABORT) {
			thread = inc;
			break;
		}
		thread_mtx_unlock(inc);

		inc = (thread_t)(void *)queue_next(&inc->task_threads);
	}

	if (result_out) 
		*result_out = thread;

	if (thread) {
		if (setast)
			act_set_astbsd(thread);

		thread_mtx_unlock(thread);
	}
	else
		result = KERN_FAILURE;

	task_unlock(task);

	return (result);
}