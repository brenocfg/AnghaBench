#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sht15_data {scalar_t__ supply_uV; int val_temp; } ;
struct TYPE_3__ {int d1; scalar_t__ vdd; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* temppoints ; 

__attribute__((used)) static inline int sht15_calc_temp(struct sht15_data *data)
{
	int d1 = temppoints[0].d1;
	int i;

	for (i = ARRAY_SIZE(temppoints) - 1; i > 0; i--)
		/* Find pointer to interpolate */
		if (data->supply_uV > temppoints[i - 1].vdd) {
			d1 = (data->supply_uV - temppoints[i - 1].vdd)
				* (temppoints[i].d1 - temppoints[i - 1].d1)
				/ (temppoints[i].vdd - temppoints[i - 1].vdd)
				+ temppoints[i - 1].d1;
			break;
		}

	return data->val_temp*10 + d1;
}