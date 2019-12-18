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
struct TYPE_2__ {unsigned long addr_data; int regsize; int regspacing; int /*<<< orphan*/ * addr; int /*<<< orphan*/  outputb; int /*<<< orphan*/  inputb; } ;
struct smi_info {int io_size; TYPE_1__ io; int /*<<< orphan*/  dev; int /*<<< orphan*/  io_cleanup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  intf_mem_inb ; 
 int /*<<< orphan*/  intf_mem_inl ; 
 int /*<<< orphan*/  intf_mem_inw ; 
 int /*<<< orphan*/  intf_mem_outb ; 
 int /*<<< orphan*/  intf_mem_outl ; 
 int /*<<< orphan*/  intf_mem_outw ; 
 int /*<<< orphan*/ * ioremap (unsigned long,int) ; 
 int /*<<< orphan*/  mem_cleanup ; 
 int /*<<< orphan*/  mem_inq ; 
 int /*<<< orphan*/  mem_outq ; 
 int /*<<< orphan*/  release_mem_region (unsigned long,int) ; 
 int /*<<< orphan*/ * request_mem_region (unsigned long,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mem_setup(struct smi_info *info)
{
	unsigned long addr = info->io.addr_data;
	int           mapsize;

	if (!addr)
		return -ENODEV;

	info->io_cleanup = mem_cleanup;

	/*
	 * Figure out the actual readb/readw/readl/etc routine to use based
	 * upon the register size.
	 */
	switch (info->io.regsize) {
	case 1:
		info->io.inputb = intf_mem_inb;
		info->io.outputb = intf_mem_outb;
		break;
	case 2:
		info->io.inputb = intf_mem_inw;
		info->io.outputb = intf_mem_outw;
		break;
	case 4:
		info->io.inputb = intf_mem_inl;
		info->io.outputb = intf_mem_outl;
		break;
#ifdef readq
	case 8:
		info->io.inputb = mem_inq;
		info->io.outputb = mem_outq;
		break;
#endif
	default:
		dev_warn(info->dev, "Invalid register size: %d\n",
			 info->io.regsize);
		return -EINVAL;
	}

	/*
	 * Calculate the total amount of memory to claim.  This is an
	 * unusual looking calculation, but it avoids claiming any
	 * more memory than it has to.  It will claim everything
	 * between the first address to the end of the last full
	 * register.
	 */
	mapsize = ((info->io_size * info->io.regspacing)
		   - (info->io.regspacing - info->io.regsize));

	if (request_mem_region(addr, mapsize, DEVICE_NAME) == NULL)
		return -EIO;

	info->io.addr = ioremap(addr, mapsize);
	if (info->io.addr == NULL) {
		release_mem_region(addr, mapsize);
		return -EIO;
	}
	return 0;
}