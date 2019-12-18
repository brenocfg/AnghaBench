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
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ U300_TIMER_APP_GPT1IA ; 
 int /*<<< orphan*/  U300_TIMER_APP_GPT1IA_IRQ_ACK ; 
 scalar_t__ U300_TIMER_APP_VBASE ; 
 struct clock_event_device clockevent_u300_1mhz ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t u300_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *evt = &clockevent_u300_1mhz;
	/* ACK/Clear timer IRQ for the APP GPT1 Timer */
	writel(U300_TIMER_APP_GPT1IA_IRQ_ACK,
		U300_TIMER_APP_VBASE + U300_TIMER_APP_GPT1IA);
	evt->event_handler(evt);
	return IRQ_HANDLED;
}