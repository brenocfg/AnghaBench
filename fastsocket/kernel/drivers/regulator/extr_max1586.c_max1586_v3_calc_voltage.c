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
struct max1586_data {unsigned int max_uV; unsigned int min_uV; } ;

/* Variables and functions */
 unsigned int MAX1586_V3_MAX_VSEL ; 

__attribute__((used)) static int max1586_v3_calc_voltage(struct max1586_data *max1586,
	unsigned selector)
{
	unsigned range_uV = max1586->max_uV - max1586->min_uV;

	return max1586->min_uV + (selector * range_uV / MAX1586_V3_MAX_VSEL);
}