#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cancelled; struct TYPE_3__* next; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_4__ {TYPE_1__* front; } ;

/* Variables and functions */
 TYPE_2__ tasks_running ; 

__attribute__((used)) static void retro_task_regular_reset(void)
{
   retro_task_t *task = tasks_running.front;

   for (; task; task = task->next)
      task->cancelled = true;
}