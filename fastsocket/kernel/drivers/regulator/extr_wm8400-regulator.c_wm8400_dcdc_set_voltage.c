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
struct wm8400 {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WM8400_DC1_VSEL_MASK ; 
 int WM8400_DCDC1 ; 
 scalar_t__ WM8400_DCDC1_CONTROL_1 ; 
 struct wm8400* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int wm8400_set_bits (struct wm8400*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8400_dcdc_set_voltage(struct regulator_dev *dev,
				  int min_uV, int max_uV)
{
	struct wm8400 *wm8400 = rdev_get_drvdata(dev);
	u16 val;
	int offset = (rdev_get_id(dev) - WM8400_DCDC1) * 2;

	if (min_uV < 850000)
		return -EINVAL;

	val = (min_uV - 825001) / 25000;

	if (850000 + (25000 * val) > max_uV)
		return -EINVAL;
	BUG_ON(850000 + (25000 * val) < min_uV);

	return wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_1 + offset,
			       WM8400_DC1_VSEL_MASK, val);
}