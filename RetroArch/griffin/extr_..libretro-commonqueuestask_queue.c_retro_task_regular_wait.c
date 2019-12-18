#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* retro_task_condition_fn_t ) (void*) ;
struct TYPE_2__ {scalar_t__ front; } ;

/* Variables and functions */
 int /*<<< orphan*/  retro_task_regular_gather () ; 
 TYPE_1__ tasks_running ; 

__attribute__((used)) static void retro_task_regular_wait(retro_task_condition_fn_t cond, void* data)
{
   while (tasks_running.front && (!cond || cond(data)))
      retro_task_regular_gather();
}