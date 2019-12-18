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
typedef  unsigned long u32 ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_CAUSE ; 
 unsigned long BRIDGE_INT_TIMER1 ; 
 unsigned long BRIDGE_INT_TIMER1_CLR ; 
 int /*<<< orphan*/  BRIDGE_MASK ; 
 int ETIME ; 
 unsigned long TIMER1_EN ; 
 unsigned long TIMER1_RELOAD_EN ; 
 int /*<<< orphan*/  TIMER1_VAL ; 
 int /*<<< orphan*/  TIMER_CTRL ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
orion_clkevt_next_event(unsigned long delta, struct clock_event_device *dev)
{
	unsigned long flags;
	u32 u;

	if (delta == 0)
		return -ETIME;

	local_irq_save(flags);

	/*
	 * Clear and enable clockevent timer interrupt.
	 */
	writel(BRIDGE_INT_TIMER1_CLR, BRIDGE_CAUSE);

	u = readl(BRIDGE_MASK);
	u |= BRIDGE_INT_TIMER1;
	writel(u, BRIDGE_MASK);

	/*
	 * Setup new clockevent timer value.
	 */
	writel(delta, TIMER1_VAL);

	/*
	 * Enable the timer.
	 */
	u = readl(TIMER_CTRL);
	u = (u & ~TIMER1_RELOAD_EN) | TIMER1_EN;
	writel(u, TIMER_CTRL);

	local_irq_restore(flags);

	return 0;
}