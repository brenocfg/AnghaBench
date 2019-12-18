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
typedef  int uint32_t ;

/* Variables and functions */
 int KTRACE_KDEBUG ; 
 int KTRACE_KPERF ; 
 scalar_t__ KTRACE_STATE_BG ; 
 scalar_t__ KTRACE_STATE_FG ; 
 scalar_t__ KTRACE_STATE_OFF ; 
 int /*<<< orphan*/  kdebug_reset () ; 
 int /*<<< orphan*/  kperf_reset () ; 
 int ktrace_active_mask ; 
 int /*<<< orphan*/  ktrace_keep_ownership_on_reset ; 
 int /*<<< orphan*/  ktrace_promote_background () ; 
 int /*<<< orphan*/  ktrace_release_ownership () ; 
 scalar_t__ ktrace_state ; 
 int should_notify_on_init ; 

__attribute__((used)) static void
ktrace_reset_internal(uint32_t reset_mask)
{
	if (!ktrace_keep_ownership_on_reset) {
		ktrace_active_mask &= ~reset_mask;
	}

	if (reset_mask & KTRACE_KPERF) {
		kperf_reset();
	}
	if (reset_mask & KTRACE_KDEBUG) {
		kdebug_reset();
	}

	if (ktrace_active_mask == 0) {
		if (ktrace_state == KTRACE_STATE_FG) {
			/* transition from foreground to background */
			ktrace_promote_background();
		} else if (ktrace_state == KTRACE_STATE_BG) {
			/* background tool is resetting ktrace */
			should_notify_on_init = true;
			ktrace_release_ownership();
			ktrace_state = KTRACE_STATE_OFF;
		}
	}
}