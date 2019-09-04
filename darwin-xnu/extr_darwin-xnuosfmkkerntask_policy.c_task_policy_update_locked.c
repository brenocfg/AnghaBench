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
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  task_pend_token_t ;
struct TYPE_7__ {int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  FALSE ; 
 int IMPORTANCE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMP_UPDATE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_POLICY_TASK ; 
 int /*<<< orphan*/  task_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  task_policy_update_internal_locked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teffective_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  teffective_1 (TYPE_1__*) ; 

__attribute__((used)) static void
task_policy_update_locked(task_t task, task_pend_token_t pend_token)
{
	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(IMP_UPDATE, TASK_POLICY_TASK) | DBG_FUNC_START),
	                          task_pid(task), teffective_0(task),
	                          teffective_1(task), task->priority, 0);

	task_policy_update_internal_locked(task, FALSE, pend_token);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
				  (IMPORTANCE_CODE(IMP_UPDATE, TASK_POLICY_TASK)) | DBG_FUNC_END,
				  task_pid(task), teffective_0(task),
				  teffective_1(task), task->priority, 0);
}