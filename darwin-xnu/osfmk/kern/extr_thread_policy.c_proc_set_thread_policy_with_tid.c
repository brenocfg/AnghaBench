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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ thread_t ;
typedef  int /*<<< orphan*/  task_t ;

/* Variables and functions */
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  proc_set_thread_policy (scalar_t__,int,int,int) ; 
 scalar_t__ task_findtid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_deallocate (scalar_t__) ; 

void
proc_set_thread_policy_with_tid(task_t     task,
                                uint64_t   tid,
                                int        category,
                                int        flavor,
                                int        value)
{
	/* takes task lock, returns ref'ed thread or NULL */
	thread_t thread = task_findtid(task, tid);

	if (thread == THREAD_NULL)
		return;

	proc_set_thread_policy(thread, category, flavor, value);

	thread_deallocate(thread);
}