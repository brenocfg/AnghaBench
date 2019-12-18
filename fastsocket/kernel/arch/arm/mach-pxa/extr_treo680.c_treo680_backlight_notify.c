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
 int /*<<< orphan*/  GPIO_NR_TREO680_BL_POWER ; 
 int TREO680_MAX_INTENSITY ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int treo680_backlight_notify(int brightness)
{
	gpio_set_value(GPIO_NR_TREO680_BL_POWER, brightness);
	return TREO680_MAX_INTENSITY - brightness;
}