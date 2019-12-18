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
 int /*<<< orphan*/  GPIO_NR_PALMZ72_POWER_DETECT ; 
 int /*<<< orphan*/  GPIO_NR_PALMZ72_USB_DETECT_N ; 
 int gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int power_supply_init(struct device *dev)
{
	int ret;

	ret = gpio_request(GPIO_NR_PALMZ72_POWER_DETECT, "CABLE_STATE_AC");
	if (ret)
		goto err1;
	ret = gpio_direction_input(GPIO_NR_PALMZ72_POWER_DETECT);
	if (ret)
		goto err2;

	ret = gpio_request(GPIO_NR_PALMZ72_USB_DETECT_N, "CABLE_STATE_USB");
	if (ret)
		goto err2;
	ret = gpio_direction_input(GPIO_NR_PALMZ72_USB_DETECT_N);
	if (ret)
		goto err3;

	return 0;
err3:
	gpio_free(GPIO_NR_PALMZ72_USB_DETECT_N);
err2:
	gpio_free(GPIO_NR_PALMZ72_POWER_DETECT);
err1:
	return ret;
}