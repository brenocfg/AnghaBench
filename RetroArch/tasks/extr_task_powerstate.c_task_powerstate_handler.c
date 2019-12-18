#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_10__ {int /*<<< orphan*/  percent; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ powerstate_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* get_powerstate ) (int*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ frontend_ctx_driver_t ;

/* Variables and functions */
 TYPE_3__* frontend_get_ptr () ; 
 int /*<<< orphan*/  stub1 (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_data (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  task_set_finished (TYPE_1__*,int) ; 

__attribute__((used)) static void task_powerstate_handler(retro_task_t *task)
{
   const frontend_ctx_driver_t *frontend = frontend_get_ptr();
   powerstate_t *powerstate = (powerstate_t*)task->state;

   if (frontend && frontend->get_powerstate)
   {
      int seconds       = 0;
      powerstate->state = frontend->get_powerstate(
            &seconds, &powerstate->percent);
   }

   task_set_data(task, powerstate);
   task_set_finished(task, true);
}