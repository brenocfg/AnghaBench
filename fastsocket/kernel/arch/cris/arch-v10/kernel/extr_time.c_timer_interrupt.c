#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int IO_FIELD (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IO_STATE (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int* R_TIMER_CTRL ; 
 int /*<<< orphan*/  c6250kHz ; 
 int /*<<< orphan*/  cascade0 ; 
 int /*<<< orphan*/  clksel0 ; 
 int /*<<< orphan*/  clksel1 ; 
 int /*<<< orphan*/  clr ; 
 int /*<<< orphan*/  cris_do_profile (struct pt_regs*) ; 
 int /*<<< orphan*/  do_timer (int) ; 
 struct pt_regs* get_irq_regs () ; 
 int /*<<< orphan*/  i0 ; 
 int /*<<< orphan*/  i1 ; 
 scalar_t__ last_rtc_update ; 
 scalar_t__ ntp_synced () ; 
 int r_timer_ctrl_shadow ; 
 int /*<<< orphan*/  reset_watchdog () ; 
 int /*<<< orphan*/  run ; 
 scalar_t__ set_rtc_mmss (scalar_t__) ; 
 int tick_nsec ; 
 int /*<<< orphan*/  timerdiv0 ; 
 int /*<<< orphan*/  timerdiv1 ; 
 int /*<<< orphan*/  tm0 ; 
 int /*<<< orphan*/  tm1 ; 
 int /*<<< orphan*/  update_process_times (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 
 TYPE_1__ xtime ; 

__attribute__((used)) static inline irqreturn_t
timer_interrupt(int irq, void *dev_id)
{
	struct pt_regs *regs = get_irq_regs();
	/* acknowledge the timer irq */

#ifdef USE_CASCADE_TIMERS
	*R_TIMER_CTRL =
		IO_FIELD( R_TIMER_CTRL, timerdiv1, 0) |
		IO_FIELD( R_TIMER_CTRL, timerdiv0, 0) |
		IO_STATE( R_TIMER_CTRL, i1, clr) |
		IO_STATE( R_TIMER_CTRL, tm1, run) |
		IO_STATE( R_TIMER_CTRL, clksel1, cascade0) |
		IO_STATE( R_TIMER_CTRL, i0, clr) |
		IO_STATE( R_TIMER_CTRL, tm0, run) |
		IO_STATE( R_TIMER_CTRL, clksel0, c6250kHz);
#else
	*R_TIMER_CTRL = r_timer_ctrl_shadow | 
		IO_STATE(R_TIMER_CTRL, i0, clr);
#endif

	/* reset watchdog otherwise it resets us! */
	reset_watchdog();
	
	/* Update statistics. */
	update_process_times(user_mode(regs));

	/* call the real timer interrupt handler */

	do_timer(1);
	
        cris_do_profile(regs); /* Save profiling information */

	/*
	 * If we have an externally synchronized Linux clock, then update
	 * CMOS clock accordingly every ~11 minutes. Set_rtc_mmss() has to be
	 * called as close as possible to 500 ms before the new second starts.
	 *
	 * The division here is not time critical since it will run once in 
	 * 11 minutes
	 */
	if (ntp_synced() &&
	    xtime.tv_sec > last_rtc_update + 660 &&
	    (xtime.tv_nsec / 1000) >= 500000 - (tick_nsec / 1000) / 2 &&
	    (xtime.tv_nsec / 1000) <= 500000 + (tick_nsec / 1000) / 2) {
		if (set_rtc_mmss(xtime.tv_sec) == 0)
			last_rtc_update = xtime.tv_sec;
		else
			last_rtc_update = xtime.tv_sec - 600; /* do it again in 60 s */
	}
        return IRQ_HANDLED;
}