#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ done; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ ccv_nnc_stream_task_t ;
struct TYPE_9__ {int active; scalar_t__ stream_wait_task_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  callee; int /*<<< orphan*/  caller; TYPE_1__* head; int /*<<< orphan*/  thread; } ;
typedef  TYPE_2__ ccv_nnc_stream_scheduler_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_stream_schedule_main ; 
 int /*<<< orphan*/  _ccv_nnc_stream_scheduler_delete_task (TYPE_2__* const,TYPE_1__* const) ; 
 int /*<<< orphan*/  _ccv_nnc_stream_task_done (TYPE_1__* const) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__* const) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swapcontext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _ccv_nnc_stream_schedule_try(ccv_nnc_stream_scheduler_t* const scheduler)
{
	pthread_mutex_lock(&scheduler->mutex);
	if (scheduler->active)
	{
		pthread_mutex_unlock(&scheduler->mutex);
		return;
	}
	scheduler->active = 1;
	for (;;)
	{
		if (scheduler->head == 0 && scheduler->stream_wait_task_count == 0)
		{
			scheduler->active = 0;
			pthread_mutex_unlock(&scheduler->mutex);
			break;
		}
		if (scheduler->head == 0)
		{
			// Launch a thread to continue the execution.
			pthread_create(&scheduler->thread, 0, _ccv_nnc_stream_schedule_main, scheduler);
			pthread_mutex_unlock(&scheduler->mutex);
			break;
		}
		ccv_nnc_stream_task_t* const task = scheduler->head;
		_ccv_nnc_stream_scheduler_delete_task(scheduler, task);
		pthread_mutex_unlock(&scheduler->mutex);
		swapcontext(&scheduler->caller, &task->context);
		task->context = scheduler->callee;
		pthread_mutex_lock(&scheduler->mutex);
		if (task->done)
			_ccv_nnc_stream_task_done(task);
	}
}