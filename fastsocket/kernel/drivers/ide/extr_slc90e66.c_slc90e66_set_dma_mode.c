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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_5__ {scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ const XFER_MW_DMA_0 ; 
 scalar_t__ const XFER_UDMA_0 ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  slc90e66_set_pio_mode (TYPE_2__*,scalar_t__) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slc90e66_set_dma_mode(ide_drive_t *drive, const u8 speed)
{
	ide_hwif_t *hwif	= drive->hwif;
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	u8 maslave		= hwif->channel ? 0x42 : 0x40;
	int sitre = 0, a_speed	= 7 << (drive->dn * 4);
	int u_speed = 0, u_flag = 1 << drive->dn;
	u16			reg4042, reg44, reg48, reg4a;

	pci_read_config_word(dev, maslave, &reg4042);
	sitre = (reg4042 & 0x4000) ? 1 : 0;
	pci_read_config_word(dev, 0x44, &reg44);
	pci_read_config_word(dev, 0x48, &reg48);
	pci_read_config_word(dev, 0x4a, &reg4a);

	if (speed >= XFER_UDMA_0) {
		u_speed = (speed - XFER_UDMA_0) << (drive->dn * 4);

		if (!(reg48 & u_flag))
			pci_write_config_word(dev, 0x48, reg48|u_flag);
		if ((reg4a & a_speed) != u_speed) {
			pci_write_config_word(dev, 0x4a, reg4a & ~a_speed);
			pci_read_config_word(dev, 0x4a, &reg4a);
			pci_write_config_word(dev, 0x4a, reg4a|u_speed);
		}
	} else {
		const u8 mwdma_to_pio[] = { 0, 3, 4 };
		u8 pio;

		if (reg48 & u_flag)
			pci_write_config_word(dev, 0x48, reg48 & ~u_flag);
		if (reg4a & a_speed)
			pci_write_config_word(dev, 0x4a, reg4a & ~a_speed);

		if (speed >= XFER_MW_DMA_0)
			pio = mwdma_to_pio[speed - XFER_MW_DMA_0];
		else
			pio = 2; /* only SWDMA2 is allowed */

		slc90e66_set_pio_mode(drive, pio);
	}
}