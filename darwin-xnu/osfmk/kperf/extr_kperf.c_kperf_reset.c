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
 int /*<<< orphan*/  kperf_action_reset () ; 
 int /*<<< orphan*/  kperf_kdbg_cswitch_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kperf_kdebug_reset () ; 
 int /*<<< orphan*/  kperf_lazy_reset () ; 
 int /*<<< orphan*/  kperf_sampling_disable () ; 
 int /*<<< orphan*/  kperf_set_lightweight_pet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kperf_timer_reset () ; 

void
kperf_reset(void)
{
	/* turn off sampling first */
	(void)kperf_sampling_disable();

	/* cleanup miscellaneous configuration first */
	kperf_lazy_reset();
	(void)kperf_kdbg_cswitch_set(0);
	(void)kperf_set_lightweight_pet(0);
	kperf_kdebug_reset();

	/* timers, which require actions, first */
	kperf_timer_reset();
	kperf_action_reset();
}