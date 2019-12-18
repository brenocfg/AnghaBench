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
 int /*<<< orphan*/  WM8350_LDO1_HIB_MODE_DIS ; 
 int WM8350_LDO1_HIB_MODE_MASK ; 
 int WM8350_LDO1_LOW_POWER ; 
 int WM8350_LDO2_LOW_POWER ; 
 int WM8350_LDO3_LOW_POWER ; 
 int WM8350_LDO4_LOW_POWER ; 
#define  WM8350_LDO_1 131 
#define  WM8350_LDO_2 130 
#define  WM8350_LDO_3 129 
#define  WM8350_LDO_4 128 
 struct wm8350* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int wm8350_reg_read (struct wm8350*,int) ; 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_ldo_set_suspend_disable(struct regulator_dev *rdev)
{
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);
	int volt_reg, ldo = rdev_get_id(rdev);
	u16 val;

	switch (ldo) {
	case WM8350_LDO_1:
		volt_reg = WM8350_LDO1_LOW_POWER;
		break;
	case WM8350_LDO_2:
		volt_reg = WM8350_LDO2_LOW_POWER;
		break;
	case WM8350_LDO_3:
		volt_reg = WM8350_LDO3_LOW_POWER;
		break;
	case WM8350_LDO_4:
		volt_reg = WM8350_LDO4_LOW_POWER;
		break;
	default:
		return -EINVAL;
	}

	/* all LDOs have same mV bits */
	val = wm8350_reg_read(wm8350, volt_reg) & ~WM8350_LDO1_HIB_MODE_MASK;
	wm8350_reg_write(wm8350, volt_reg, WM8350_LDO1_HIB_MODE_DIS);
	return 0;
}