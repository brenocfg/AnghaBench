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
struct wm831x_ldo {int base; struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  REGULATOR_MODE_IDLE 129 
#define  REGULATOR_MODE_NORMAL 128 
 int /*<<< orphan*/  WM831X_LDO7_ON_MODE ; 
 int WM831X_LDO_CONTROL ; 
 int WM831X_LDO_ON_CONTROL ; 
 struct wm831x_ldo* rdev_get_drvdata (struct regulator_dev*) ; 
 int wm831x_set_bits (struct wm831x*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_aldo_set_mode(struct regulator_dev *rdev,
				  unsigned int mode)
{
	struct wm831x_ldo *ldo = rdev_get_drvdata(rdev);
	struct wm831x *wm831x = ldo->wm831x;
	int ctrl_reg = ldo->base + WM831X_LDO_CONTROL;
	int on_reg = ldo->base + WM831X_LDO_ON_CONTROL;
	int ret;


	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		ret = wm831x_set_bits(wm831x, on_reg,
				      WM831X_LDO7_ON_MODE, 0);
		if (ret < 0)
			return ret;
		break;

	case REGULATOR_MODE_IDLE:
		ret = wm831x_set_bits(wm831x, ctrl_reg,
				      WM831X_LDO7_ON_MODE,
				      WM831X_LDO7_ON_MODE);
		if (ret < 0)
			return ret;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}