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
struct da903x_regulator_info {unsigned int min_uV; unsigned int step_uV; int max_uV; } ;

/* Variables and functions */
 int EINVAL ; 
 struct da903x_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int da903x_list_voltage(struct regulator_dev *rdev, unsigned selector)
{
	struct da903x_regulator_info *info = rdev_get_drvdata(rdev);
	int ret;

	ret = info->min_uV + info->step_uV * selector;
	if (ret > info->max_uV)
		return -EINVAL;
	return ret;
}