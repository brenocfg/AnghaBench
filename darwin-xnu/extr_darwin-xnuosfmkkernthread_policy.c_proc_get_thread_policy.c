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

/* Variables and functions */
 int proc_get_thread_policy_locked (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_mtx_unlock (int /*<<< orphan*/ ) ; 

int
proc_get_thread_policy(thread_t   thread,
                       int        category,
                       int        flavor)
{
	int value = 0;
	thread_mtx_lock(thread);
	value = proc_get_thread_policy_locked(thread, category, flavor, NULL);
	thread_mtx_unlock(thread);
	return value;
}