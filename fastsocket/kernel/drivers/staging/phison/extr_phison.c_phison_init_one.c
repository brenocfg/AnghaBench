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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  struct ata_port_info {int pio_mask; int mwdma_mask; int /*<<< orphan*/ * port_ops; int /*<<< orphan*/  udma_mask; int /*<<< orphan*/  flags; } const ata_port_info ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_FLAG_NO_ATAPI ; 
 int /*<<< orphan*/  ATA_UDMA5 ; 
 int ata_pci_sff_init_one (struct pci_dev*,struct ata_port_info const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  phison_ops ; 
 int /*<<< orphan*/  phison_sht ; 

__attribute__((used)) static int phison_init_one(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int ret;
	struct ata_port_info info = {
		.flags		= ATA_FLAG_NO_ATAPI,

		.pio_mask	= 0x1f,
		.mwdma_mask	= 0x07,
		.udma_mask 	= ATA_UDMA5,

		.port_ops	= &phison_ops,
	};
	const struct ata_port_info *ppi[] = { &info, NULL };

	ret = ata_pci_sff_init_one(pdev, ppi, &phison_sht, NULL);

	dev_dbg(&pdev->dev, "phison_init_one(), ret = %x\n", ret);

	return ret;
}