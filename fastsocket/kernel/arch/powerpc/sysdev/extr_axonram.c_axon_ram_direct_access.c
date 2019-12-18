#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct block_device {TYPE_3__* bd_part; TYPE_2__* bd_disk; } ;
struct axon_ram_bank {scalar_t__ ph_addr; TYPE_1__* device; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {scalar_t__ start_sect; } ;
struct TYPE_5__ {struct axon_ram_bank* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXON_RAM_SECTOR_SHIFT ; 
 int ERANGE ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long virt_to_phys (void**) ; 

__attribute__((used)) static int
axon_ram_direct_access(struct block_device *device, sector_t sector,
		       void **kaddr, unsigned long *pfn)
{
	struct axon_ram_bank *bank = device->bd_disk->private_data;
	loff_t offset;

	offset = sector;
	if (device->bd_part != NULL)
		offset += device->bd_part->start_sect;
	offset <<= AXON_RAM_SECTOR_SHIFT;
	if (offset >= bank->size) {
		dev_err(&bank->device->dev, "Access outside of address space\n");
		return -ERANGE;
	}

	*kaddr = (void *)(bank->ph_addr + offset);
	*pfn = virt_to_phys(kaddr) >> PAGE_SHIFT;

	return 0;
}