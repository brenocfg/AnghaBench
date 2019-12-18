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
struct pci_bus {unsigned char number; } ;

/* Variables and functions */
 size_t HI (int /*<<< orphan*/ ) ; 
 unsigned char KSEG1ADDR (int /*<<< orphan*/ ) ; 
 size_t LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NILE4_PCICTRL ; 
 int /*<<< orphan*/  NILE4_PCIERR ; 
 int /*<<< orphan*/  NILE4_PCIINIT1 ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 unsigned char PCI_ACCESS_WRITE ; 
 unsigned int PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCI_FUNC (unsigned int) ; 
 int PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  PCI_WINDOW1 ; 
 int* vrc_pciregs ; 

__attribute__((used)) static int nile4_pcibios_config_access(unsigned char access_type,
	struct pci_bus *bus, unsigned int devfn, int where, u32 *val)
{
	unsigned char busnum = bus->number;
	u32 adr, mask, err;

	if ((busnum == 0) && (PCI_SLOT(devfn) > 8))
		/* The addressing scheme chosen leaves room for just
		 * 8 devices on the first busnum (besides the PCI
		 * controller itself) */
		return PCIBIOS_DEVICE_NOT_FOUND;

	if ((busnum == 0) && (devfn == PCI_DEVFN(0, 0))) {
		/* Access controller registers directly */
		if (access_type == PCI_ACCESS_WRITE) {
			vrc_pciregs[(0x200 + where) >> 2] = *val;
		} else {
			*val = vrc_pciregs[(0x200 + where) >> 2];
		}
		return PCIBIOS_SUCCESSFUL;
	}

	/* Temporarily map PCI Window 1 to config space */
	mask = vrc_pciregs[LO(NILE4_PCIINIT1)];
	vrc_pciregs[LO(NILE4_PCIINIT1)] = 0x0000001a | (busnum ? 0x200 : 0);

	/* Clear PCI Error register. This also clears the Error Type
	 * bits in the Control register */
	vrc_pciregs[LO(NILE4_PCIERR)] = 0;
	vrc_pciregs[HI(NILE4_PCIERR)] = 0;

	/* Setup address */
	if (busnum == 0)
		adr =
		    KSEG1ADDR(PCI_WINDOW1) +
		    ((1 << (PCI_SLOT(devfn) + 15)) | (PCI_FUNC(devfn) << 8)
		     | (where & ~3));
	else
		adr = KSEG1ADDR(PCI_WINDOW1) | (busnum << 16) | (devfn << 8) |
		      (where & ~3);

	if (access_type == PCI_ACCESS_WRITE)
		*(u32 *) adr = *val;
	else
		*val = *(u32 *) adr;

	/* Check for master or target abort */
	err = (vrc_pciregs[HI(NILE4_PCICTRL)] >> 5) & 0x7;

	/* Restore PCI Window 1 */
	vrc_pciregs[LO(NILE4_PCIINIT1)] = mask;

	if (err)
		return PCIBIOS_DEVICE_NOT_FOUND;

	return PCIBIOS_SUCCESSFUL;
}