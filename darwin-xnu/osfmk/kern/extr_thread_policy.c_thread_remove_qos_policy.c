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
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_7__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  KERN_TERMINATED ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_policy_update_complete_unlocked (TYPE_1__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_remove_qos_policy_locked (TYPE_1__*,struct task_pend_token*) ; 

kern_return_t
thread_remove_qos_policy(thread_t thread)
{
	struct task_pend_token pend_token = {};

	thread_mtx_lock(thread);
	if (!thread->active) {
		thread_mtx_unlock(thread);
		return KERN_TERMINATED;
	}

	thread_remove_qos_policy_locked(thread, &pend_token);

	thread_mtx_unlock(thread);

	thread_policy_update_complete_unlocked(thread, &pend_token);

	return KERN_SUCCESS;
}