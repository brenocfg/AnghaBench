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
 int /*<<< orphan*/  TOSA_GPIO_AC_IN ; 
 int gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tosa_power_init(struct device *dev)
{
	int ret = gpio_request(TOSA_GPIO_AC_IN, "ac in");
	if (ret)
		goto err_gpio_req;

	ret = gpio_direction_input(TOSA_GPIO_AC_IN);
	if (ret)
		goto err_gpio_in;

	return 0;

err_gpio_in:
	gpio_free(TOSA_GPIO_AC_IN);
err_gpio_req:
	return ret;
}