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
typedef  int /*<<< orphan*/  u8 ;
struct tps_pmic {TYPE_1__** info; } ;
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {int* table; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TPS6507X_DCDC_1 130 
#define  TPS6507X_DCDC_2 129 
#define  TPS6507X_DCDC_3 128 
 int TPS6507X_DEFDCDCX_DCDC_MASK ; 
 int /*<<< orphan*/  TPS6507X_REG_DEFDCDC1 ; 
 int /*<<< orphan*/  TPS6507X_REG_DEFDCDC2_LOW ; 
 int /*<<< orphan*/  TPS6507X_REG_DEFDCDC3_LOW ; 
 struct tps_pmic* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int tps_6507x_reg_read (struct tps_pmic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps6507x_dcdc_get_voltage(struct regulator_dev *dev)
{
	struct tps_pmic *tps = rdev_get_drvdata(dev);
	int data, dcdc = rdev_get_id(dev);
	u8 reg;

	switch (dcdc) {
	case TPS6507X_DCDC_1:
		reg = TPS6507X_REG_DEFDCDC1;
		break;
	case TPS6507X_DCDC_2:
		reg = TPS6507X_REG_DEFDCDC2_LOW;
		break;
	case TPS6507X_DCDC_3:
		reg = TPS6507X_REG_DEFDCDC3_LOW;
		break;
	default:
		return -EINVAL;
	}

	data = tps_6507x_reg_read(tps, reg);
	if (data < 0)
		return data;

	data &= TPS6507X_DEFDCDCX_DCDC_MASK;
	return tps->info[dcdc]->table[data] * 1000;
}