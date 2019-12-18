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
 int /*<<< orphan*/  VIPER_BCKLIGHT_EN_GPIO ; 
 int /*<<< orphan*/  VIPER_LCD_EN_GPIO ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int viper_backlight_notify(int brightness)
{
	gpio_set_value(VIPER_LCD_EN_GPIO, !!brightness);
	gpio_set_value(VIPER_BCKLIGHT_EN_GPIO, !!brightness);

	return brightness;
}