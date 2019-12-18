#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tps_pmic {TYPE_1__** info; } ;
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {int table_len; int* table; } ;

/* Variables and functions */
 int EINVAL ; 
 int TPS65023_LDO_1 ; 
 int TPS65023_LDO_2 ; 
 int TPS65023_LDO_CTRL_LDOx_SHIFT (int) ; 
 int /*<<< orphan*/  TPS65023_REG_LDO_CTRL ; 
 struct tps_pmic* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int tps_65023_reg_read (struct tps_pmic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65023_ldo_get_voltage(struct regulator_dev *dev)
{
	struct tps_pmic *tps = rdev_get_drvdata(dev);
	int data, ldo = rdev_get_id(dev);

	if (ldo < TPS65023_LDO_1 || ldo > TPS65023_LDO_2)
		return -EINVAL;

	data = tps_65023_reg_read(tps, TPS65023_REG_LDO_CTRL);
	if (data < 0)
		return data;

	data >>= (TPS65023_LDO_CTRL_LDOx_SHIFT(ldo - TPS65023_LDO_1));
	data &= (tps->info[ldo]->table_len - 1);
	return tps->info[ldo]->table[data] * 1000;
}