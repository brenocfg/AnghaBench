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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int pio_mode; int devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  sis_set_fifo (struct ata_port*,struct ata_device*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_133_set_piomode (struct ata_port *ap, struct ata_device *adev)
{
	struct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int port = 0x40;
	u32 t1;
	u32 reg54;
	int speed = adev->pio_mode - XFER_PIO_0;

	const u32 timing133[] = {
		0x28269000,	/* Recovery << 24 | Act << 16 | Ini << 12 */
		0x0C266000,
		0x04263000,
		0x0C0A3000,
		0x05093000
	};
	const u32 timing100[] = {
		0x1E1C6000,	/* Recovery << 24 | Act << 16 | Ini << 12 */
		0x091C4000,
		0x031C2000,
		0x09072000,
		0x04062000
	};

	sis_set_fifo(ap, adev);

	/* If bit 14 is set then the registers are mapped at 0x70 not 0x40 */
	pci_read_config_dword(pdev, 0x54, &reg54);
	if (reg54 & 0x40000000)
		port = 0x70;
	port += 8 * ap->port_no +  4 * adev->devno;

	pci_read_config_dword(pdev, port, &t1);
	t1 &= 0xC0C00FFF;	/* Mask out timing */

	if (t1 & 0x08)		/* 100 or 133 ? */
		t1 |= timing133[speed];
	else
		t1 |= timing100[speed];
	pci_write_config_byte(pdev, port, t1);
}