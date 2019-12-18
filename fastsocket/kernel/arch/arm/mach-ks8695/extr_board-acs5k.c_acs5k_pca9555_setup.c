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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  gpio_direction_input (unsigned int) ; 
 int /*<<< orphan*/  gpio_direction_output (unsigned int,int) ; 
 int /*<<< orphan*/  gpio_export (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_request (unsigned int,char*) ; 

__attribute__((used)) static int acs5k_pca9555_setup(struct i2c_client *client,
			       unsigned gpio_base, unsigned ngpio,
			       void *context)
{
	static int acs5k_gpio_value[] = {
		-1, -1, -1, -1, -1, -1, -1, 0, 1, 1, -1, 0, 1, 0, -1, -1
	};
	int n;

	for (n = 0; n < ARRAY_SIZE(acs5k_gpio_value); ++n) {
		gpio_request(gpio_base + n, "ACS-5000 GPIO Expander");
		if (acs5k_gpio_value[n] < 0)
			gpio_direction_input(gpio_base + n);
		else
			gpio_direction_output(gpio_base + n,
					      acs5k_gpio_value[n]);
		gpio_export(gpio_base + n, 0); /* Export, direction locked down */
	}

	return 0;
}