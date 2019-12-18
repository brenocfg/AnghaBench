#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* task_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
struct TYPE_7__ {int /*<<< orphan*/  threads; } ;
struct TYPE_6__ {scalar_t__ active; int /*<<< orphan*/  task_threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_2__*) ; 

int get_task_numactivethreads(task_t task)
{
	thread_t	inc;
	int num_active_thr=0;
	task_lock(task);

	for (inc  = (thread_t)(void *)queue_first(&task->threads);
			!queue_end(&task->threads, (queue_entry_t)inc); inc = (thread_t)(void *)queue_next(&inc->task_threads)) 
	{
		if(inc->active)
			num_active_thr++;
	}
	task_unlock(task);
	return num_active_thr;
}