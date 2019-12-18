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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct ata_queued_cmd {struct ata_device* dev; struct ata_port* ap; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIIXP_IDE_UDMA_CONTROL ; 
 int /*<<< orphan*/  ata_bmdma_start (struct ata_queued_cmd*) ; 
 scalar_t__ ata_using_udma (struct ata_device*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atiixp_bmdma_start(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *adev = qc->dev;

	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int dn = (2 * ap->port_no) + adev->devno;
	u16 tmp16;

	pci_read_config_word(pdev, ATIIXP_IDE_UDMA_CONTROL, &tmp16);
	if (ata_using_udma(adev))
		tmp16 |= (1 << dn);
	else
		tmp16 &= ~(1 << dn);
	pci_write_config_word(pdev, ATIIXP_IDE_UDMA_CONTROL, tmp16);
	ata_bmdma_start(qc);
}