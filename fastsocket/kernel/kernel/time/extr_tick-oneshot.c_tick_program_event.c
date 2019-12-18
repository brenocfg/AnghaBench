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
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {struct clock_event_device* evtdev; } ;

/* Variables and functions */
 TYPE_1__ __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_cpu_device ; 
 int tick_dev_program_event (struct clock_event_device*,int /*<<< orphan*/ ,int) ; 

int tick_program_event(ktime_t expires, int force)
{
	struct clock_event_device *dev = __get_cpu_var(tick_cpu_device).evtdev;

	return tick_dev_program_event(dev, expires, force);
}