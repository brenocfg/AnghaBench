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
typedef  TYPE_1__* task_t ;
struct TYPE_3__ {scalar_t__ purged_memory_critical; scalar_t__ purged_memory_warn; } ;

/* Variables and functions */

void
task_clear_used_for_purging(task_t task)
{
	if (task == NULL) {
		return;
	}
	
	task->purged_memory_warn = 0;
	task->purged_memory_critical = 0;
}