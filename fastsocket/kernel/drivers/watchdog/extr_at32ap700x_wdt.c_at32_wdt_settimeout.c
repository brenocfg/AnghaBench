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
struct TYPE_2__ {int timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 int TIMEOUT_MAX ; 
 int TIMEOUT_MIN ; 
 TYPE_1__* wdt ; 

__attribute__((used)) static int at32_wdt_settimeout(int time)
{
	/*
	 * All counting occurs at 1 / SLOW_CLOCK (32 kHz) and max prescaler is
	 * 2 ^ 16 allowing up to 2 seconds timeout.
	 */
	if ((time < TIMEOUT_MIN) || (time > TIMEOUT_MAX))
		return -EINVAL;

	/*
	 * Set new watchdog time. It will be used when at32_wdt_start() is
	 * called.
	 */
	wdt->timeout = time;
	return 0;
}