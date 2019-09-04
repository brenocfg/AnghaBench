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
struct TYPE_3__ {int /*<<< orphan*/ * task_debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  ads_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,void*) ; 

void
machine_task_terminate(task_t task)
{
	if (task) {
		void *task_debug;

		task_debug = task->task_debug;
		if (task_debug != NULL) {
			task->task_debug = NULL;
			zfree(ads_zone, task_debug);
		}	 
	}
}