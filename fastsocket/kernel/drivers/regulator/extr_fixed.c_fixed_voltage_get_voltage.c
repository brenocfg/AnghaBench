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
 struct fixed_voltage_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int fixed_voltage_get_voltage(struct regulator_dev *dev)
{
	struct fixed_voltage_data *data = rdev_get_drvdata(dev);

	return data->microvolts;
}