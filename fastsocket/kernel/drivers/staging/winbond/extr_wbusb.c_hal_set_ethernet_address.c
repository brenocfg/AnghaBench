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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct hw_data {scalar_t__ CurrentMacAddress; scalar_t__ SurpriseRemove; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_INCREMENT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  Wb35Reg_BurstWrite (struct hw_data*,int,int*,int,int /*<<< orphan*/ ) ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hal_set_ethernet_address(struct hw_data *pHwData, u8 * current_address)
{
	u32 ltmp[2];

	if (pHwData->SurpriseRemove)
		return;

	memcpy(pHwData->CurrentMacAddress, current_address, ETH_ALEN);

	ltmp[0] = cpu_to_le32(*(u32 *) pHwData->CurrentMacAddress);
	ltmp[1] =
	    cpu_to_le32(*(u32 *) (pHwData->CurrentMacAddress + 4)) & 0xffff;

	Wb35Reg_BurstWrite(pHwData, 0x03e8, ltmp, 2, AUTO_INCREMENT);
}