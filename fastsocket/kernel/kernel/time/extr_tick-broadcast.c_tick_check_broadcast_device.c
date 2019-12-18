#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clock_event_device {scalar_t__ rating; int features; } ;
struct TYPE_2__ {struct clock_event_device* evtdev; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_C3STOP ; 
 int /*<<< orphan*/  clockevents_exchange_device (int /*<<< orphan*/ *,struct clock_event_device*) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 TYPE_1__ tick_broadcast_device ; 
 int /*<<< orphan*/  tick_broadcast_start_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_get_broadcast_mask () ; 

int tick_check_broadcast_device(struct clock_event_device *dev)
{
	if ((tick_broadcast_device.evtdev &&
	     tick_broadcast_device.evtdev->rating >= dev->rating) ||
	     (dev->features & CLOCK_EVT_FEAT_C3STOP))
		return 0;

	clockevents_exchange_device(NULL, dev);
	tick_broadcast_device.evtdev = dev;
	if (!cpumask_empty(tick_get_broadcast_mask()))
		tick_broadcast_start_periodic(dev);
	return 1;
}