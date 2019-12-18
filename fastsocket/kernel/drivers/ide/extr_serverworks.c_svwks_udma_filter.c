#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct pci_dev {scalar_t__ device; scalar_t__ revision; int /*<<< orphan*/  devfn; } ;
struct TYPE_6__ {scalar_t__ media; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_SERVERWORKS_CSB6IDE ; 
 scalar_t__ PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2 ; 
 scalar_t__ PCI_DEVICE_ID_SERVERWORKS_HT1000IDE ; 
 scalar_t__ PCI_DEVICE_ID_SERVERWORKS_OSB4IDE ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 scalar_t__ SVWKS_CSB5_REVISION_NEW ; 
 scalar_t__ check_in_drive_lists (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ide_disk ; 
 scalar_t__ isa_dev ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (scalar_t__,int,int*) ; 
 int /*<<< orphan*/  svwks_bad_ata100 ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 svwks_udma_filter(ide_drive_t *drive)
{
	struct pci_dev *dev = to_pci_dev(drive->hwif->dev);
	u8 mask = 0;

	if (dev->device == PCI_DEVICE_ID_SERVERWORKS_HT1000IDE)
		return 0x1f;
	if (dev->device == PCI_DEVICE_ID_SERVERWORKS_OSB4IDE) {
		u32 reg = 0;
		if (isa_dev)
			pci_read_config_dword(isa_dev, 0x64, &reg);
			
		/*
		 *	Don't enable UDMA on disk devices for the moment
		 */
		if(drive->media == ide_disk)
			return 0;
		/* Check the OSB4 DMA33 enable bit */
		return ((reg & 0x00004000) == 0x00004000) ? 0x07 : 0;
	} else if (dev->revision < SVWKS_CSB5_REVISION_NEW) {
		return 0x07;
	} else if (dev->revision >= SVWKS_CSB5_REVISION_NEW) {
		u8 btr = 0, mode;
		pci_read_config_byte(dev, 0x5A, &btr);
		mode = btr & 0x3;

		/* If someone decides to do UDMA133 on CSB5 the same
		   issue will bite so be inclusive */
		if (mode > 2 && check_in_drive_lists(drive, svwks_bad_ata100))
			mode = 2;

		switch(mode) {
		case 3:	 mask = 0x3f; break;
		case 2:	 mask = 0x1f; break;
		case 1:	 mask = 0x07; break;
		default: mask = 0x00; break;
		}
	}
	if (((dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE) ||
	     (dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2)) &&
	    (!(PCI_FUNC(dev->devfn) & 1)))
		mask = 0x1f;

	return mask;
}