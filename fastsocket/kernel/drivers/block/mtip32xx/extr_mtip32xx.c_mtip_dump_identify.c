#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mtip_port {TYPE_2__* dd; scalar_t__ identify; int /*<<< orphan*/  identify_valid; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATA_SECT_SIZE ; 
 int /*<<< orphan*/  PCI_REVISION_ID ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ mtip_hw_get_capacity (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  pci_read_config_word (TYPE_1__*,int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static void mtip_dump_identify(struct mtip_port *port)
{
	sector_t sectors;
	unsigned short revid;
	char cbuf[42];

	if (!port->identify_valid)
		return;

	strlcpy(cbuf, (char *)(port->identify+10), 21);
	dev_info(&port->dd->pdev->dev,
		"Serial No.: %s\n", cbuf);

	strlcpy(cbuf, (char *)(port->identify+23), 9);
	dev_info(&port->dd->pdev->dev,
		"Firmware Ver.: %s\n", cbuf);

	strlcpy(cbuf, (char *)(port->identify+27), 41);
	dev_info(&port->dd->pdev->dev, "Model: %s\n", cbuf);

	if (mtip_hw_get_capacity(port->dd, &sectors))
		dev_info(&port->dd->pdev->dev,
			"Capacity: %llu sectors (%llu MB)\n",
			 (u64)sectors,
			 ((u64)sectors) * ATA_SECT_SIZE >> 20);

	pci_read_config_word(port->dd->pdev, PCI_REVISION_ID, &revid);
	switch (revid & 0xFF) {
	case 0x1:
		strlcpy(cbuf, "A0", 3);
		break;
	case 0x3:
		strlcpy(cbuf, "A2", 3);
		break;
	default:
		strlcpy(cbuf, "?", 2);
		break;
	}
	dev_info(&port->dd->pdev->dev,
		"Card Type: %s\n", cbuf);
}