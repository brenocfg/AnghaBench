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
 unsigned int REGULATOR_MODE_NORMAL ; 

__attribute__((used)) static unsigned int wm8400_dcdc_get_optimum_mode(struct regulator_dev *dev,
						 int input_uV, int output_uV,
						 int load_uA)
{
	return REGULATOR_MODE_NORMAL;
}