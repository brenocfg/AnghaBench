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
struct ata_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ata_dma_enabled (struct ata_device*) ; 
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  oldpiix_set_dmamode (struct ata_port*,struct ata_device*) ; 
 int /*<<< orphan*/  oldpiix_set_piomode (struct ata_port*,struct ata_device*) ; 

__attribute__((used)) static unsigned int oldpiix_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *adev = qc->dev;

	if (adev != ap->private_data) {
		oldpiix_set_piomode(ap, adev);
		if (ata_dma_enabled(adev))
			oldpiix_set_dmamode(ap, adev);
	}
	return ata_sff_qc_issue(qc);
}