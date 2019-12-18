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
struct clock_event_device {scalar_t__ mode; int /*<<< orphan*/  next_event; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ CLOCK_EVT_MODE_PERIODIC ; 
 int /*<<< orphan*/  clockevents_program_event (struct clock_event_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  tick_do_periodic_broadcast () ; 
 int /*<<< orphan*/  tick_period ; 

__attribute__((used)) static void tick_handle_periodic_broadcast(struct clock_event_device *dev)
{
	ktime_t next;

	tick_do_periodic_broadcast();

	/*
	 * The device is in periodic mode. No reprogramming necessary:
	 */
	if (dev->mode == CLOCK_EVT_MODE_PERIODIC)
		return;

	/*
	 * Setup the next period for devices, which do not have
	 * periodic mode. We read dev->next_event first and add to it
	 * when the event alrady expired. clockevents_program_event()
	 * sets dev->next_event only when the event is really
	 * programmed to the device.
	 */
	for (next = dev->next_event; ;) {
		next = ktime_add(next, tick_period);

		if (!clockevents_program_event(dev, next, ktime_get()))
			return;
		tick_do_periodic_broadcast();
	}
}