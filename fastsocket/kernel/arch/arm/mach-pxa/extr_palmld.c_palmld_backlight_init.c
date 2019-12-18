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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_NR_PALMLD_BL_POWER ; 
 int /*<<< orphan*/  GPIO_NR_PALMLD_LCD_POWER ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int palmld_backlight_init(struct device *dev)
{
	int ret;

	ret = gpio_request(GPIO_NR_PALMLD_BL_POWER, "BL POWER");
	if (ret)
		goto err;
	ret = gpio_direction_output(GPIO_NR_PALMLD_BL_POWER, 0);
	if (ret)
		goto err2;
	ret = gpio_request(GPIO_NR_PALMLD_LCD_POWER, "LCD POWER");
	if (ret)
		goto err2;
	ret = gpio_direction_output(GPIO_NR_PALMLD_LCD_POWER, 0);
	if (ret)
		goto err3;

	return 0;
err3:
	gpio_free(GPIO_NR_PALMLD_LCD_POWER);
err2:
	gpio_free(GPIO_NR_PALMLD_BL_POWER);
err:
	return ret;
}