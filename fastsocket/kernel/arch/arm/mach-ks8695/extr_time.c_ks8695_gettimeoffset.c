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
 unsigned long CLOCK_TICK_RATE ; 
 unsigned long HZ ; 
 scalar_t__ KS8695_INTST ; 
 int KS8695_IRQ_TIMER1 ; 
 scalar_t__ KS8695_IRQ_VA ; 
 scalar_t__ KS8695_T1PD ; 
 scalar_t__ KS8695_T1TC ; 
 scalar_t__ KS8695_TMR_VA ; 
 unsigned long LATCH ; 
 int __raw_readl (scalar_t__) ; 
 int tick_nsec ; 

__attribute__((used)) static unsigned long ks8695_gettimeoffset (void)
{
	unsigned long elapsed, tick2, intpending;

	/*
	 * Get the current number of ticks.  Note that there is a race
	 * condition between us reading the timer and checking for an
	 * interrupt.  We solve this by ensuring that the counter has not
	 * reloaded between our two reads.
	 */
	elapsed = __raw_readl(KS8695_TMR_VA + KS8695_T1TC) + __raw_readl(KS8695_TMR_VA + KS8695_T1PD);
	do {
		tick2 = elapsed;
		intpending = __raw_readl(KS8695_IRQ_VA + KS8695_INTST) & (1 << KS8695_IRQ_TIMER1);
		elapsed = __raw_readl(KS8695_TMR_VA + KS8695_T1TC) + __raw_readl(KS8695_TMR_VA + KS8695_T1PD);
	} while (elapsed > tick2);

	/* Convert to number of ticks expired (not remaining) */
	elapsed = (CLOCK_TICK_RATE / HZ) - elapsed;

	/* Is interrupt pending?  If so, then timer has been reloaded already. */
	if (intpending)
		elapsed += (CLOCK_TICK_RATE / HZ);

	/* Convert ticks to usecs */
	return (unsigned long)(elapsed * (tick_nsec / 1000)) / LATCH;
}