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
 int /*<<< orphan*/  CPU_PROFILING ; 
 int /*<<< orphan*/  do_leds () ; 
 int /*<<< orphan*/  do_set_rtc () ; 
 int /*<<< orphan*/  do_timer (int) ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  profile_tick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_process_times (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xtime_lock ; 

void timer_tick(void)
{
	profile_tick(CPU_PROFILING);
	do_leds();
	do_set_rtc();
	write_seqlock(&xtime_lock);
	do_timer(1);
	write_sequnlock(&xtime_lock);
#ifndef CONFIG_SMP
	update_process_times(user_mode(get_irq_regs()));
#endif
}