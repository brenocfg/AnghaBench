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
struct TYPE_5__ {struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  TYPE_1__ ccv_nnc_stream_task_t ;
struct TYPE_6__ {TYPE_1__* head; TYPE_1__* tail; } ;
typedef  TYPE_2__ ccv_nnc_stream_scheduler_t ;

/* Variables and functions */

void ccv_nnc_stream_scheduler_prepend_task(ccv_nnc_stream_scheduler_t* const scheduler, ccv_nnc_stream_task_t* const task)
{
	if (scheduler->head)
	{
		scheduler->head->prev = task;
		task->next = scheduler->head;
	} else {
		scheduler->tail = task;
		task->next = 0;
	}
	scheduler->head = task;
	task->prev = 0;
}