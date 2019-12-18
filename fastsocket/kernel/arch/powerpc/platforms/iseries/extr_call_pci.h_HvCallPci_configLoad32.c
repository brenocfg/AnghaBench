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
struct HvCallPci_LoadReturn {scalar_t__ rc; int /*<<< orphan*/  value; } ;
struct HvCallPci_DsaAddr {void* deviceId; void* subBusNumber; int /*<<< orphan*/  busNumber; } ;

/* Variables and functions */
 int /*<<< orphan*/  HvCall3Ret16 (int /*<<< orphan*/ ,struct HvCallPci_LoadReturn*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvCallPciConfigLoad32 ; 

__attribute__((used)) static inline u64 HvCallPci_configLoad32(u16 busNumber, u8 subBusNumber,
		u8 deviceId, u32 offset, u32 *value)
{
	struct HvCallPci_DsaAddr dsa;
	struct HvCallPci_LoadReturn retVal;

	*((u64*)&dsa) = 0;

	dsa.busNumber = busNumber;
	dsa.subBusNumber = subBusNumber;
	dsa.deviceId = deviceId;

	HvCall3Ret16(HvCallPciConfigLoad32, &retVal, *(u64 *)&dsa, offset, 0);

	*value = retVal.value;

	return retVal.rc;
}