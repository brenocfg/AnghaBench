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
 int /*<<< orphan*/  OIER ; 
 int /*<<< orphan*/  OIER_E0 ; 
 int /*<<< orphan*/  OSSR ; 
 int /*<<< orphan*/  OSSR_M0 ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 

__attribute__((used)) static irqreturn_t sa1100_ost0_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *c = dev_id;

	/* Disarm the compare/match, signal the event. */
	OIER &= ~OIER_E0;
	OSSR = OSSR_M0;
	c->event_handler(c);

	return IRQ_HANDLED;
}