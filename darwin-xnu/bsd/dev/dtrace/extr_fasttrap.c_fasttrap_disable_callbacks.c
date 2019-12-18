#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cpu_ft_lock; struct TYPE_3__* cpu_next; } ;
typedef  TYPE_1__ dtrace_cpu_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__* CPU ; 
 int /*<<< orphan*/ * dtrace_pid_probe_ptr ; 
 int /*<<< orphan*/ * dtrace_return_probe_ptr ; 
 int /*<<< orphan*/  fasttrap_count_mtx ; 
 scalar_t__ fasttrap_pid_count ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_exclusive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fasttrap_disable_callbacks(void)
{
	//ASSERT(MUTEX_HELD(&cpu_lock));

	lck_mtx_lock(&fasttrap_count_mtx);
	ASSERT(fasttrap_pid_count > 0);
	fasttrap_pid_count--;
	if (fasttrap_pid_count == 0) {
		dtrace_cpu_t *cur, *cpu = CPU;

		/*
		 * APPLE NOTE: This loop seems broken, it touches every CPU
		 * but the one we're actually running on. Need to ask Sun folks
		 * if that is safe. Scenario is this: We're running on CPU A,
		 * and lock all but A. Then we get preempted, and start running
		 * on CPU B. A probe fires on A, and is allowed to enter. BOOM!
		 */
		for (cur = cpu->cpu_next; cur != cpu; cur = cur->cpu_next) {
			lck_rw_lock_exclusive(&cur->cpu_ft_lock);
			// rw_enter(&cur->cpu_ft_lock, RW_WRITER);
		}

		dtrace_pid_probe_ptr = NULL;
		dtrace_return_probe_ptr = NULL;

		for (cur = cpu->cpu_next; cur != cpu; cur = cur->cpu_next) {
			lck_rw_unlock_exclusive(&cur->cpu_ft_lock);
			// rw_exit(&cur->cpu_ft_lock);
		}
	}
	lck_mtx_unlock(&fasttrap_count_mtx);
}