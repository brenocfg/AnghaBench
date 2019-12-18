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
 struct clock_event_device clockevent_microblaze_timer ; 
 int /*<<< orphan*/  heartbeat () ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 int /*<<< orphan*/  timer_ack () ; 

__attribute__((used)) static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *evt = &clockevent_microblaze_timer;
#ifdef CONFIG_HEART_BEAT
	heartbeat();
#endif
	timer_ack();
	evt->event_handler(evt);
	return IRQ_HANDLED;
}