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
typedef  scalar_t__ u16 ;
struct wm831x_dcdc {scalar_t__ base; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ WM831X_DCDC_SLEEP_CONTROL ; 
 struct wm831x_dcdc* rdev_get_drvdata (struct regulator_dev*) ; 
 int wm831x_buckp_set_voltage_int (struct regulator_dev*,scalar_t__,int,int) ; 

__attribute__((used)) static int wm831x_buckp_set_suspend_voltage(struct regulator_dev *rdev,
					    int uV)
{
	struct wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	u16 reg = dcdc->base + WM831X_DCDC_SLEEP_CONTROL;

	return wm831x_buckp_set_voltage_int(rdev, reg, uV, uV);
}