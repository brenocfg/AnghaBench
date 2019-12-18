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
struct TYPE_5__ {int progress; int /*<<< orphan*/  (* progress_cb ) (TYPE_1__*) ;int /*<<< orphan*/  title; scalar_t__ error; scalar_t__ finished; int /*<<< orphan*/  mute; } ;
typedef  TYPE_1__ retro_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  task_queue_msg_push (TYPE_1__*,int,int,int,char*,...) ; 

__attribute__((used)) static void task_queue_push_progress(retro_task_t *task)
{
   if (task->title && !task->mute)
   {
      if (task->finished)
      {
         if (task->error)
            task_queue_msg_push(task, 1, 60, true, "%s: %s",
               "Task failed", task->title);
         else
            task_queue_msg_push(task, 1, 60, false, "100%%: %s", task->title);
      }
      else
      {
         if (task->progress >= 0 && task->progress <= 100)
            task_queue_msg_push(task, 1, 60, true, "%i%%: %s",
                  task->progress, task->title);
         else
            task_queue_msg_push(task, 1, 60, false, "%s...", task->title);
      }

      if (task->progress_cb)
         task->progress_cb(task);
   }
}