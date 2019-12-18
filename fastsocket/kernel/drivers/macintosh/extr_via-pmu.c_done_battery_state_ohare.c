#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct adb_request {int* reply; } ;
struct TYPE_2__ {unsigned int flags; long charge; long max_charge; long amperage; long voltage; long time_remaining; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_GET_MB_INFO ; 
 int /*<<< orphan*/  PMAC_MB_INFO_MODEL ; 
 int PMAC_TYPE_COMET ; 
 unsigned int PMU_BATT_CHARGING ; 
 unsigned int PMU_BATT_PRESENT ; 
 unsigned int PMU_BATT_TYPE_HOOPER ; 
 int /*<<< orphan*/  PMU_PWR_AC_PRESENT ; 
 int /*<<< orphan*/  async_req_locks ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pmu_batteries ; 
 size_t pmu_cur_battery ; 
 int /*<<< orphan*/  pmu_power_flags ; 

__attribute__((used)) static void
done_battery_state_ohare(struct adb_request* req)
{
	/* format:
	 *  [0]    :  flags
	 *    0x01 :  AC indicator
	 *    0x02 :  charging
	 *    0x04 :  battery exist
	 *    0x08 :  
	 *    0x10 :  
	 *    0x20 :  full charged
	 *    0x40 :  pcharge reset
	 *    0x80 :  battery exist
	 *
	 *  [1][2] :  battery voltage
	 *  [3]    :  CPU temperature
	 *  [4]    :  battery temperature
	 *  [5]    :  current
	 *  [6][7] :  pcharge
	 *              --tkoba
	 */
	unsigned int bat_flags = PMU_BATT_TYPE_HOOPER;
	long pcharge, charge, vb, vmax, lmax;
	long vmax_charging, vmax_charged;
	long amperage, voltage, time, max;
	int mb = pmac_call_feature(PMAC_FTR_GET_MB_INFO,
			NULL, PMAC_MB_INFO_MODEL, 0);

	if (req->reply[0] & 0x01)
		pmu_power_flags |= PMU_PWR_AC_PRESENT;
	else
		pmu_power_flags &= ~PMU_PWR_AC_PRESENT;
	
	if (mb == PMAC_TYPE_COMET) {
		vmax_charged = 189;
		vmax_charging = 213;
		lmax = 6500;
	} else {
		vmax_charged = 330;
		vmax_charging = 330;
		lmax = 6500;
	}
	vmax = vmax_charged;

	/* If battery installed */
	if (req->reply[0] & 0x04) {
		bat_flags |= PMU_BATT_PRESENT;
		if (req->reply[0] & 0x02)
			bat_flags |= PMU_BATT_CHARGING;
		vb = (req->reply[1] << 8) | req->reply[2];
		voltage = (vb * 265 + 72665) / 10;
		amperage = req->reply[5];
		if ((req->reply[0] & 0x01) == 0) {
			if (amperage > 200)
				vb += ((amperage - 200) * 15)/100;
		} else if (req->reply[0] & 0x02) {
			vb = (vb * 97) / 100;
			vmax = vmax_charging;
		}
		charge = (100 * vb) / vmax;
		if (req->reply[0] & 0x40) {
			pcharge = (req->reply[6] << 8) + req->reply[7];
			if (pcharge > lmax)
				pcharge = lmax;
			pcharge *= 100;
			pcharge = 100 - pcharge / lmax;
			if (pcharge < charge)
				charge = pcharge;
		}
		if (amperage > 0)
			time = (charge * 16440) / amperage;
		else
			time = 0;
		max = 100;
		amperage = -amperage;
	} else
		charge = max = amperage = voltage = time = 0;

	pmu_batteries[pmu_cur_battery].flags = bat_flags;
	pmu_batteries[pmu_cur_battery].charge = charge;
	pmu_batteries[pmu_cur_battery].max_charge = max;
	pmu_batteries[pmu_cur_battery].amperage = amperage;
	pmu_batteries[pmu_cur_battery].voltage = voltage;
	pmu_batteries[pmu_cur_battery].time_remaining = time;

	clear_bit(0, &async_req_locks);
}