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
 unsigned int WM8400_DC1_VSEL_MASK ; 

__attribute__((used)) static int wm8400_dcdc_list_voltage(struct regulator_dev *dev,
				    unsigned selector)
{
	if (selector > WM8400_DC1_VSEL_MASK)
		return -EINVAL;

	return 850000 + (selector * 25000);
}