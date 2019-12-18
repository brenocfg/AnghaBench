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
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 
 int ktrace_keep_ownership_on_reset ; 
 int /*<<< orphan*/  ktrace_set_invalid_owning_pid () ; 
 int /*<<< orphan*/  ktrace_set_owning_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (int /*<<< orphan*/ ) ; 

int
ktrace_set_owning_pid(int pid)
{
	ktrace_assert_lock_held();

	/* allow user space to successfully unset owning pid */
	if (pid == -1) {
		ktrace_set_invalid_owning_pid();
		return 0;
	}

	/* use ktrace_reset or ktrace_release_ownership, not this */
	if (pid == 0) {
		ktrace_set_invalid_owning_pid();
		return EINVAL;
	}

	proc_t p = proc_find(pid);
	if (!p) {
		ktrace_set_invalid_owning_pid();
		return ESRCH;
	}

	ktrace_keep_ownership_on_reset = true;
	ktrace_set_owning_proc(p);

	proc_rele(p);
	return 0;
}