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
typedef  int u8 ;
struct tps_pmic {TYPE_1__** info; } ;
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {int* table; } ;

/* Variables and functions */
 int EINVAL ; 
 int TPS6507X_LDO_1 ; 
 int TPS6507X_LDO_2 ; 
 int TPS6507X_REG_DEFLDO2 ; 
 int TPS6507X_REG_DEFLDO2_LDO2_MASK ; 
 int TPS6507X_REG_LDO_CTRL1 ; 
 int TPS6507X_REG_LDO_CTRL1_LDO1_MASK ; 
 struct tps_pmic* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int tps_6507x_reg_read (struct tps_pmic*,int) ; 

__attribute__((used)) static int tps6507x_ldo_get_voltage(struct regulator_dev *dev)
{
	struct tps_pmic *tps = rdev_get_drvdata(dev);
	int data, ldo = rdev_get_id(dev);
	u8 reg, mask;

	if (ldo < TPS6507X_LDO_1 || ldo > TPS6507X_LDO_2)
		return -EINVAL;
	else {
		reg = (ldo == TPS6507X_LDO_1 ?
			TPS6507X_REG_LDO_CTRL1 : TPS6507X_REG_DEFLDO2);
		mask = (ldo == TPS6507X_LDO_1 ?
			TPS6507X_REG_LDO_CTRL1_LDO1_MASK :
				TPS6507X_REG_DEFLDO2_LDO2_MASK);
	}

	data = tps_6507x_reg_read(tps, reg);
	if (data < 0)
		return data;

	data &= mask;
	return tps->info[ldo]->table[data] * 1000;
}