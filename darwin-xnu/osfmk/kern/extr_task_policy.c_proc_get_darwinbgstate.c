#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_3__* task_t ;
struct TYPE_7__ {scalar_t__ tep_sup_active; } ;
struct TYPE_6__ {scalar_t__ trp_apptype; int trp_boosted; scalar_t__ trp_int_darwinbg; scalar_t__ trp_ext_darwinbg; } ;
struct TYPE_8__ {TYPE_2__ effective_policy; TYPE_1__ requested_policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_FLAG_ADAPTIVE ; 
 int /*<<< orphan*/  PROC_FLAG_ADAPTIVE_IMPORTANT ; 
 int /*<<< orphan*/  PROC_FLAG_APPLICATION ; 
 int /*<<< orphan*/  PROC_FLAG_DARWINBG ; 
 int /*<<< orphan*/  PROC_FLAG_EXT_DARWINBG ; 
 int /*<<< orphan*/  PROC_FLAG_IMPORTANCE_DONOR ; 
 int /*<<< orphan*/  PROC_FLAG_IOS_APPLEDAEMON ; 
 int /*<<< orphan*/  PROC_FLAG_IOS_IMPPROMOTION ; 
 int /*<<< orphan*/  PROC_FLAG_SUPPRESSED ; 
 scalar_t__ TASK_APPTYPE_APP_DEFAULT ; 
 scalar_t__ TASK_APPTYPE_APP_TAL ; 
 scalar_t__ TASK_APPTYPE_DAEMON_ADAPTIVE ; 
 scalar_t__ TASK_APPTYPE_DAEMON_BACKGROUND ; 
 scalar_t__ task_is_importance_donor (TYPE_3__*) ; 

int
proc_get_darwinbgstate(task_t task, uint32_t * flagsp)
{
	if (task->requested_policy.trp_ext_darwinbg)
		*flagsp |= PROC_FLAG_EXT_DARWINBG;

	if (task->requested_policy.trp_int_darwinbg)
		*flagsp |= PROC_FLAG_DARWINBG;

#if CONFIG_EMBEDDED
	if (task->requested_policy.trp_apptype == TASK_APPTYPE_DAEMON_BACKGROUND)
		*flagsp |= PROC_FLAG_IOS_APPLEDAEMON;

	if (task->requested_policy.trp_apptype == TASK_APPTYPE_DAEMON_ADAPTIVE)
		*flagsp |= PROC_FLAG_IOS_IMPPROMOTION;
#endif /* CONFIG_EMBEDDED */

	if (task->requested_policy.trp_apptype == TASK_APPTYPE_APP_DEFAULT ||
	    task->requested_policy.trp_apptype == TASK_APPTYPE_APP_TAL)
		*flagsp |= PROC_FLAG_APPLICATION;

	if (task->requested_policy.trp_apptype == TASK_APPTYPE_DAEMON_ADAPTIVE)
		*flagsp |= PROC_FLAG_ADAPTIVE;

	if (task->requested_policy.trp_apptype == TASK_APPTYPE_DAEMON_ADAPTIVE &&
	    task->requested_policy.trp_boosted == 1)
		*flagsp |= PROC_FLAG_ADAPTIVE_IMPORTANT;

	if (task_is_importance_donor(task))
		*flagsp |= PROC_FLAG_IMPORTANCE_DONOR;

	if (task->effective_policy.tep_sup_active)
		*flagsp |= PROC_FLAG_SUPPRESSED;

	return(0);
}