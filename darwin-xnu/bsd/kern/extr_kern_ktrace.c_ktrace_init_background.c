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
typedef  int errno_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KTRACE_STATE_BG ; 
 scalar_t__ KTRACE_STATE_OFF ; 
 int /*<<< orphan*/  PRIV_KTRACE_BACKGROUND ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 
 scalar_t__ ktrace_background_available_notify_user () ; 
 int /*<<< orphan*/  ktrace_bg_pid ; 
 int /*<<< orphan*/  ktrace_bg_unique_id ; 
 int /*<<< orphan*/  ktrace_set_owning_proc (int /*<<< orphan*/ ) ; 
 scalar_t__ ktrace_state ; 
 int priv_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_uniqueid (int /*<<< orphan*/ ) ; 
 int should_notify_on_init ; 

__attribute__((used)) static errno_t
ktrace_init_background(void)
{
	int err = 0;

	ktrace_assert_lock_held();

	if ((err = priv_check_cred(kauth_cred_get(), PRIV_KTRACE_BACKGROUND, 0))) {
		return err;
	}

	/*
	 * When a background tool first checks in, send a notification if ktrace
	 * is available.
	 */
	if (should_notify_on_init) {
		if (ktrace_state == KTRACE_STATE_OFF) {
			/*
			 * This notification can only fail if a process does not
			 * hold the receive right for the host special port.
			 * Return an error and don't make the current process
			 * the background tool.
			 */
			if (ktrace_background_available_notify_user() == KERN_FAILURE) {
				return EINVAL;
			}
		}
		should_notify_on_init = false;
	}

	proc_t p = current_proc();

	ktrace_bg_unique_id = proc_uniqueid(p);
	ktrace_bg_pid = proc_pid(p);

	if (ktrace_state == KTRACE_STATE_BG) {
		ktrace_set_owning_proc(p);
	}

	return 0;
}