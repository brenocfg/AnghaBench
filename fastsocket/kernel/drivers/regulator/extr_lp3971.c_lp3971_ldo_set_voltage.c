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
typedef  size_t u16 ;
struct regulator_dev {int dummy; } ;
struct lp3971 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int LDO_VOL_CONTR_MASK ; 
 int LDO_VOL_CONTR_SHIFT (int) ; 
 size_t LDO_VOL_MAX_IDX ; 
 size_t LDO_VOL_MIN_IDX ; 
 int* LDO_VOL_VALUE_MAP (int) ; 
 int LP3971_LDO1 ; 
 int /*<<< orphan*/  LP3971_LDO_VOL_CONTR_REG (int) ; 
 int lp3971_set_bits (struct lp3971*,int /*<<< orphan*/ ,int,size_t) ; 
 struct lp3971* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp3971_ldo_set_voltage(struct regulator_dev *dev,
				  int min_uV, int max_uV)
{
	struct lp3971 *lp3971 = rdev_get_drvdata(dev);
	int ldo = rdev_get_id(dev) - LP3971_LDO1;
	int min_vol = min_uV / 1000, max_vol = max_uV / 1000;
	const int *vol_map = LDO_VOL_VALUE_MAP(ldo);
	u16 val;

	if (min_vol < vol_map[LDO_VOL_MIN_IDX] ||
	    min_vol > vol_map[LDO_VOL_MAX_IDX])
		return -EINVAL;

	for (val = LDO_VOL_MIN_IDX; val <= LDO_VOL_MAX_IDX; val++)
		if (vol_map[val] >= min_vol)
			break;

	if (vol_map[val] > max_vol)
		return -EINVAL;

	return lp3971_set_bits(lp3971, LP3971_LDO_VOL_CONTR_REG(ldo),
		LDO_VOL_CONTR_MASK << LDO_VOL_CONTR_SHIFT(ldo), val);
}