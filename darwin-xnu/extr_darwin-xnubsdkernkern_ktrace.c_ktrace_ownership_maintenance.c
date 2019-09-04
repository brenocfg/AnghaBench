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
typedef  int /*<<< orphan*/ * proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 
 int /*<<< orphan*/  ktrace_owning_pid ; 
 scalar_t__ ktrace_owning_unique_id ; 
 int /*<<< orphan*/  ktrace_release_ownership () ; 
 int /*<<< orphan*/ * proc_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_rele (int /*<<< orphan*/ *) ; 
 scalar_t__ proc_uniqueid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ktrace_ownership_maintenance(void)
{
	ktrace_assert_lock_held();

	/* do nothing if ktrace is not owned */
	if (ktrace_owning_unique_id == 0) {
		return;
	}

	/* reset ownership if process cannot be found */

	proc_t owning_proc = proc_find(ktrace_owning_pid);

	if (owning_proc != NULL) {
		/* make sure the pid was not recycled */
		if (proc_uniqueid(owning_proc) != ktrace_owning_unique_id) {
			ktrace_release_ownership();
		}

		proc_rele(owning_proc);
	} else {
		ktrace_release_ownership();
	}
}