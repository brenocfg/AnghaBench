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
 int HZ ; 
 scalar_t__ WDT_INTERVAL ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ next_heartbeat ; 
 int timeout ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  wdt_enable () ; 

__attribute__((used)) static void wdt_startup(void)
{
	next_heartbeat = jiffies + (timeout * HZ);

	wdt_enable();
	mod_timer(&timer, jiffies + WDT_INTERVAL);
}