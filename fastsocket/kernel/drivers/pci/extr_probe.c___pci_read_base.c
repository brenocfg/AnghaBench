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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct resource {int flags; int /*<<< orphan*/  name; } ;
struct pci_dev_rh1 {int /*<<< orphan*/  mmio_always_on; } ;
struct pci_dev {scalar_t__ rh_reserved1; int /*<<< orphan*/  dev; } ;
struct pci_bus_region {int start; int end; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  enum pci_bar_type { ____Placeholder_pci_bar_type } pci_bar_type ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM_64 ; 
 int IORESOURCE_ROM_ENABLE ; 
 int IORESOURCE_SIZEALIGN ; 
 int IO_SPACE_LIMIT ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int PCI_BASE_ADDRESS_IO_MASK ; 
 int PCI_BASE_ADDRESS_MEM_MASK ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MEMORY ; 
 int PCI_ROM_ADDRESS_ENABLE ; 
 int PCI_ROM_ADDRESS_MASK ; 
 int decode_bar (struct pci_dev*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned int,struct resource*) ; 
 int pci_bar_unknown ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,unsigned int,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int pci_size (int,int,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,unsigned int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcibios_bus_to_resource (struct pci_dev*,struct resource*,struct pci_bus_region*) ; 

int __pci_read_base(struct pci_dev *dev, enum pci_bar_type type,
			struct resource *res, unsigned int pos)
{
	u32 l, sz, mask;
	u16 orig_cmd;
	struct pci_bus_region region;

	mask = type ? ~PCI_ROM_ADDRESS_ENABLE : ~0;

	if (!((struct pci_dev_rh1 *)dev->rh_reserved1)->mmio_always_on) {
		pci_read_config_word(dev, PCI_COMMAND, &orig_cmd);
		pci_write_config_word(dev, PCI_COMMAND,
			orig_cmd & ~(PCI_COMMAND_MEMORY | PCI_COMMAND_IO));
	}

	res->name = pci_name(dev);

	pci_read_config_dword(dev, pos, &l);
	pci_write_config_dword(dev, pos, mask);
	pci_read_config_dword(dev, pos, &sz);
	pci_write_config_dword(dev, pos, l);

	/*
	 * All bits set in sz means the device isn't working properly.
	 * If the BAR isn't implemented, all bits must be 0.  If it's a
	 * memory BAR or a ROM, bit 0 must be clear; if it's an io BAR, bit
	 * 1 must be clear.
	 */
	if (!sz || sz == 0xffffffff)
		goto fail;

	/*
	 * I don't know how l can have all bits set.  Copied from old code.
	 * Maybe it fixes a bug on some ancient platform.
	 */
	if (l == 0xffffffff)
		l = 0;

	if (type == pci_bar_unknown) {
		res->flags = decode_bar(dev, l);
		res->flags |= IORESOURCE_SIZEALIGN;
		if (res->flags & IORESOURCE_IO) {
			l &= PCI_BASE_ADDRESS_IO_MASK;
			mask = PCI_BASE_ADDRESS_IO_MASK & IO_SPACE_LIMIT;
		} else {
			l &= PCI_BASE_ADDRESS_MEM_MASK;
			mask = (u32)PCI_BASE_ADDRESS_MEM_MASK;
		}
	} else {
		res->flags |= (l & IORESOURCE_ROM_ENABLE);
		l &= PCI_ROM_ADDRESS_MASK;
		mask = (u32)PCI_ROM_ADDRESS_MASK;
	}

	if (res->flags & IORESOURCE_MEM_64) {
		u64 l64 = l;
		u64 sz64 = sz;
		u64 mask64 = mask | (u64)~0 << 32;

		pci_read_config_dword(dev, pos + 4, &l);
		pci_write_config_dword(dev, pos + 4, ~0);
		pci_read_config_dword(dev, pos + 4, &sz);
		pci_write_config_dword(dev, pos + 4, l);

		l64 |= ((u64)l << 32);
		sz64 |= ((u64)sz << 32);

		sz64 = pci_size(l64, sz64, mask64);

		if (!sz64)
			goto fail;

		if ((sizeof(resource_size_t) < 8) && (sz64 > 0x100000000ULL)) {
			dev_err(&dev->dev, "reg %x: can't handle 64-bit BAR\n",
				pos);
			goto fail;
		}

		if ((sizeof(resource_size_t) < 8) && l) {
			/* Address above 32-bit boundary; disable the BAR */
			pci_write_config_dword(dev, pos, 0);
			pci_write_config_dword(dev, pos + 4, 0);
			region.start = 0;
			region.end = sz64;
			pcibios_bus_to_resource(dev, res, &region);
		} else {
			region.start = l64;
			region.end = l64 + sz64;
			pcibios_bus_to_resource(dev, res, &region);
			dev_printk(KERN_DEBUG, &dev->dev, "reg %x: %pR\n",
				   pos, res);
		}
	} else {
		sz = pci_size(l, sz, mask);

		if (!sz)
			goto fail;

		region.start = l;
		region.end = l + sz;
		pcibios_bus_to_resource(dev, res, &region);

		dev_printk(KERN_DEBUG, &dev->dev, "reg %x: %pR\n", pos, res);
	}

 out:
	if (!((struct pci_dev_rh1 *)dev->rh_reserved1)->mmio_always_on)
		pci_write_config_word(dev, PCI_COMMAND, orig_cmd);

	return (res->flags & IORESOURCE_MEM_64) ? 1 : 0;
 fail:
	res->flags = 0;
	goto out;
}