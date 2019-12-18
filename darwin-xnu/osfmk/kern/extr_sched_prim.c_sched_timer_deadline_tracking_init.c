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
 int /*<<< orphan*/  TIMER_DEADLINE_TRACKING_BIN_1_DEFAULT ; 
 int /*<<< orphan*/  TIMER_DEADLINE_TRACKING_BIN_2_DEFAULT ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_deadline_tracking_bin_1 ; 
 int /*<<< orphan*/  timer_deadline_tracking_bin_2 ; 

__attribute__((used)) static void
sched_timer_deadline_tracking_init(void) {
	nanoseconds_to_absolutetime(TIMER_DEADLINE_TRACKING_BIN_1_DEFAULT, &timer_deadline_tracking_bin_1);
	nanoseconds_to_absolutetime(TIMER_DEADLINE_TRACKING_BIN_2_DEFAULT, &timer_deadline_tracking_bin_2);
}