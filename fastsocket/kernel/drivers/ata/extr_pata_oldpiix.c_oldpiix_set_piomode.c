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
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct ata_port {struct ata_device* private_data; scalar_t__ port_no; TYPE_1__* host; } ;
struct ata_device {unsigned int pio_mode; scalar_t__ class; scalar_t__ devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 unsigned int XFER_PIO_0 ; 
 scalar_t__ ata_pio_need_iordy (struct ata_device*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,unsigned int,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,unsigned int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void oldpiix_set_piomode (struct ata_port *ap, struct ata_device *adev)
{
	unsigned int pio	= adev->pio_mode - XFER_PIO_0;
	struct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned int idetm_port= ap->port_no ? 0x42 : 0x40;
	u16 idetm_data;
	int control = 0;

	/*
	 *	See Intel Document 298600-004 for the timing programing rules
	 *	for PIIX/ICH. Note that the early PIIX does not have the slave
	 *	timing port at 0x44.
	 */

	static const	 /* ISP  RTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	if (pio > 1)
		control |= 1;	/* TIME */
	if (ata_pio_need_iordy(adev))
		control |= 2;	/* IE */

	/* Intel specifies that the prefetch/posting is for disk only */
	if (adev->class == ATA_DEV_ATA)
		control |= 4;	/* PPE */

	pci_read_config_word(dev, idetm_port, &idetm_data);

	/*
	 * Set PPE, IE and TIME as appropriate.
	 * Clear the other drive's timing bits.
	 */
	if (adev->devno == 0) {
		idetm_data &= 0xCCE0;
		idetm_data |= control;
	} else {
		idetm_data &= 0xCC0E;
		idetm_data |= (control << 4);
	}
	idetm_data |= (timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	pci_write_config_word(dev, idetm_port, idetm_data);

	/* Track which port is configured */
	ap->private_data = adev;
}