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
struct fb_var_screeninfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGPIO_MAGICIAN_LCD_POWER ; 
 int /*<<< orphan*/  GPIO104_MAGICIAN_LCD_POWER_1 ; 
 int /*<<< orphan*/  GPIO105_MAGICIAN_LCD_POWER_2 ; 
 int /*<<< orphan*/  GPIO106_MAGICIAN_LCD_POWER_3 ; 
 int /*<<< orphan*/  GPIO75_MAGICIAN_SAMSUNG_POWER ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int system_rev ; 

__attribute__((used)) static void samsung_lcd_power(int on, struct fb_var_screeninfo *si)
{
	pr_debug("Samsung LCD power\n");

	if (on) {
		pr_debug("on\n");
		if (system_rev < 3)
			gpio_set_value(GPIO75_MAGICIAN_SAMSUNG_POWER, 1);
		else
			gpio_set_value(EGPIO_MAGICIAN_LCD_POWER, 1);
		mdelay(10);
		gpio_set_value(GPIO106_MAGICIAN_LCD_POWER_3, 1);
		mdelay(10);
		gpio_set_value(GPIO104_MAGICIAN_LCD_POWER_1, 1);
		mdelay(30);
		gpio_set_value(GPIO105_MAGICIAN_LCD_POWER_2, 1);
		mdelay(10);
	} else {
		pr_debug("off\n");
		mdelay(10);
		gpio_set_value(GPIO105_MAGICIAN_LCD_POWER_2, 0);
		mdelay(30);
		gpio_set_value(GPIO104_MAGICIAN_LCD_POWER_1, 0);
		mdelay(10);
		gpio_set_value(GPIO106_MAGICIAN_LCD_POWER_3, 0);
		mdelay(10);
		if (system_rev < 3)
			gpio_set_value(GPIO75_MAGICIAN_SAMSUNG_POWER, 0);
		else
			gpio_set_value(EGPIO_MAGICIAN_LCD_POWER, 0);
	}
}