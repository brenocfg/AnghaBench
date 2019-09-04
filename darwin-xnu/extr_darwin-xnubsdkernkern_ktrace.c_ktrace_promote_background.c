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

/* Variables and functions */
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KTRACE_STATE_BG ; 
 scalar_t__ KTRACE_STATE_OFF ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ktrace_background_available_notify_user () ; 
 int /*<<< orphan*/  ktrace_release_ownership () ; 
 scalar_t__ ktrace_state ; 
 int should_notify_on_init ; 

__attribute__((used)) static void
ktrace_promote_background(void)
{
	assert(ktrace_state != KTRACE_STATE_BG);

	/*
	 * Remember to send a background available notification on the next init
	 * if the notification failed (meaning no task holds the receive right
	 * for the host special port).
	 */
	if (ktrace_background_available_notify_user() == KERN_FAILURE) {
		should_notify_on_init = true;
	} else {
		should_notify_on_init = false;
	}

	ktrace_release_ownership();
	ktrace_state = KTRACE_STATE_OFF;
}