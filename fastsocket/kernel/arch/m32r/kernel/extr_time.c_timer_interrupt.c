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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_PROFILING ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TICK_SIZE ; 
 int /*<<< orphan*/  do_timer (int) ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 scalar_t__ last_rtc_update ; 
 scalar_t__ ntp_synced () ; 
 int /*<<< orphan*/  profile_tick (int /*<<< orphan*/ ) ; 
 scalar_t__ set_rtc_mmss (scalar_t__) ; 
 int /*<<< orphan*/  smp_local_timer_interrupt () ; 
 int /*<<< orphan*/  smp_send_timer () ; 
 int /*<<< orphan*/  update_process_times (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ xtime ; 
 int /*<<< orphan*/  xtime_lock ; 

__attribute__((used)) static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
#ifndef CONFIG_SMP
	profile_tick(CPU_PROFILING);
#endif
	/* XXX FIXME. Uh, the xtime_lock should be held here, no? */
	do_timer(1);

#ifndef CONFIG_SMP
	update_process_times(user_mode(get_irq_regs()));
#endif
	/*
	 * If we have an externally synchronized Linux clock, then update
	 * CMOS clock accordingly every ~11 minutes. Set_rtc_mmss() has to be
	 * called as close as possible to 500 ms before the new second starts.
	 */
	write_seqlock(&xtime_lock);
	if (ntp_synced()
		&& xtime.tv_sec > last_rtc_update + 660
		&& (xtime.tv_nsec / 1000) >= 500000 - ((unsigned)TICK_SIZE) / 2
		&& (xtime.tv_nsec / 1000) <= 500000 + ((unsigned)TICK_SIZE) / 2)
	{
		if (set_rtc_mmss(xtime.tv_sec) == 0)
			last_rtc_update = xtime.tv_sec;
		else	/* do it again in 60 s */
			last_rtc_update = xtime.tv_sec - 600;
	}
	write_sequnlock(&xtime_lock);
	/* As we return to user mode fire off the other CPU schedulers..
	   this is basically because we don't yet share IRQ's around.
	   This message is rigged to be safe on the 386 - basically it's
	   a hack, so don't look closely for now.. */

#ifdef CONFIG_SMP
	smp_local_timer_interrupt();
	smp_send_timer();
#endif

	return IRQ_HANDLED;
}