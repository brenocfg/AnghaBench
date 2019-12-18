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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_TIMER1_CLEAR ; 
 int /*<<< orphan*/  EP93XX_TIMER4_VALUE_LOW ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 long TIMER4_TICKS_PER_JIFFY ; 
 scalar_t__ __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ last_jiffy_time ; 
 int /*<<< orphan*/  timer_tick () ; 

__attribute__((used)) static irqreturn_t ep93xx_timer_interrupt(int irq, void *dev_id)
{
	__raw_writel(1, EP93XX_TIMER1_CLEAR);
	while ((signed long)
		(__raw_readl(EP93XX_TIMER4_VALUE_LOW) - last_jiffy_time)
						>= TIMER4_TICKS_PER_JIFFY) {
		last_jiffy_time += TIMER4_TICKS_PER_JIFFY;
		timer_tick();
	}

	return IRQ_HANDLED;
}