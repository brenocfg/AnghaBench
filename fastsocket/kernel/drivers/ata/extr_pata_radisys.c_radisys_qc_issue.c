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
struct ata_queued_cmd {struct ata_device* dev; struct ata_port* ap; } ;
struct ata_port {struct ata_device* private_data; } ;
struct ata_device {scalar_t__ dma_mode; scalar_t__ pio_mode; } ;

/* Variables and functions */
 scalar_t__ XFER_UDMA_0 ; 
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  radisys_set_dmamode (struct ata_port*,struct ata_device*) ; 
 int /*<<< orphan*/  radisys_set_piomode (struct ata_port*,struct ata_device*) ; 

__attribute__((used)) static unsigned int radisys_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *adev = qc->dev;

	if (adev != ap->private_data) {
		/* UDMA timing is not shared */
		if (adev->dma_mode < XFER_UDMA_0) {
			if (adev->dma_mode)
				radisys_set_dmamode(ap, adev);
			else if (adev->pio_mode)
				radisys_set_piomode(ap, adev);
		}
	}
	return ata_sff_qc_issue(qc);
}