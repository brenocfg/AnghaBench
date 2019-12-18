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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  CLOCK_EVT_NOTIFY_ADD 137 
#define  CLOCK_EVT_NOTIFY_BROADCAST_ENTER 136 
#define  CLOCK_EVT_NOTIFY_BROADCAST_EXIT 135 
#define  CLOCK_EVT_NOTIFY_BROADCAST_FORCE 134 
#define  CLOCK_EVT_NOTIFY_BROADCAST_OFF 133 
#define  CLOCK_EVT_NOTIFY_BROADCAST_ON 132 
#define  CLOCK_EVT_NOTIFY_CPU_DEAD 131 
#define  CLOCK_EVT_NOTIFY_CPU_DYING 130 
#define  CLOCK_EVT_NOTIFY_RESUME 129 
#define  CLOCK_EVT_NOTIFY_SUSPEND 128 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  tick_broadcast_on_off (unsigned long,void*) ; 
 int /*<<< orphan*/  tick_broadcast_oneshot_control (unsigned long) ; 
 int tick_check_new_device (void*) ; 
 int /*<<< orphan*/  tick_handover_do_timer (void*) ; 
 int /*<<< orphan*/  tick_resume () ; 
 int /*<<< orphan*/  tick_shutdown (void*) ; 
 int /*<<< orphan*/  tick_shutdown_broadcast (void*) ; 
 int /*<<< orphan*/  tick_shutdown_broadcast_oneshot (void*) ; 
 int /*<<< orphan*/  tick_suspend () ; 
 int /*<<< orphan*/  tick_suspend_broadcast () ; 

__attribute__((used)) static int tick_notify(struct notifier_block *nb, unsigned long reason,
			       void *dev)
{
	switch (reason) {

	case CLOCK_EVT_NOTIFY_ADD:
		return tick_check_new_device(dev);

	case CLOCK_EVT_NOTIFY_BROADCAST_ON:
	case CLOCK_EVT_NOTIFY_BROADCAST_OFF:
	case CLOCK_EVT_NOTIFY_BROADCAST_FORCE:
		tick_broadcast_on_off(reason, dev);
		break;

	case CLOCK_EVT_NOTIFY_BROADCAST_ENTER:
	case CLOCK_EVT_NOTIFY_BROADCAST_EXIT:
		tick_broadcast_oneshot_control(reason);
		break;

	case CLOCK_EVT_NOTIFY_CPU_DYING:
		tick_handover_do_timer(dev);
		break;

	case CLOCK_EVT_NOTIFY_CPU_DEAD:
		tick_shutdown_broadcast_oneshot(dev);
		tick_shutdown_broadcast(dev);
		tick_shutdown(dev);
		break;

	case CLOCK_EVT_NOTIFY_SUSPEND:
		tick_suspend();
		tick_suspend_broadcast();
		break;

	case CLOCK_EVT_NOTIFY_RESUME:
		tick_resume();
		break;

	default:
		break;
	}

	return NOTIFY_OK;
}