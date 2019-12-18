#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* title; struct TYPE_8__* error; int /*<<< orphan*/  (* cleanup ) (TYPE_1__*) ;int /*<<< orphan*/  user_data; int /*<<< orphan*/  task_data; int /*<<< orphan*/  (* callback ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ retro_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 TYPE_1__* task_queue_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_queue_push_progress (TYPE_1__*) ; 
 int /*<<< orphan*/  tasks_finished ; 

__attribute__((used)) static void retro_task_internal_gather(void)
{
   retro_task_t *task = NULL;
   while ((task = task_queue_get(&tasks_finished)) != NULL)
   {
      task_queue_push_progress(task);

      if (task->callback)
         task->callback(task, task->task_data, task->user_data, task->error);

      if (task->cleanup)
          task->cleanup(task);

      if (task->error)
         free(task->error);

      if (task->title)
         free(task->title);

      free(task);
   }
}