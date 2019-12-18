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
 int /*<<< orphan*/  CPU_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TIMER_TOPSTAT ; 
 int /*<<< orphan*/  TIMER_VIRT ; 
 int /*<<< orphan*/  timer_tick () ; 

__attribute__((used)) static irqreturn_t
h7201_timer_interrupt(int irq, void *dev_id)
{
	CPU_REG (TIMER_VIRT, TIMER_TOPSTAT);
	timer_tick();

	return IRQ_HANDLED;
}