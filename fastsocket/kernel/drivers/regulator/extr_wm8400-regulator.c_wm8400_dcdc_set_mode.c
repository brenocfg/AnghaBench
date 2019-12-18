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
struct wm8400 {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  REGULATOR_MODE_FAST 130 
#define  REGULATOR_MODE_IDLE 129 
#define  REGULATOR_MODE_NORMAL 128 
 int WM8400_DC1_ACTIVE ; 
 int WM8400_DC1_FRC_PWM ; 
 int WM8400_DC1_SLEEP ; 
 int WM8400_DCDC1 ; 
 int /*<<< orphan*/  WM8400_DCDC1_CONTROL_1 ; 
 int /*<<< orphan*/  WM8400_DCDC1_CONTROL_2 ; 
 struct wm8400* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int wm8400_set_bits (struct wm8400*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8400_dcdc_set_mode(struct regulator_dev *dev, unsigned int mode)
{
	struct wm8400 *wm8400 = rdev_get_drvdata(dev);
	int offset = (rdev_get_id(dev) - WM8400_DCDC1) * 2;
	int ret;

	switch (mode) {
	case REGULATOR_MODE_FAST:
		/* Datasheet: active with force PWM */
		ret = wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_2 + offset,
				      WM8400_DC1_FRC_PWM, WM8400_DC1_FRC_PWM);
		if (ret != 0)
			return ret;

		return wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_1 + offset,
				       WM8400_DC1_ACTIVE | WM8400_DC1_SLEEP,
				       WM8400_DC1_ACTIVE);

	case REGULATOR_MODE_NORMAL:
		/* Datasheet: active */
		ret = wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_2 + offset,
				      WM8400_DC1_FRC_PWM, 0);
		if (ret != 0)
			return ret;

		return wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_1 + offset,
				       WM8400_DC1_ACTIVE | WM8400_DC1_SLEEP,
				       WM8400_DC1_ACTIVE);

	case REGULATOR_MODE_IDLE:
		/* Datasheet: standby */
		ret = wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_1 + offset,
				      WM8400_DC1_ACTIVE, 0);
		if (ret != 0)
			return ret;
		return wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_1 + offset,
				       WM8400_DC1_SLEEP, 0);

	default:
		return -EINVAL;
	}
}