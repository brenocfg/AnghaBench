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
struct thermostat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  display_stats (struct thermostat*) ; 
 int fan_speed ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  read_sensors (struct thermostat*) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  update_fans_speed (struct thermostat*) ; 

__attribute__((used)) static int monitor_task(void *arg)
{
	struct thermostat* th = arg;

	set_freezable();
	while(!kthread_should_stop()) {
		try_to_freeze();
		msleep_interruptible(2000);

#ifndef DEBUG
		if (fan_speed != -1)
			read_sensors(th);
#else
		read_sensors(th);
#endif		

		if (fan_speed != -1)
			update_fans_speed(th);

#ifdef DEBUG
		display_stats(th);
#endif

	}

	return 0;
}