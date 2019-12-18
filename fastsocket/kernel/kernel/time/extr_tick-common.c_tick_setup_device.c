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
struct tick_device {scalar_t__ mode; struct clock_event_device* evtdev; } ;
struct cpumask {int dummy; } ;
struct clock_event_device {void (* event_handler ) (struct clock_event_device*) ;int /*<<< orphan*/  irq; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  next_event; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int HZ ; 
 int NSEC_PER_SEC ; 
 scalar_t__ TICKDEV_MODE_PERIODIC ; 
 int TICK_DO_TIMER_BOOT ; 
 void clockevents_handle_noop (struct clock_event_device*) ; 
 int /*<<< orphan*/  cpumask_equal (int /*<<< orphan*/ ,struct cpumask const*) ; 
 int /*<<< orphan*/  irq_set_affinity (int /*<<< orphan*/ ,struct cpumask const*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int) ; 
 scalar_t__ tick_device_uses_broadcast (struct clock_event_device*,int) ; 
 int tick_do_timer_cpu ; 
 int /*<<< orphan*/  tick_next_period ; 
 int /*<<< orphan*/  tick_period ; 
 int /*<<< orphan*/  tick_setup_oneshot (struct clock_event_device*,void (*) (struct clock_event_device*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_setup_periodic (struct clock_event_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tick_setup_device(struct tick_device *td,
			      struct clock_event_device *newdev, int cpu,
			      const struct cpumask *cpumask)
{
	ktime_t next_event;
	void (*handler)(struct clock_event_device *) = NULL;

	/*
	 * First device setup ?
	 */
	if (!td->evtdev) {
		/*
		 * If no cpu took the do_timer update, assign it to
		 * this cpu:
		 */
		if (tick_do_timer_cpu == TICK_DO_TIMER_BOOT) {
			tick_do_timer_cpu = cpu;
			tick_next_period = ktime_get();
			tick_period = ktime_set(0, NSEC_PER_SEC / HZ);
		}

		/*
		 * Startup in periodic mode first.
		 */
		td->mode = TICKDEV_MODE_PERIODIC;
	} else {
		handler = td->evtdev->event_handler;
		next_event = td->evtdev->next_event;
		td->evtdev->event_handler = clockevents_handle_noop;
	}

	td->evtdev = newdev;

	/*
	 * When the device is not per cpu, pin the interrupt to the
	 * current cpu:
	 */
	if (!cpumask_equal(newdev->cpumask, cpumask))
		irq_set_affinity(newdev->irq, cpumask);

	/*
	 * When global broadcasting is active, check if the current
	 * device is registered as a placeholder for broadcast mode.
	 * This allows us to handle this x86 misfeature in a generic
	 * way.
	 */
	if (tick_device_uses_broadcast(newdev, cpu))
		return;

	if (td->mode == TICKDEV_MODE_PERIODIC)
		tick_setup_periodic(newdev, 0);
	else
		tick_setup_oneshot(newdev, handler, next_event);
}