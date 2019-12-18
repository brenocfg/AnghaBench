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
typedef  int /*<<< orphan*/  u8 ;
struct via82cxxx_dev {int via_80w; } ;
struct pci_dev {int dummy; } ;
struct ide_host {struct via82cxxx_dev* host_priv; } ;
struct TYPE_3__ {int channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA40 ; 
 int /*<<< orphan*/  ATA_CBL_PATA40_SHORT ; 
 int /*<<< orphan*/  ATA_CBL_PATA80 ; 
 struct ide_host* pci_get_drvdata (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ via_cable_override (struct pci_dev*) ; 

__attribute__((used)) static u8 via82cxxx_cable_detect(ide_hwif_t *hwif)
{
	struct pci_dev *pdev = to_pci_dev(hwif->dev);
	struct ide_host *host = pci_get_drvdata(pdev);
	struct via82cxxx_dev *vdev = host->host_priv;

	if (via_cable_override(pdev))
		return ATA_CBL_PATA40_SHORT;

	if ((vdev->via_80w >> hwif->channel) & 1)
		return ATA_CBL_PATA80;
	else
		return ATA_CBL_PATA40;
}