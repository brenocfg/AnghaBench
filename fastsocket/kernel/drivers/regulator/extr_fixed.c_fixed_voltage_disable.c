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
struct regulator_dev {int dummy; } ;
struct fixed_voltage_data {scalar_t__ is_enabled; int /*<<< orphan*/  enable_high; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct fixed_voltage_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int fixed_voltage_disable(struct regulator_dev *dev)
{
	struct fixed_voltage_data *data = rdev_get_drvdata(dev);

	if (gpio_is_valid(data->gpio)) {
		gpio_set_value_cansleep(data->gpio, !data->enable_high);
		data->is_enabled = 0;
	}

	return 0;
}