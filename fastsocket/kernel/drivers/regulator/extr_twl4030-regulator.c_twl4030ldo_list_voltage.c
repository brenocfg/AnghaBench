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
struct twlreg_info {int* table; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_UNSUP (int) ; 
 int LDO_MV (int) ; 
 struct twlreg_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int twl4030ldo_list_voltage(struct regulator_dev *rdev, unsigned index)
{
	struct twlreg_info	*info = rdev_get_drvdata(rdev);
	int			mV = info->table[index];

	return IS_UNSUP(mV) ? 0 : (LDO_MV(mV) * 1000);
}