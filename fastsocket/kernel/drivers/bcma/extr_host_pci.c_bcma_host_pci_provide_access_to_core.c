#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {int id; } ;
struct bcma_device {TYPE_2__* bus; TYPE_1__ id; } ;
struct TYPE_4__ {struct bcma_device* mapped_core; } ;

/* Variables and functions */
#define  BCMA_CORE_CHIPCOMMON 129 
#define  BCMA_CORE_PCIE 128 
 int BCMA_CORE_SIZE ; 
 int /*<<< orphan*/  bcma_host_pci_switch_core (struct bcma_device*) ; 

__attribute__((used)) static u16 bcma_host_pci_provide_access_to_core(struct bcma_device *core)
{
	switch (core->id.id) {
	case BCMA_CORE_CHIPCOMMON:
		return 3 * BCMA_CORE_SIZE;
	case BCMA_CORE_PCIE:
		return 2 * BCMA_CORE_SIZE;
	}

	if (core->bus->mapped_core != core)
		bcma_host_pci_switch_core(core);
	return 0;
}