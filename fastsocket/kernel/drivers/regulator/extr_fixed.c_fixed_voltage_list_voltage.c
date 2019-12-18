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
struct fixed_voltage_data {int microvolts; } ;

/* Variables and functions */
 int EINVAL ; 
 struct fixed_voltage_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int fixed_voltage_list_voltage(struct regulator_dev *dev,
				      unsigned selector)
{
	struct fixed_voltage_data *data = rdev_get_drvdata(dev);

	if (selector != 0)
		return -EINVAL;

	return data->microvolts;
}