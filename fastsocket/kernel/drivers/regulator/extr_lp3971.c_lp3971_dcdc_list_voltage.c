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
 int* buck_voltage_map ; 

__attribute__((used)) static int lp3971_dcdc_list_voltage(struct regulator_dev *dev, unsigned index)
{
	return 1000 * buck_voltage_map[index];
}