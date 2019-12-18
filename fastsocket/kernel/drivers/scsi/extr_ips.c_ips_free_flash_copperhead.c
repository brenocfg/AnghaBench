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
struct TYPE_3__ {int /*<<< orphan*/ * flash_data; int /*<<< orphan*/  flash_busaddr; int /*<<< orphan*/  flash_len; int /*<<< orphan*/  pcidev; } ;
typedef  TYPE_1__ ips_ha_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ips_FlashData ; 
 int /*<<< orphan*/  ips_FlashDataInUse ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ips_free_flash_copperhead(ips_ha_t * ha)
{
	if (ha->flash_data == ips_FlashData)
		test_and_clear_bit(0, &ips_FlashDataInUse);
	else if (ha->flash_data)
		pci_free_consistent(ha->pcidev, ha->flash_len, ha->flash_data,
				    ha->flash_busaddr);
	ha->flash_data = NULL;
}