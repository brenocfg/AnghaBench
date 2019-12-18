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
 scalar_t__ AT91_TC ; 
 scalar_t__ AT91_TC_CLK1BASE ; 
 scalar_t__ AT91_TC_SR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  at91_sys_read (scalar_t__) ; 
 int /*<<< orphan*/  timer_tick () ; 

__attribute__((used)) static irqreturn_t at91x40_timer_interrupt(int irq, void *dev_id)
{
	at91_sys_read(AT91_TC + AT91_TC_CLK1BASE + AT91_TC_SR);
	timer_tick();
	return IRQ_HANDLED;
}