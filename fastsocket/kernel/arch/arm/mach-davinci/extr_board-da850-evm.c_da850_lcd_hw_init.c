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
 int /*<<< orphan*/  DA850_LCD_BL_PIN ; 
 int /*<<< orphan*/  DA850_LCD_PWR_PIN ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int da850_lcd_hw_init(void)
{
	int status;

	status = gpio_request(DA850_LCD_BL_PIN, "lcd bl\n");
	if (status < 0)
		return status;

	status = gpio_request(DA850_LCD_PWR_PIN, "lcd pwr\n");
	if (status < 0) {
		gpio_free(DA850_LCD_BL_PIN);
		return status;
	}

	gpio_direction_output(DA850_LCD_BL_PIN, 0);
	gpio_direction_output(DA850_LCD_PWR_PIN, 0);

	/* disable lcd backlight */
	gpio_set_value(DA850_LCD_BL_PIN, 0);

	/* disable lcd power */
	gpio_set_value(DA850_LCD_PWR_PIN, 0);

	/* enable lcd power */
	gpio_set_value(DA850_LCD_PWR_PIN, 1);

	/* enable lcd backlight */
	gpio_set_value(DA850_LCD_BL_PIN, 1);

	return 0;
}