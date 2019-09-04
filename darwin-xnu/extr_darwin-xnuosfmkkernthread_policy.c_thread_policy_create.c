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
typedef  TYPE_1__* thread_t ;
struct task_pend_token {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  base_pri; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int IMPORTANCE_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMP_UPDATE ; 
 int IMP_UPDATE_TASK_CREATE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TASK_POLICY_THREAD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  theffective_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  theffective_1 (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_policy_update_internal_spinlocked (TYPE_1__*,int /*<<< orphan*/ ,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_tid (TYPE_1__*) ; 

void
thread_policy_create(thread_t thread)
{
	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(IMP_UPDATE, (IMP_UPDATE_TASK_CREATE | TASK_POLICY_THREAD))) | DBG_FUNC_START,
	                          thread_tid(thread), theffective_0(thread),
	                          theffective_1(thread), thread->base_pri, 0);

	/* We pass a pend token but ignore it */
	struct task_pend_token pend_token = {};

	thread_policy_update_internal_spinlocked(thread, TRUE, &pend_token);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(IMP_UPDATE, (IMP_UPDATE_TASK_CREATE | TASK_POLICY_THREAD))) | DBG_FUNC_END,
	                          thread_tid(thread), theffective_0(thread),
	                          theffective_1(thread), thread->base_pri, 0);
}