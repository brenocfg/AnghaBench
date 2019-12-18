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
 int /*<<< orphan*/  TIF_POLLING_NRFLAG ; 
 int /*<<< orphan*/  clear_bl_bit () ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpu_sleep () ; 
 int /*<<< orphan*/  hlt_counter ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  set_bl_bit () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  start_critical_timings () ; 
 int /*<<< orphan*/  stop_critical_timings () ; 

void default_idle(void)
{
	if (!hlt_counter) {
		clear_thread_flag(TIF_POLLING_NRFLAG);
		smp_mb__after_clear_bit();
		set_bl_bit();
		stop_critical_timings();

		while (!need_resched())
			cpu_sleep();

		start_critical_timings();
		clear_bl_bit();
		set_thread_flag(TIF_POLLING_NRFLAG);
	} else
		while (!need_resched())
			cpu_relax();
}