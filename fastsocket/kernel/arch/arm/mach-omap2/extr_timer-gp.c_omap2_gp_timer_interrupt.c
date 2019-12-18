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
struct omap_dm_timer {int dummy; } ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  OMAP_TIMER_INT_OVERFLOW ; 
 struct clock_event_device clockevent_gpt ; 
 int /*<<< orphan*/  omap_dm_timer_write_status (struct omap_dm_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 

__attribute__((used)) static irqreturn_t omap2_gp_timer_interrupt(int irq, void *dev_id)
{
	struct omap_dm_timer *gpt = (struct omap_dm_timer *)dev_id;
	struct clock_event_device *evt = &clockevent_gpt;

	omap_dm_timer_write_status(gpt, OMAP_TIMER_INT_OVERFLOW);

	evt->event_handler(evt);
	return IRQ_HANDLED;
}