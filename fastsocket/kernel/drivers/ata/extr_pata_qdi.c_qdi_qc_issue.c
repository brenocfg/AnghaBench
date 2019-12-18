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
struct qdi_data {scalar_t__* clock; scalar_t__ last; int /*<<< orphan*/  timing; } ;
struct ata_queued_cmd {struct ata_device* dev; struct ata_port* ap; } ;
struct ata_port {TYPE_1__* host; } ;
struct ata_device {size_t devno; scalar_t__ pio_mode; } ;
struct TYPE_2__ {struct qdi_data* private_data; } ;

/* Variables and functions */
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  outb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int qdi_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *adev = qc->dev;
	struct qdi_data *qdi = ap->host->private_data;

	if (qdi->clock[adev->devno] != qdi->last) {
		if (adev->pio_mode) {
			qdi->last = qdi->clock[adev->devno];
			outb(qdi->clock[adev->devno], qdi->timing);
		}
	}
	return ata_sff_qc_issue(qc);
}