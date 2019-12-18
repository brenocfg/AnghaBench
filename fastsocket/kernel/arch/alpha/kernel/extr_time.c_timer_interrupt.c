#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  void* __u32 ;
struct TYPE_4__ {void* last_time; unsigned long scaled_ticks_per_cycle; unsigned long partial_tick; scalar_t__ last_rtc_update; } ;
struct TYPE_3__ {scalar_t__ tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_PROFILING ; 
 unsigned long FIX_SHIFT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TICK_SIZE ; 
 int /*<<< orphan*/  do_timer (long) ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 scalar_t__ ntp_synced () ; 
 int /*<<< orphan*/  profile_tick (int /*<<< orphan*/ ) ; 
 void* rpcc () ; 
 int set_rtc_mmss (scalar_t__) ; 
 TYPE_2__ state ; 
 int /*<<< orphan*/  update_process_times (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ xtime ; 
 int /*<<< orphan*/  xtime_lock ; 

irqreturn_t timer_interrupt(int irq, void *dev)
{
	unsigned long delta;
	__u32 now;
	long nticks;

#ifndef CONFIG_SMP
	/* Not SMP, do kernel PC profiling here.  */
	profile_tick(CPU_PROFILING);
#endif

	write_seqlock(&xtime_lock);

	/*
	 * Calculate how many ticks have passed since the last update,
	 * including any previous partial leftover.  Save any resulting
	 * fraction for the next pass.
	 */
	now = rpcc();
	delta = now - state.last_time;
	state.last_time = now;
	delta = delta * state.scaled_ticks_per_cycle + state.partial_tick;
	state.partial_tick = delta & ((1UL << FIX_SHIFT) - 1); 
	nticks = delta >> FIX_SHIFT;

	if (nticks)
		do_timer(nticks);

	/*
	 * If we have an externally synchronized Linux clock, then update
	 * CMOS clock accordingly every ~11 minutes. Set_rtc_mmss() has to be
	 * called as close as possible to 500 ms before the new second starts.
	 */
	if (ntp_synced()
	    && xtime.tv_sec > state.last_rtc_update + 660
	    && xtime.tv_nsec >= 500000 - ((unsigned) TICK_SIZE) / 2
	    && xtime.tv_nsec <= 500000 + ((unsigned) TICK_SIZE) / 2) {
		int tmp = set_rtc_mmss(xtime.tv_sec);
		state.last_rtc_update = xtime.tv_sec - (tmp ? 600 : 0);
	}

	write_sequnlock(&xtime_lock);

#ifndef CONFIG_SMP
	while (nticks--)
		update_process_times(user_mode(get_irq_regs()));
#endif

	return IRQ_HANDLED;
}