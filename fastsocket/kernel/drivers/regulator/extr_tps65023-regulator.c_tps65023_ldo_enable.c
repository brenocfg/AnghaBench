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
typedef  int u8 ;
struct tps_pmic {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int TPS65023_LDO_1 ; 
 int TPS65023_LDO_2 ; 
 int /*<<< orphan*/  TPS65023_REG_REG_CTRL ; 
 struct tps_pmic* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int tps_65023_set_bits (struct tps_pmic*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tps65023_ldo_enable(struct regulator_dev *dev)
{
	struct tps_pmic *tps = rdev_get_drvdata(dev);
	int ldo = rdev_get_id(dev);
	u8 shift;

	if (ldo < TPS65023_LDO_1 || ldo > TPS65023_LDO_2)
		return -EINVAL;

	shift = (ldo == TPS65023_LDO_1 ? 1 : 2);
	return tps_65023_set_bits(tps, TPS65023_REG_REG_CTRL, 1 << shift);
}