#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_ldt_t ;
typedef  TYPE_1__* task_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* task_destroy ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {scalar_t__ i386_ldt; int /*<<< orphan*/ * task_debug; int /*<<< orphan*/ * hv_task_target; } ;

/* Variables and functions */
 TYPE_3__ hv_callbacks ; 
 int /*<<< orphan*/  ids_zone ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_ldt_free (scalar_t__) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,void*) ; 

void
machine_task_terminate(task_t task)
{
	if (task) {
		user_ldt_t user_ldt;
		void *task_debug;

#if HYPERVISOR
		if (task->hv_task_target) {
			hv_callbacks.task_destroy(task->hv_task_target);
			task->hv_task_target = NULL;
		}
#endif

		user_ldt = task->i386_ldt;
		if (user_ldt != 0) {
			task->i386_ldt = 0;
			user_ldt_free(user_ldt);
		}

		task_debug = task->task_debug;
		if (task_debug != NULL) {
			task->task_debug = NULL;
			zfree(ids_zone, task_debug);
		}	 
	}
}