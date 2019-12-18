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
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TIMER1_VA_BASE ; 
 scalar_t__ TIMER_INTCLR ; 
 int /*<<< orphan*/  timer_tick () ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t
integrator_timer_interrupt(int irq, void *dev_id)
{
	/*
	 * clear the interrupt
	 */
	writel(1, TIMER1_VA_BASE + TIMER_INTCLR);

	timer_tick();

	return IRQ_HANDLED;
}