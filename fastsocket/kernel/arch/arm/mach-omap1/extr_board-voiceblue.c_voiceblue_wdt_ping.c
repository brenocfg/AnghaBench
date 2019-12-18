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
 int /*<<< orphan*/  MACHINE_REBOOT ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  machine_state ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wdt_gpio_state ; 

void voiceblue_wdt_ping(void)
{
	if (test_bit(MACHINE_REBOOT, &machine_state))
		return;

	wdt_gpio_state = !wdt_gpio_state;
	gpio_set_value(0, wdt_gpio_state);
}