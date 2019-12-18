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
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int WM8350_DCDC_MAX_VSEL ; 
 int wm8350_dcdc_val_to_mvolts (unsigned int) ; 

__attribute__((used)) static int wm8350_dcdc_list_voltage(struct regulator_dev *rdev,
				    unsigned selector)
{
	if (selector > WM8350_DCDC_MAX_VSEL)
		return -EINVAL;
	return wm8350_dcdc_val_to_mvolts(selector) * 1000;
}