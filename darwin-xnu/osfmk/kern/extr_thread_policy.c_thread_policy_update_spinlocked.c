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
typedef  int /*<<< orphan*/  task_pend_token_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  base_pri; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int IMPORTANCE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMP_UPDATE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_POLICY_THREAD ; 
 int /*<<< orphan*/  theffective_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  theffective_1 (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_policy_update_internal_spinlocked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_tid (TYPE_1__*) ; 

__attribute__((used)) static void
thread_policy_update_spinlocked(thread_t thread, boolean_t recompute_priority, task_pend_token_t pend_token)
{
	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(IMP_UPDATE, TASK_POLICY_THREAD) | DBG_FUNC_START),
	                          thread_tid(thread), theffective_0(thread),
	                          theffective_1(thread), thread->base_pri, 0);

	thread_policy_update_internal_spinlocked(thread, recompute_priority, pend_token);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(IMP_UPDATE, TASK_POLICY_THREAD)) | DBG_FUNC_END,
	                          thread_tid(thread), theffective_0(thread),
	                          theffective_1(thread), thread->base_pri, 0);
}