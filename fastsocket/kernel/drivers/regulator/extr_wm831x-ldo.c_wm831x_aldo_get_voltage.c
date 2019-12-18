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
 int WM831X_LDO7_ON_VSEL_MASK ; 
 int WM831X_LDO_ON_CONTROL ; 
 struct wm831x_ldo* rdev_get_drvdata (struct regulator_dev*) ; 
 int wm831x_aldo_list_voltage (struct regulator_dev*,int) ; 
 int wm831x_reg_read (struct wm831x*,int) ; 

__attribute__((used)) static int wm831x_aldo_get_voltage(struct regulator_dev *rdev)
{
	struct wm831x_ldo *ldo = rdev_get_drvdata(rdev);
	struct wm831x *wm831x = ldo->wm831x;
	int reg = ldo->base + WM831X_LDO_ON_CONTROL;
	int ret;

	ret = wm831x_reg_read(wm831x, reg);
	if (ret < 0)
		return ret;

	ret &= WM831X_LDO7_ON_VSEL_MASK;

	return wm831x_aldo_list_voltage(rdev, ret);
}