#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; struct TYPE_6__* next; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* push_running ) (TYPE_1__*) ;} ;
struct TYPE_7__ {TYPE_1__* front; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLOCK_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLOCK_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ TASK_TYPE_BLOCKING ; 
 TYPE_5__* impl_current ; 
 int /*<<< orphan*/  queue_lock ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 TYPE_2__ tasks_running ; 

bool task_queue_push(retro_task_t *task)
{
   /* Ignore this task if a related one is already running */
   if (task->type == TASK_TYPE_BLOCKING)
   {
      retro_task_t *running = NULL;
      bool found = false;

      SLOCK_LOCK(queue_lock);
      running = tasks_running.front;

      for (; running; running = running->next)
      {
         if (running->type == TASK_TYPE_BLOCKING)
         {
            found = true;
            break;
         }
      }

      SLOCK_UNLOCK(queue_lock);

      /* skip this task, user must try again later */
      if (found)
         return false;
   }

   /* The lack of NULL checks in the following functions
    * is proposital to ensure correct control flow by the users. */
   impl_current->push_running(task);

   return true;
}