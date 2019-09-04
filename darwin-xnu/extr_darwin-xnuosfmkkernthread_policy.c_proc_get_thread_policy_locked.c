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
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int thread_get_requested_policy_spinlocked (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
proc_get_thread_policy_locked(thread_t   thread,
                              int        category,
                              int        flavor,
                              int*       value2)
{
	int value = 0;

	spl_t s = splsched();
	thread_lock(thread);

	value = thread_get_requested_policy_spinlocked(thread, category, flavor, value2);

	thread_unlock(thread);
	splx(s);

	return value;
}