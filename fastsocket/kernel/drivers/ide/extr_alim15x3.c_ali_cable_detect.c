#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int ATA_CBL_PATA40 ; 
 int ATA_CBL_PATA40_SHORT ; 
 int ATA_CBL_PATA80 ; 
 scalar_t__ ali_cable_override (struct pci_dev*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int m5229_revision ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 ali_cable_detect(ide_hwif_t *hwif)
{
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	unsigned long flags;
	u8 cbl = ATA_CBL_PATA40, tmpbyte;

	local_irq_save(flags);

	if (m5229_revision >= 0xC2) {
		/*
		 * m5229 80-pin cable detection (from Host View)
		 *
		 * 0x4a bit0 is 0 => primary channel has 80-pin
		 * 0x4a bit1 is 0 => secondary channel has 80-pin
		 *
		 * Certain laptops use short but suitable cables
		 * and don't implement the detect logic.
		 */
		if (ali_cable_override(dev))
			cbl = ATA_CBL_PATA40_SHORT;
		else {
			pci_read_config_byte(dev, 0x4a, &tmpbyte);
			if ((tmpbyte & (1 << hwif->channel)) == 0)
				cbl = ATA_CBL_PATA80;
		}
	}

	local_irq_restore(flags);

	return cbl;
}