#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ const XFER_UDMA_0 ; 
 scalar_t__ const XFER_UDMA_3 ; 
 scalar_t__ const XFER_UDMA_6 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,scalar_t__) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ali_set_dma_mode(ide_drive_t *drive, const u8 speed)
{
	ide_hwif_t *hwif	= drive->hwif;
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	u8 speed1		= speed;
	u8 unit			= drive->dn & 1;
	u8 tmpbyte		= 0x00;
	int m5229_udma		= (hwif->channel) ? 0x57 : 0x56;

	if (speed == XFER_UDMA_6)
		speed1 = 0x47;

	if (speed < XFER_UDMA_0) {
		u8 ultra_enable	= (unit) ? 0x7f : 0xf7;
		/*
		 * clear "ultra enable" bit
		 */
		pci_read_config_byte(dev, m5229_udma, &tmpbyte);
		tmpbyte &= ultra_enable;
		pci_write_config_byte(dev, m5229_udma, tmpbyte);

		/*
		 * FIXME: Oh, my... DMA timings are never set.
		 */
	} else {
		pci_read_config_byte(dev, m5229_udma, &tmpbyte);
		tmpbyte &= (0x0f << ((1-unit) << 2));
		/*
		 * enable ultra dma and set timing
		 */
		tmpbyte |= ((0x08 | ((4-speed1)&0x07)) << (unit << 2));
		pci_write_config_byte(dev, m5229_udma, tmpbyte);
		if (speed >= XFER_UDMA_3) {
			pci_read_config_byte(dev, 0x4b, &tmpbyte);
			tmpbyte |= 1;
			pci_write_config_byte(dev, 0x4b, tmpbyte);
		}
	}
}