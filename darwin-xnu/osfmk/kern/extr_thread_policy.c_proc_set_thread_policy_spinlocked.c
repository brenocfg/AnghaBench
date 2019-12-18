#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  task_pend_token_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  FALSE ; 
 int IMPORTANCE_CODE (int,int) ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int TASK_POLICY_THREAD ; 
 int /*<<< orphan*/  thread_policy_update_spinlocked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_set_requested_policy_spinlocked (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  threquested_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  threquested_1 (int /*<<< orphan*/ ) ; 
 int tpending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
proc_set_thread_policy_spinlocked(thread_t          thread,
                                  int               category,
                                  int               flavor,
                                  int               value,
                                  int               value2,
                                  task_pend_token_t pend_token)
{
	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(flavor, (category | TASK_POLICY_THREAD))) | DBG_FUNC_START,
	                          thread_tid(thread), threquested_0(thread),
	                          threquested_1(thread), value, 0);

	thread_set_requested_policy_spinlocked(thread, category, flavor, value, value2);

	thread_policy_update_spinlocked(thread, FALSE, pend_token);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(flavor, (category | TASK_POLICY_THREAD))) | DBG_FUNC_END,
	                          thread_tid(thread), threquested_0(thread),
	                          threquested_1(thread), tpending(pend_token), 0);
}