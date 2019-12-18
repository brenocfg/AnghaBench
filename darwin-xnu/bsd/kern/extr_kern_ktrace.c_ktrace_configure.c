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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 scalar_t__ KTRACE_STATE_BG ; 
 scalar_t__ KTRACE_STATE_FG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrace_active_mask ; 
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 
 scalar_t__ ktrace_bg_unique_id ; 
 int ktrace_owner_kernel ; 
 int /*<<< orphan*/  ktrace_ownership_maintenance () ; 
 scalar_t__ ktrace_owning_unique_id ; 
 int /*<<< orphan*/  ktrace_set_owning_proc (int /*<<< orphan*/ ) ; 
 scalar_t__ ktrace_state ; 
 scalar_t__ proc_uniqueid (int /*<<< orphan*/ ) ; 

int
ktrace_configure(uint32_t config_mask)
{
	ktrace_assert_lock_held();
	assert(config_mask != 0);

	proc_t p = current_proc();

	/* if process clearly owns ktrace, allow */
	if (proc_uniqueid(p) == ktrace_owning_unique_id) {
		ktrace_active_mask |= config_mask;
		return 0;
	}

	/* background configure while foreground is active is not allowed */
	if (proc_uniqueid(p) == ktrace_bg_unique_id &&
	    ktrace_state == KTRACE_STATE_FG)
	{
		return EBUSY;
	}

	ktrace_ownership_maintenance();

	/* allow process to gain control when unowned or background */
	if (ktrace_owning_unique_id == 0 || ktrace_state == KTRACE_STATE_BG) {
		if (!kauth_cred_issuser(kauth_cred_get())) {
			return EPERM;
		}

		ktrace_owner_kernel = false;
		ktrace_set_owning_proc(p);
		ktrace_active_mask |= config_mask;
		return 0;
	}

	/* owned by an existing, different process */
	return EBUSY;
}