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
struct TYPE_2__ {unsigned int addr_data; int regspacing; int /*<<< orphan*/  regsize; int /*<<< orphan*/  outputb; int /*<<< orphan*/  inputb; } ;
struct smi_info {int io_size; TYPE_1__ io; int /*<<< orphan*/  dev; int /*<<< orphan*/  io_cleanup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_cleanup ; 
 int /*<<< orphan*/  port_inb ; 
 int /*<<< orphan*/  port_inl ; 
 int /*<<< orphan*/  port_inw ; 
 int /*<<< orphan*/  port_outb ; 
 int /*<<< orphan*/  port_outl ; 
 int /*<<< orphan*/  port_outw ; 
 int /*<<< orphan*/  release_region (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * request_region (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int port_setup(struct smi_info *info)
{
	unsigned int addr = info->io.addr_data;
	int          idx;

	if (!addr)
		return -ENODEV;

	info->io_cleanup = port_cleanup;

	/*
	 * Figure out the actual inb/inw/inl/etc routine to use based
	 * upon the register size.
	 */
	switch (info->io.regsize) {
	case 1:
		info->io.inputb = port_inb;
		info->io.outputb = port_outb;
		break;
	case 2:
		info->io.inputb = port_inw;
		info->io.outputb = port_outw;
		break;
	case 4:
		info->io.inputb = port_inl;
		info->io.outputb = port_outl;
		break;
	default:
		dev_warn(info->dev, "Invalid register size: %d\n",
			 info->io.regsize);
		return -EINVAL;
	}

	/*
	 * Some BIOSes reserve disjoint I/O regions in their ACPI
	 * tables.  This causes problems when trying to register the
	 * entire I/O region.  Therefore we must register each I/O
	 * port separately.
	 */
	for (idx = 0; idx < info->io_size; idx++) {
		if (request_region(addr + idx * info->io.regspacing,
				   info->io.regsize, DEVICE_NAME) == NULL) {
			/* Undo allocations */
			while (idx--) {
				release_region(addr + idx * info->io.regspacing,
					       info->io.regsize);
			}
			return -EIO;
		}
	}
	return 0;
}