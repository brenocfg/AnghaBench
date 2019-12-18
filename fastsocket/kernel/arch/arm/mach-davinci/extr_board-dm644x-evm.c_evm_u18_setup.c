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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_attr_user_sw ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int gpio_request (int,char*) ; 
 int sw_gpio ; 

__attribute__((used)) static int
evm_u18_setup(struct i2c_client *client, int gpio, unsigned ngpio, void *c)
{
	int	status;

	/* export dip switch option */
	sw_gpio = gpio + 7;
	status = gpio_request(sw_gpio, "user_sw");
	if (status == 0)
		status = gpio_direction_input(sw_gpio);
	if (status == 0)
		status = device_create_file(&client->dev, &dev_attr_user_sw);
	else
		gpio_free(sw_gpio);
	if (status != 0)
		sw_gpio = -EINVAL;

	/* audio PLL:  48 kHz (vs 44.1 or 32), single rate (vs double) */
	gpio_request(gpio + 3, "pll_fs2");
	gpio_direction_output(gpio + 3, 0);

	gpio_request(gpio + 2, "pll_fs1");
	gpio_direction_output(gpio + 2, 0);

	gpio_request(gpio + 1, "pll_sr");
	gpio_direction_output(gpio + 1, 0);

	return 0;
}