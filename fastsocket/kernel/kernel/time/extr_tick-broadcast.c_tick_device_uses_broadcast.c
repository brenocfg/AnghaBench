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
struct clock_event_device {int features; int /*<<< orphan*/  event_handler; } ;
struct TYPE_2__ {int /*<<< orphan*/  evtdev; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_C3STOP ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tick_broadcast_clear_oneshot (int) ; 
 TYPE_1__ tick_broadcast_device ; 
 int /*<<< orphan*/  tick_broadcast_lock ; 
 int /*<<< orphan*/  tick_broadcast_start_periodic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_device_is_functional (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_get_broadcast_mask () ; 
 int /*<<< orphan*/  tick_handle_periodic ; 

int tick_device_uses_broadcast(struct clock_event_device *dev, int cpu)
{
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&tick_broadcast_lock, flags);

	/*
	 * Devices might be registered with both periodic and oneshot
	 * mode disabled. This signals, that the device needs to be
	 * operated from the broadcast device and is a placeholder for
	 * the cpu local device.
	 */
	if (!tick_device_is_functional(dev)) {
		dev->event_handler = tick_handle_periodic;
		cpumask_set_cpu(cpu, tick_get_broadcast_mask());
		tick_broadcast_start_periodic(tick_broadcast_device.evtdev);
		ret = 1;
	} else {
		/*
		 * When the new device is not affected by the stop
		 * feature and the cpu is marked in the broadcast mask
		 * then clear the broadcast bit.
		 */
		if (!(dev->features & CLOCK_EVT_FEAT_C3STOP)) {
			int cpu = smp_processor_id();

			cpumask_clear_cpu(cpu, tick_get_broadcast_mask());
			tick_broadcast_clear_oneshot(cpu);
		}
	}
	spin_unlock_irqrestore(&tick_broadcast_lock, flags);
	return ret;
}