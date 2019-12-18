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
typedef  int /*<<< orphan*/  task_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ force_all_ctrs ; 
 int kpc_calling_pm ; 
 scalar_t__ kpc_get_force_all_ctrs () ; 
 int /*<<< orphan*/  kpc_pm_handler (scalar_t__) ; 
 int /*<<< orphan*/  kpc_task_get_forced_all_ctrs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_task_set_forced_all_ctrs (int /*<<< orphan*/ ,scalar_t__) ; 

int
kpc_force_all_ctrs(task_t task, int val)
{
	boolean_t new_state = val ? TRUE : FALSE;
	boolean_t old_state = kpc_get_force_all_ctrs();

	/*
	 * Refuse to do the operation if the counters are already forced by
	 * another task.
	 */
	if (kpc_get_force_all_ctrs() && !kpc_task_get_forced_all_ctrs(task))
		return EACCES;

	/* nothing to do if the state is not changing */
	if (old_state == new_state)
		return 0;

	/* notify the power manager */
	if (kpc_pm_handler) {
#if MACH_ASSERT
		kpc_calling_pm = true;
#endif /* MACH_ASSERT */
		kpc_pm_handler( new_state ? FALSE : TRUE );
#if MACH_ASSERT
		kpc_calling_pm = false;
#endif /* MACH_ASSERT */
	}

	/*
	 * This is a force -- ensure that counters are forced, even if power
	 * management fails to acknowledge it.
	 */
	if (force_all_ctrs != new_state) {
		force_all_ctrs = new_state;
	}

	/* update the task bits */
	kpc_task_set_forced_all_ctrs(task, new_state);

	return 0;
}