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
typedef  void* u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct HvCallPci_DsaAddr {void* deviceId; void* subBusNumber; int /*<<< orphan*/  busNumber; } ;

/* Variables and functions */
 scalar_t__ HvCall3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvCallPciGetBusUnitInfo ; 

__attribute__((used)) static inline u64 HvCallPci_getBusUnitInfo(u16 busNumberParm, u8 subBusParm,
		u8 deviceIdParm, u64 parms, u32 sizeofParms)
{
	struct HvCallPci_DsaAddr dsa;

	*((u64*)&dsa) = 0;

	dsa.busNumber = busNumberParm;
	dsa.subBusNumber = subBusParm;
	dsa.deviceId = deviceIdParm;

	return HvCall3(HvCallPciGetBusUnitInfo, *(u64*)&dsa, parms,
			sizeofParms);
}