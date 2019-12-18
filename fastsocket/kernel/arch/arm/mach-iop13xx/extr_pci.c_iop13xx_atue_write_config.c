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
typedef  int u32 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP13XX_ATUE_OCCAR ; 
 int /*<<< orphan*/  IOP13XX_ATUE_OCCDR ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 unsigned long iop13xx_atue_cfg_address (struct pci_bus*,unsigned int,int) ; 
 int /*<<< orphan*/  iop13xx_atue_pci_status (int) ; 
 int iop13xx_atue_read (unsigned long) ; 

__attribute__((used)) static int
iop13xx_atue_write_config(struct pci_bus *bus, unsigned int devfn, int where,
		int size, u32 value)
{
	unsigned long addr = iop13xx_atue_cfg_address(bus, devfn, where);
	u32 val;

	if (size != 4) {
		val = iop13xx_atue_read(addr);
		if (!iop13xx_atue_pci_status(1) == 0)
			return PCIBIOS_SUCCESSFUL;

		where = (where & 3) * 8;

		if (size == 1)
			val &= ~(0xff << where);
		else
			val &= ~(0xffff << where);

		__raw_writel(val | value << where, IOP13XX_ATUE_OCCDR);
	} else {
		__raw_writel(addr, IOP13XX_ATUE_OCCAR);
		__raw_writel(value, IOP13XX_ATUE_OCCDR);
	}

	return PCIBIOS_SUCCESSFUL;
}