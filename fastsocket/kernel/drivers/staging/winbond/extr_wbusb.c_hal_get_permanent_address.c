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
struct hw_data {int /*<<< orphan*/  PermanentMacAddress; scalar_t__ SurpriseRemove; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hal_get_permanent_address(struct hw_data *pHwData, u8 * pethernet_address)
{
	if (pHwData->SurpriseRemove)
		return;

	memcpy(pethernet_address, pHwData->PermanentMacAddress, 6);
}