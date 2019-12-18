#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lockdep_recursion; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  debug_locks ; 
 int /*<<< orphan*/  lockdep_lock ; 

__attribute__((used)) static int graph_lock(void)
{
	__raw_spin_lock(&lockdep_lock);
	/*
	 * Make sure that if another CPU detected a bug while
	 * walking the graph we dont change it (while the other
	 * CPU is busy printing out stuff with the graph lock
	 * dropped already)
	 */
	if (!debug_locks) {
		__raw_spin_unlock(&lockdep_lock);
		return 0;
	}
	/* prevent any recursions within lockdep from causing deadlocks */
	current->lockdep_recursion++;
	return 1;
}