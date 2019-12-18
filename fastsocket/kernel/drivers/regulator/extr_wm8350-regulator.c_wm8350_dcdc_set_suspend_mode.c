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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dcdc6_hib_mode; int /*<<< orphan*/  dcdc4_hib_mode; int /*<<< orphan*/  dcdc3_hib_mode; int /*<<< orphan*/  dcdc1_hib_mode; } ;
struct wm8350 {TYPE_1__ pmic; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  REGULATOR_MODE_IDLE 136 
#define  REGULATOR_MODE_NORMAL 135 
#define  REGULATOR_MODE_STANDBY 134 
#define  WM8350_DCDC_1 133 
#define  WM8350_DCDC_2 132 
#define  WM8350_DCDC_3 131 
#define  WM8350_DCDC_4 130 
#define  WM8350_DCDC_5 129 
#define  WM8350_DCDC_6 128 
 int /*<<< orphan*/  WM8350_DCDC_HIB_MODE_IMAGE ; 
 int /*<<< orphan*/  WM8350_DCDC_HIB_MODE_LDO_IM ; 
 int /*<<< orphan*/  WM8350_DCDC_HIB_MODE_STANDBY ; 
 struct wm8350* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int wm8350_dcdc_set_suspend_mode(struct regulator_dev *rdev,
	unsigned int mode)
{
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);
	int dcdc = rdev_get_id(rdev);
	u16 *hib_mode;

	switch (dcdc) {
	case WM8350_DCDC_1:
		hib_mode = &wm8350->pmic.dcdc1_hib_mode;
		break;
	case WM8350_DCDC_3:
		hib_mode = &wm8350->pmic.dcdc3_hib_mode;
		break;
	case WM8350_DCDC_4:
		hib_mode = &wm8350->pmic.dcdc4_hib_mode;
		break;
	case WM8350_DCDC_6:
		hib_mode = &wm8350->pmic.dcdc6_hib_mode;
		break;
	case WM8350_DCDC_2:
	case WM8350_DCDC_5:
	default:
		return -EINVAL;
	}

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		*hib_mode = WM8350_DCDC_HIB_MODE_IMAGE;
		break;
	case REGULATOR_MODE_IDLE:
		*hib_mode = WM8350_DCDC_HIB_MODE_STANDBY;
		break;
	case REGULATOR_MODE_STANDBY:
		*hib_mode = WM8350_DCDC_HIB_MODE_LDO_IM;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}