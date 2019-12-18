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
typedef  int u16 ;
struct wm8350 {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WM8350_DC1_VSEL_MASK ; 
 int WM8350_DCDC1_CONTROL ; 
 int WM8350_DCDC3_CONTROL ; 
 int WM8350_DCDC4_CONTROL ; 
 int WM8350_DCDC6_CONTROL ; 
#define  WM8350_DCDC_1 133 
#define  WM8350_DCDC_2 132 
#define  WM8350_DCDC_3 131 
#define  WM8350_DCDC_4 130 
#define  WM8350_DCDC_5 129 
#define  WM8350_DCDC_6 128 
 struct wm8350* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int wm8350_dcdc_val_to_mvolts (int) ; 
 int wm8350_reg_read (struct wm8350*,int) ; 

__attribute__((used)) static int wm8350_dcdc_get_voltage(struct regulator_dev *rdev)
{
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);
	int volt_reg, dcdc = rdev_get_id(rdev);
	u16 val;

	switch (dcdc) {
	case WM8350_DCDC_1:
		volt_reg = WM8350_DCDC1_CONTROL;
		break;
	case WM8350_DCDC_3:
		volt_reg = WM8350_DCDC3_CONTROL;
		break;
	case WM8350_DCDC_4:
		volt_reg = WM8350_DCDC4_CONTROL;
		break;
	case WM8350_DCDC_6:
		volt_reg = WM8350_DCDC6_CONTROL;
		break;
	case WM8350_DCDC_2:
	case WM8350_DCDC_5:
	default:
		return -EINVAL;
	}

	/* all DCDCs have same mV bits */
	val = wm8350_reg_read(wm8350, volt_reg) & WM8350_DC1_VSEL_MASK;
	return wm8350_dcdc_val_to_mvolts(val) * 1000;
}