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
struct TYPE_5__ {int mute; int /*<<< orphan*/  callback; int /*<<< orphan*/  handler; int /*<<< orphan*/ * state; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ retro_task_t ;
typedef  int /*<<< orphan*/  powerstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_TYPE_NONE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* task_init () ; 
 int /*<<< orphan*/  task_powerstate_cb ; 
 int /*<<< orphan*/  task_powerstate_handler ; 
 int /*<<< orphan*/  task_queue_push (TYPE_1__*) ; 

void task_push_get_powerstate(void)
{
   retro_task_t *task  = task_init();
   powerstate_t *state = NULL;

   if (!task)
      return;
   state = (powerstate_t*)calloc(1, sizeof(*state));
   if (!state)
   {
      free(task);
      return;
   }

   task->type     = TASK_TYPE_NONE;
   task->state    = state;
   task->handler  = task_powerstate_handler;
   task->callback = task_powerstate_cb;
   task->mute     = true;

   task_queue_push(task);
}