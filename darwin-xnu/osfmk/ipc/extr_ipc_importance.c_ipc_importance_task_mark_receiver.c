#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_importance_task_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {scalar_t__ iit_assertcnt; scalar_t__ iit_externcnt; scalar_t__ iit_externdrop; scalar_t__ iit_denap; int iit_receiver; } ;

/* Variables and functions */
 scalar_t__ IIT_EXTERN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 
 int /*<<< orphan*/  panic (char*) ; 

void
ipc_importance_task_mark_receiver(ipc_importance_task_t task_imp, boolean_t receiving)
{
	assert(task_imp != NULL);	

	ipc_importance_lock();
	if (receiving) {
		assert(task_imp->iit_assertcnt == 0);
		assert(task_imp->iit_externcnt == 0);
		assert(task_imp->iit_externdrop == 0);
		assert(task_imp->iit_denap == 0);
		task_imp->iit_receiver = 1;  /* task can receive importance boost */
	} else if (task_imp->iit_receiver) {
		assert(task_imp->iit_denap == 0);
		if (task_imp->iit_assertcnt != 0 || IIT_EXTERN(task_imp) != 0) {
			panic("disabling imp_receiver on task with pending importance boosts!");
		}
		task_imp->iit_receiver = 0;
	}
	ipc_importance_unlock();
}