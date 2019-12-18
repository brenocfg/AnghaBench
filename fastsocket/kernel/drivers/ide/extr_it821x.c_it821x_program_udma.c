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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct it821x_dev {scalar_t__ clock_mode; scalar_t__ timing10; } ;
struct TYPE_5__ {int channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ ATA_66 ; 
 struct it821x_dev* ide_get_hwifdata (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void it821x_program_udma(ide_drive_t *drive, u16 timing)
{
	ide_hwif_t *hwif = drive->hwif;
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	struct it821x_dev *itdev = ide_get_hwifdata(hwif);
	int channel = hwif->channel;
	u8 unit = drive->dn & 1, conf;

	/* Program UDMA timing bits */
	if(itdev->clock_mode == ATA_66)
		conf = timing >> 8;
	else
		conf = timing & 0xFF;

	if (itdev->timing10 == 0)
		pci_write_config_byte(dev, 0x56 + 4 * channel + unit, conf);
	else {
		pci_write_config_byte(dev, 0x56 + 4 * channel, conf);
		pci_write_config_byte(dev, 0x56 + 4 * channel + 1, conf);
	}
}