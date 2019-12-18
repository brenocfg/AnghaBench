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
 int EINTR ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 scalar_t__ disable_vt_switch ; 
 int fg_console ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  release_console_sem () ; 
 scalar_t__ set_console (unsigned int) ; 
 scalar_t__ vc_allocate (unsigned int) ; 
 scalar_t__ vt_waitactive (unsigned int) ; 

int vt_move_to_console(unsigned int vt, int alloc)
{
	int prev;

	acquire_console_sem();
	/* Graphics mode - up to X */
	if (disable_vt_switch) {
		release_console_sem();
		return 0;
	}
	prev = fg_console;

	if (alloc && vc_allocate(vt)) {
		/* we can't have a free VC for now. Too bad,
		 * we don't want to mess the screen for now. */
		release_console_sem();
		return -ENOSPC;
	}

	if (set_console(vt)) {
		/*
		 * We're unable to switch to the SUSPEND_CONSOLE.
		 * Let the calling function know so it can decide
		 * what to do.
		 */
		release_console_sem();
		return -EIO;
	}
	release_console_sem();
	if (vt_waitactive(vt + 1)) {
		pr_debug("Suspend: Can't switch VCs.");
		return -EINTR;
	}
	return prev;
}