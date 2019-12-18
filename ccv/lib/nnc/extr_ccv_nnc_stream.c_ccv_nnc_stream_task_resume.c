#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucontext_t ;
struct TYPE_5__ {scalar_t__ done; int /*<<< orphan*/  context; TYPE_2__* super; } ;
typedef  TYPE_1__ ccv_nnc_stream_task_t ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  caller; int /*<<< orphan*/  callee; } ;
typedef  TYPE_2__ ccv_nnc_stream_scheduler_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_stream_task_done (TYPE_1__* const) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swapcontext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ccv_nnc_stream_task_resume(ccv_nnc_stream_task_t* const task)
{
	ccv_nnc_stream_scheduler_t* const scheduler = task->super;
	ucontext_t old_context = scheduler->caller;
	swapcontext(&scheduler->caller, &task->context);
	task->context = scheduler->callee;
	scheduler->caller = old_context;
	if (task->done)
	{
		pthread_mutex_lock(&scheduler->mutex);
		_ccv_nnc_stream_task_done(task);
		pthread_mutex_unlock(&scheduler->mutex);
	}
}