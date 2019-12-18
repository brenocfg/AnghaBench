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
struct clock_event_device {int /*<<< orphan*/  name; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CLOCK_EVT_MODE_ONESHOT 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 int /*<<< orphan*/  COMPARE ; 
 int /*<<< orphan*/  cpu_disable_idle_sleep () ; 
 int /*<<< orphan*/  cpu_enable_idle_sleep () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysreg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void comparator_mode(enum clock_event_mode mode,
		struct clock_event_device *evdev)
{
	switch (mode) {
	case CLOCK_EVT_MODE_ONESHOT:
		pr_debug("%s: start\n", evdev->name);
		/* FALLTHROUGH */
	case CLOCK_EVT_MODE_RESUME:
		cpu_disable_idle_sleep();
		break;
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
		sysreg_write(COMPARE, 0);
		pr_debug("%s: stop\n", evdev->name);
		cpu_enable_idle_sleep();
		break;
	default:
		BUG();
	}
}