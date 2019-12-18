#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_importance_task_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {scalar_t__ iit_legacy_externcnt; scalar_t__ iit_externcnt; scalar_t__ iit_legacy_externdrop; scalar_t__ iit_externdrop; scalar_t__ iit_assertcnt; char* iit_procname; int iit_bsd_pid; scalar_t__ iit_live_donor; scalar_t__ iit_donor; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IIT_EXTERN (TYPE_1__*) ; 
 scalar_t__ IIT_LEGACY_EXTERN (TYPE_1__*) ; 
 int /*<<< orphan*/  IIT_UPDATE_DROP ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ipc_importance_task_is_donor (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_importance_task_propagate_assertion_locked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int,scalar_t__) ; 

__attribute__((used)) static void
ipc_importance_reset_locked(ipc_importance_task_t task_imp, boolean_t donor)
{
	boolean_t before_donor, after_donor;

	/* remove the donor bit, live-donor bit and externalized boosts */
	before_donor = ipc_importance_task_is_donor(task_imp);
	if (donor) {
		task_imp->iit_donor = 0;
	}
	assert(IIT_LEGACY_EXTERN(task_imp) <= IIT_EXTERN(task_imp));
	assert(task_imp->iit_legacy_externcnt <= task_imp->iit_externcnt);
	assert(task_imp->iit_legacy_externdrop <= task_imp->iit_externdrop);
	task_imp->iit_externcnt -= task_imp->iit_legacy_externcnt;
	task_imp->iit_externdrop -= task_imp->iit_legacy_externdrop;

	/* assert(IIT_LEGACY_EXTERN(task_imp) <= task_imp->iit_assertcnt); */
	if (IIT_EXTERN(task_imp) < task_imp->iit_assertcnt) {
		task_imp->iit_assertcnt -= IIT_LEGACY_EXTERN(task_imp);
	} else {
		task_imp->iit_assertcnt = IIT_EXTERN(task_imp);
	}
	task_imp->iit_legacy_externcnt = 0;
	task_imp->iit_legacy_externdrop = 0;
	after_donor = ipc_importance_task_is_donor(task_imp);

#if DEVELOPMENT || DEBUG
	if (task_imp->iit_assertcnt > 0 && task_imp->iit_live_donor) {
		printf("Live donor task %s[%d] still has %d importance assertions after reset\n", 
		       task_imp->iit_procname, task_imp->iit_bsd_pid, task_imp->iit_assertcnt);
	}
#endif

	/* propagate a downstream drop if there was a change in donor status */
	if (after_donor != before_donor) {
		ipc_importance_task_propagate_assertion_locked(task_imp, IIT_UPDATE_DROP, FALSE);
	}
}