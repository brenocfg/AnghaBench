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
#define  REGULATOR_MODE_FAST 131 
#define  REGULATOR_MODE_IDLE 130 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 int WM8350_DCDC_1 ; 
 int WM8350_DCDC_2 ; 
 int WM8350_DCDC_5 ; 
 int WM8350_DCDC_6 ; 
 int /*<<< orphan*/  WM8350_DCDC_ACTIVE_OPTIONS ; 
 int /*<<< orphan*/  WM8350_DCDC_SLEEP_OPTIONS ; 
 int /*<<< orphan*/  force_continuous_enable (struct wm8350*,int,int) ; 
 struct wm8350* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int /*<<< orphan*/  wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8350_dcdc_set_mode(struct regulator_dev *rdev, unsigned int mode)
{
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);
	int dcdc = rdev_get_id(rdev);
	u16 val;

	if (dcdc < WM8350_DCDC_1 || dcdc > WM8350_DCDC_6)
		return -EINVAL;

	if (dcdc == WM8350_DCDC_2 || dcdc == WM8350_DCDC_5)
		return -EINVAL;

	val = 1 << (dcdc - WM8350_DCDC_1);

	switch (mode) {
	case REGULATOR_MODE_FAST:
		/* force continuous mode */
		wm8350_set_bits(wm8350, WM8350_DCDC_ACTIVE_OPTIONS, val);
		wm8350_clear_bits(wm8350, WM8350_DCDC_SLEEP_OPTIONS, val);
		force_continuous_enable(wm8350, dcdc, 1);
		break;
	case REGULATOR_MODE_NORMAL:
		/* active / pulse skipping */
		wm8350_set_bits(wm8350, WM8350_DCDC_ACTIVE_OPTIONS, val);
		wm8350_clear_bits(wm8350, WM8350_DCDC_SLEEP_OPTIONS, val);
		force_continuous_enable(wm8350, dcdc, 0);
		break;
	case REGULATOR_MODE_IDLE:
		/* standby mode */
		force_continuous_enable(wm8350, dcdc, 0);
		wm8350_clear_bits(wm8350, WM8350_DCDC_SLEEP_OPTIONS, val);
		wm8350_clear_bits(wm8350, WM8350_DCDC_ACTIVE_OPTIONS, val);
		break;
	case REGULATOR_MODE_STANDBY:
		/* LDO mode */
		force_continuous_enable(wm8350, dcdc, 0);
		wm8350_set_bits(wm8350, WM8350_DCDC_SLEEP_OPTIONS, val);
		break;
	}

	return 0;
}