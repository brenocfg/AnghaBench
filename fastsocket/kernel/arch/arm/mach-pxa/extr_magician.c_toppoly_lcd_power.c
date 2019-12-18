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
 int /*<<< orphan*/  EGPIO_MAGICIAN_TOPPOLY_POWER ; 
 int /*<<< orphan*/  GPIO104_MAGICIAN_LCD_POWER_1 ; 
 int /*<<< orphan*/  GPIO105_MAGICIAN_LCD_POWER_2 ; 
 int /*<<< orphan*/  GPIO106_MAGICIAN_LCD_POWER_3 ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void toppoly_lcd_power(int on, struct fb_var_screeninfo *si)
{
	pr_debug("Toppoly LCD power\n");

	if (on) {
		pr_debug("on\n");
		gpio_set_value(EGPIO_MAGICIAN_TOPPOLY_POWER, 1);
		gpio_set_value(GPIO106_MAGICIAN_LCD_POWER_3, 1);
		udelay(2000);
		gpio_set_value(EGPIO_MAGICIAN_LCD_POWER, 1);
		udelay(2000);
		/* FIXME: enable LCDC here */
		udelay(2000);
		gpio_set_value(GPIO104_MAGICIAN_LCD_POWER_1, 1);
		udelay(2000);
		gpio_set_value(GPIO105_MAGICIAN_LCD_POWER_2, 1);
	} else {
		pr_debug("off\n");
		msleep(15);
		gpio_set_value(GPIO105_MAGICIAN_LCD_POWER_2, 0);
		udelay(500);
		gpio_set_value(GPIO104_MAGICIAN_LCD_POWER_1, 0);
		udelay(1000);
		gpio_set_value(GPIO106_MAGICIAN_LCD_POWER_3, 0);
		gpio_set_value(EGPIO_MAGICIAN_LCD_POWER, 0);
	}
}