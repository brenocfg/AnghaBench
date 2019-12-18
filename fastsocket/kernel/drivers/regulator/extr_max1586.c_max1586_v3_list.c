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
struct max1586_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MAX1586_V3_MAX_VSEL ; 
 int max1586_v3_calc_voltage (struct max1586_data*,unsigned int) ; 
 struct max1586_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int max1586_v3_list(struct regulator_dev *rdev, unsigned selector)
{
	struct max1586_data *max1586 = rdev_get_drvdata(rdev);

	if (selector > MAX1586_V3_MAX_VSEL)
		return -EINVAL;
	return max1586_v3_calc_voltage(max1586, selector);
}