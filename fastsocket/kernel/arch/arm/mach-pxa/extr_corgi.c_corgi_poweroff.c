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
 int /*<<< orphan*/  CORGI_GPIO_LED_GREEN ; 
 int /*<<< orphan*/  arm_machine_restart (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_is_corgi () ; 

__attribute__((used)) static void corgi_poweroff(void)
{
	if (!machine_is_corgi())
		/* Green LED off tells the bootloader to halt */
		gpio_set_value(CORGI_GPIO_LED_GREEN, 0);

	arm_machine_restart('h', NULL);
}