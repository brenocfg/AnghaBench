#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_stream_task_t ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  active; } ;
typedef  TYPE_1__ ccv_nnc_stream_scheduler_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_stream_schedule_try (TYPE_1__* const) ; 
 int /*<<< orphan*/  ccv_nnc_stream_scheduler_append_task (TYPE_1__* const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void ccv_nnc_stream_schedule_task(ccv_nnc_stream_scheduler_t* const scheduler, ccv_nnc_stream_task_t* const task)
{
	int activate_scheduler = 0;
	pthread_mutex_lock(&scheduler->mutex);
	// Append to the end, for swap tasks, they all prepend. Thus, this ensures all tasks scheduled this way will be executed later.
	ccv_nnc_stream_scheduler_append_task(scheduler, task);
	if (!scheduler->active)
		activate_scheduler = 1;
	pthread_mutex_unlock(&scheduler->mutex);
	if (activate_scheduler)
		_ccv_nnc_stream_schedule_try(scheduler);
}