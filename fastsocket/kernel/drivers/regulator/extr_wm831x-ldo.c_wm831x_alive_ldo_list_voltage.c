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
 unsigned int WM831X_ALIVE_LDO_MAX_SELECTOR ; 

__attribute__((used)) static int wm831x_alive_ldo_list_voltage(struct regulator_dev *rdev,
				      unsigned int selector)
{
	/* 0.8-1.55V in 50mV steps */
	if (selector <= WM831X_ALIVE_LDO_MAX_SELECTOR)
		return 800000 + (selector * 50000);
	return -EINVAL;
}