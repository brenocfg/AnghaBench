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
typedef  int /*<<< orphan*/  u16 ;
struct HvCallPci_LoadReturn {scalar_t__ rc; } ;
struct HvCallPci_DsaAddr {void* deviceId; void* subBusNumber; int /*<<< orphan*/  busNumber; } ;

/* Variables and functions */
 int /*<<< orphan*/  HvCall1Ret16 (int /*<<< orphan*/ ,struct HvCallPci_LoadReturn*,scalar_t__) ; 
 int /*<<< orphan*/  HvCallPciEoi ; 

__attribute__((used)) static inline u64 HvCallPci_eoi(u16 busNumberParm, u8 subBusParm,
		u8 deviceIdParm)
{
	struct HvCallPci_DsaAddr dsa;
	struct HvCallPci_LoadReturn retVal;

	*((u64*)&dsa) = 0;

	dsa.busNumber = busNumberParm;
	dsa.subBusNumber = subBusParm;
	dsa.deviceId = deviceIdParm;

	HvCall1Ret16(HvCallPciEoi, &retVal, *(u64*)&dsa);

	return retVal.rc;
}