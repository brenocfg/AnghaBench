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
struct task_pend_token {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_set_thread_policy_locked (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_policy_update_complete_unlocked (int /*<<< orphan*/ ,struct task_pend_token*) ; 

void
proc_set_thread_policy(thread_t   thread,
                       int        category,
                       int        flavor,
                       int        value)
{
	struct task_pend_token pend_token = {};

	thread_mtx_lock(thread);

	proc_set_thread_policy_locked(thread, category, flavor, value, 0, &pend_token);

	thread_mtx_unlock(thread);

	thread_policy_update_complete_unlocked(thread, &pend_token);
}