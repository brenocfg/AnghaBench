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
struct pmu_battery_info {int flags; } ;

/* Variables and functions */
#define  PMU_BATT_TYPE_COMET 130 
#define  PMU_BATT_TYPE_HOOPER 129 
 int PMU_BATT_TYPE_MASK ; 
#define  PMU_BATT_TYPE_SMART 128 
 char** pmu_batt_types ; 

__attribute__((used)) static char *pmu_bat_get_model_name(struct pmu_battery_info *pbi)
{
	switch (pbi->flags & PMU_BATT_TYPE_MASK) {
	case PMU_BATT_TYPE_SMART:
		return pmu_batt_types[0];
	case PMU_BATT_TYPE_COMET:
		return pmu_batt_types[1];
	case PMU_BATT_TYPE_HOOPER:
		return pmu_batt_types[2];
	default: break;
	}
	return pmu_batt_types[3];
}