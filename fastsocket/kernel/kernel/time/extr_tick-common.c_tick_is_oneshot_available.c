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
struct clock_event_device {int features; } ;
struct TYPE_2__ {struct clock_event_device* evtdev; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_ONESHOT ; 
 TYPE_1__ __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_cpu_device ; 

int tick_is_oneshot_available(void)
{
	struct clock_event_device *dev = __get_cpu_var(tick_cpu_device).evtdev;

	return dev && (dev->features & CLOCK_EVT_FEAT_ONESHOT);
}