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
struct _parisc_agp_info {scalar_t__ lba_cap_offset; scalar_t__ lba_regs; int /*<<< orphan*/  gart_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; scalar_t__ capndx; int /*<<< orphan*/  gart_bus_addr; } ;

/* Variables and functions */
 scalar_t__ PCI_AGP_STATUS ; 
 TYPE_1__* agp_bridge ; 
 struct _parisc_agp_info parisc_agp_info ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int
parisc_agp_configure(void)
{
	struct _parisc_agp_info *info = &parisc_agp_info;

	agp_bridge->gart_bus_addr = info->gart_base;
	agp_bridge->capndx = info->lba_cap_offset;
	agp_bridge->mode = readl(info->lba_regs+info->lba_cap_offset+PCI_AGP_STATUS);

	return 0;
}