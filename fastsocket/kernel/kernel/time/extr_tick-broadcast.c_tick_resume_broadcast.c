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
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {int mode; struct clock_event_device* evtdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_MODE_RESUME ; 
#define  TICKDEV_MODE_ONESHOT 129 
#define  TICKDEV_MODE_PERIODIC 128 
 int /*<<< orphan*/  clockevents_set_mode (struct clock_event_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 int cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__ tick_broadcast_device ; 
 int /*<<< orphan*/  tick_broadcast_lock ; 
 int /*<<< orphan*/  tick_broadcast_start_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_get_broadcast_mask () ; 
 int tick_resume_broadcast_oneshot (struct clock_event_device*) ; 

int tick_resume_broadcast(void)
{
	struct clock_event_device *bc;
	unsigned long flags;
	int broadcast = 0;

	spin_lock_irqsave(&tick_broadcast_lock, flags);

	bc = tick_broadcast_device.evtdev;

	if (bc) {
		clockevents_set_mode(bc, CLOCK_EVT_MODE_RESUME);

		switch (tick_broadcast_device.mode) {
		case TICKDEV_MODE_PERIODIC:
			if (!cpumask_empty(tick_get_broadcast_mask()))
				tick_broadcast_start_periodic(bc);
			broadcast = cpumask_test_cpu(smp_processor_id(),
						     tick_get_broadcast_mask());
			break;
		case TICKDEV_MODE_ONESHOT:
			broadcast = tick_resume_broadcast_oneshot(bc);
			break;
		}
	}
	spin_unlock_irqrestore(&tick_broadcast_lock, flags);

	return broadcast;
}