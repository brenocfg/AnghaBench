#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  scalar_t__ task_t ;
struct task_pend_token {int dummy; } ;
struct TYPE_11__ {int thrp_qos; } ;
struct TYPE_12__ {scalar_t__ task; TYPE_1__ requested_policy; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int IMPORTANCE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMP_MAIN_THREAD_QOS ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_QOS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  proc_set_thread_policy_locked (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct task_pend_token*) ; 
 int task_compute_main_thread_qos (scalar_t__) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_policy_update_complete_unlocked (TYPE_2__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_tid (TYPE_2__*) ; 
 int /*<<< orphan*/  threquested_0 (TYPE_2__*) ; 
 int /*<<< orphan*/  threquested_1 (TYPE_2__*) ; 

void
task_set_main_thread_qos(task_t task, thread_t thread) {
	struct task_pend_token pend_token = {};

	assert(thread->task == task);

	thread_mtx_lock(thread);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(IMP_MAIN_THREAD_QOS, 0)) | DBG_FUNC_START,
	                          thread_tid(thread), threquested_0(thread), threquested_1(thread),
	                          thread->requested_policy.thrp_qos, 0);

	int primordial_qos = task_compute_main_thread_qos(task);

	proc_set_thread_policy_locked(thread, TASK_POLICY_ATTRIBUTE, TASK_POLICY_QOS,
	                              primordial_qos, 0, &pend_token);

	thread_mtx_unlock(thread);

	thread_policy_update_complete_unlocked(thread, &pend_token);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(IMP_MAIN_THREAD_QOS, 0)) | DBG_FUNC_END,
	                          thread_tid(thread), threquested_0(thread), threquested_1(thread),
	                          primordial_qos, 0);
}