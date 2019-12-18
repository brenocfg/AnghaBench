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
struct clock_event_device {scalar_t__ mode; int /*<<< orphan*/  list; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CLOCK_EVT_MODE_UNUSED ; 
 int /*<<< orphan*/  CLOCK_EVT_NOTIFY_ADD ; 
 int /*<<< orphan*/  clockevent_devices ; 
 int /*<<< orphan*/  clockevents_do_notify (int /*<<< orphan*/ ,struct clock_event_device*) ; 
 int /*<<< orphan*/  clockevents_lock ; 
 int /*<<< orphan*/  clockevents_notify_released () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void clockevents_register_device(struct clock_event_device *dev)
{
	unsigned long flags;

	BUG_ON(dev->mode != CLOCK_EVT_MODE_UNUSED);
	BUG_ON(!dev->cpumask);

	spin_lock_irqsave(&clockevents_lock, flags);

	list_add(&dev->list, &clockevent_devices);
	clockevents_do_notify(CLOCK_EVT_NOTIFY_ADD, dev);
	clockevents_notify_released();

	spin_unlock_irqrestore(&clockevents_lock, flags);
}