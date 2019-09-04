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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  kill_idle_exit_proc () ; 

boolean_t memorystatus_idle_exit_from_VM(void) {

	/*
	 * This routine should no longer be needed since we are
	 * now using jetsam bands on all platforms and so will deal
	 * with IDLE processes within the memorystatus thread itself.
	 *
	 * But we still use it because we observed that macos systems
	 * started heavy compression/swapping with a bunch of
	 * idle-exitable processes alive and doing nothing. We decided
	 * to rather kill those processes than start swapping earlier.
	 */

	return(kill_idle_exit_proc());
}