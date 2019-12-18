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

/* Variables and functions */
 int EINVAL ; 
 int heartbeat ; 
 int wdt_max_duration ; 

__attribute__((used)) static int orion_wdt_settimeout(int new_time)
{
	if ((new_time <= 0) || (new_time > wdt_max_duration))
		return -EINVAL;

	/* Set new watchdog time to be used when
	 * orion_wdt_enable() or orion_wdt_ping() is called. */
	heartbeat = new_time;
	return 0;
}