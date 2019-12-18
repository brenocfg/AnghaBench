#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ finished; int /*<<< orphan*/  (* handler ) (TYPE_1__*) ;struct TYPE_7__* next; } ;
typedef  TYPE_1__ retro_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  retro_task_internal_gather () ; 
 int /*<<< orphan*/  retro_task_regular_push_running (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 TYPE_1__* task_queue_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_queue_push_progress (TYPE_1__*) ; 
 int /*<<< orphan*/  task_queue_put (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  tasks_finished ; 
 int /*<<< orphan*/  tasks_running ; 

__attribute__((used)) static void retro_task_regular_gather(void)
{
   retro_task_t *task  = NULL;
   retro_task_t *queue = NULL;
   retro_task_t *next  = NULL;

   while ((task = task_queue_get(&tasks_running)) != NULL)
   {
      task->next = queue;
      queue = task;
   }

   for (task = queue; task; task = next)
   {
      next = task->next;
      task->handler(task);

      task_queue_push_progress(task);

      if (task->finished)
         task_queue_put(&tasks_finished, task);
      else
         retro_task_regular_push_running(task);
   }

   retro_task_internal_gather();
}