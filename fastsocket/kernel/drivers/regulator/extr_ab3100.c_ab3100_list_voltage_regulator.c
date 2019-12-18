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
struct regulator_dev {struct ab3100_regulator* reg_data; } ;
struct ab3100_regulator {unsigned int voltages_len; int* typ_voltages; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ab3100_list_voltage_regulator(struct regulator_dev *reg,
					 unsigned selector)
{
	struct ab3100_regulator *abreg = reg->reg_data;

	if (selector > abreg->voltages_len)
		return -EINVAL;
	return abreg->typ_voltages[selector];
}