#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  retro_task_t ;
struct TYPE_3__ {int /*<<< orphan*/  state; int /*<<< orphan*/  percent; } ;
typedef  TYPE_1__ powerstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  powerstate_percent ; 
 int /*<<< orphan*/  powerstate_status ; 

__attribute__((used)) static void task_powerstate_cb(retro_task_t *task,
      void *task_data,
      void *user_data, const char *error)
{
   powerstate_t *powerstate = (powerstate_t*)task_data;

   powerstate_percent = powerstate->percent;
   powerstate_status  = powerstate->state;

   free(powerstate);
}