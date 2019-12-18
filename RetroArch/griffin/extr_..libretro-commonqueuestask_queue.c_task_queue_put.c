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
struct TYPE_5__ {TYPE_2__* back; TYPE_2__* front; } ;
typedef  TYPE_1__ task_queue_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ retro_task_t ;

/* Variables and functions */

__attribute__((used)) static void task_queue_put(task_queue_t *queue, retro_task_t *task)
{
   task->next = NULL;

   if (queue->front)
      queue->back->next = task;
   else
      queue->front = task;

   queue->back = task;
}