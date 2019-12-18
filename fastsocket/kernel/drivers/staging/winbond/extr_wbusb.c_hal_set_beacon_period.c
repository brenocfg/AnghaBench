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
typedef  int u32 ;
typedef  int u16 ;
struct hw_data {int BeaconPeriod; int ProbeDelay; scalar_t__ SurpriseRemove; } ;

/* Variables and functions */
 int /*<<< orphan*/  Wb35Reg_Write (struct hw_data*,int,int) ; 

__attribute__((used)) static void hal_set_beacon_period(struct hw_data *pHwData, u16 beacon_period)
{
	u32 tmp;

	if (pHwData->SurpriseRemove)
		return;

	pHwData->BeaconPeriod = beacon_period;
	tmp = pHwData->BeaconPeriod << 16;
	tmp |= pHwData->ProbeDelay;
	Wb35Reg_Write(pHwData, 0x0848, tmp);
}