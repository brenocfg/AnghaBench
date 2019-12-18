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
typedef  int u32 ;
struct clock_event_device {int dummy; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_CAUSE ; 
 int BRIDGE_INT_TIMER1 ; 
 int BRIDGE_INT_TIMER1_CLR ; 
 int /*<<< orphan*/  BRIDGE_MASK ; 
 int CLOCK_EVT_MODE_PERIODIC ; 
 int TIMER1_EN ; 
 int /*<<< orphan*/  TIMER1_RELOAD ; 
 int TIMER1_RELOAD_EN ; 
 int /*<<< orphan*/  TIMER1_VAL ; 
 int /*<<< orphan*/  TIMER_CTRL ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int ticks_per_jiffy ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
orion_clkevt_mode(enum clock_event_mode mode, struct clock_event_device *dev)
{
	unsigned long flags;
	u32 u;

	local_irq_save(flags);
	if (mode == CLOCK_EVT_MODE_PERIODIC) {
		/*
		 * Setup timer to fire at 1/HZ intervals.
		 */
		writel(ticks_per_jiffy - 1, TIMER1_RELOAD);
		writel(ticks_per_jiffy - 1, TIMER1_VAL);

		/*
		 * Enable timer interrupt.
		 */
		u = readl(BRIDGE_MASK);
		writel(u | BRIDGE_INT_TIMER1, BRIDGE_MASK);

		/*
		 * Enable timer.
		 */
		u = readl(TIMER_CTRL);
		writel(u | TIMER1_EN | TIMER1_RELOAD_EN, TIMER_CTRL);
	} else {
		/*
		 * Disable timer.
		 */
		u = readl(TIMER_CTRL);
		writel(u & ~TIMER1_EN, TIMER_CTRL);

		/*
		 * Disable timer interrupt.
		 */
		u = readl(BRIDGE_MASK);
		writel(u & ~BRIDGE_INT_TIMER1, BRIDGE_MASK);

		/*
		 * ACK pending timer interrupt.
		 */
		writel(BRIDGE_INT_TIMER1_CLR, BRIDGE_CAUSE);

	}
	local_irq_restore(flags);
}