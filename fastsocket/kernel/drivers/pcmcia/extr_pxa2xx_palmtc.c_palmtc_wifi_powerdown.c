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
 int /*<<< orphan*/  GPIO_NR_PALMTC_PCMCIA_POWER1 ; 
 int /*<<< orphan*/  GPIO_NR_PALMTC_PCMCIA_POWER2 ; 
 int /*<<< orphan*/  GPIO_NR_PALMTC_PCMCIA_RESET ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int palmtc_wifi_powerdown(void)
{
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_RESET, 1);
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER2, 0);
	mdelay(40);
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER1, 0);
	return 0;
}