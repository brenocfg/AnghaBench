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
struct TYPE_4__ {TYPE_1__* bridge_dev; int /*<<< orphan*/  ifp_resource; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCIBIOS_MIN_MEM ; 
 TYPE_2__ intel_private ; 
 int pci_bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pcibios_align_resource ; 

__attribute__((used)) static int intel_alloc_chipset_flush_resource(void)
{
	int ret;
	ret = pci_bus_alloc_resource(intel_private.bridge_dev->bus, &intel_private.ifp_resource, PAGE_SIZE,
				     PAGE_SIZE, PCIBIOS_MIN_MEM, 0,
				     pcibios_align_resource, intel_private.bridge_dev);

	return ret;
}