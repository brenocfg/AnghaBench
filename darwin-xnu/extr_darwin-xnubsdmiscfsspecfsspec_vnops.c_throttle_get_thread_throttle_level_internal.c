#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uthread_t ;
struct TYPE_3__ {scalar_t__ uu_throttle_bc; } ;

/* Variables and functions */
 int THROTTLE_LEVEL_TIER3 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int timer_get_user_idle_level () ; 

__attribute__((used)) static int
throttle_get_thread_throttle_level_internal(uthread_t ut, int io_tier) {
	int thread_throttle_level = io_tier;
	int user_idle_level;

	assert(ut != NULL);

	/* Bootcache misses should always be throttled */
	if (ut->uu_throttle_bc)
		thread_throttle_level = THROTTLE_LEVEL_TIER3;

	/*
	 * Issue tier3 I/O as tier2 when the user is idle
	 * to allow maintenance tasks to make more progress.
	 *
	 * Assume any positive idle level is enough... for now it's
	 * only ever 0 or 128 but this is not defined anywhere.
	 */
	if (thread_throttle_level >= THROTTLE_LEVEL_TIER3) {
		user_idle_level = timer_get_user_idle_level();
		if (user_idle_level > 0) {
			thread_throttle_level--;
		}
	}

	return (thread_throttle_level);
}