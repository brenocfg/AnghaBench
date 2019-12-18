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
struct TYPE_2__ {int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {TYPE_1__ tf; int /*<<< orphan*/  tag; struct ata_device* dev; } ;
struct ata_device {int /*<<< orphan*/  flags; scalar_t__ udma_mask; scalar_t__ mwdma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DFLAG_DUBIOUS_XFER ; 
 scalar_t__ ata_is_nodata (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_is_pio (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_tag_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ata_verify_xfer(struct ata_queued_cmd *qc)
{
	struct ata_device *dev = qc->dev;

	if (ata_tag_internal(qc->tag))
		return;

	if (ata_is_nodata(qc->tf.protocol))
		return;

	if ((dev->mwdma_mask || dev->udma_mask) && ata_is_pio(qc->tf.protocol))
		return;

	dev->flags &= ~ATA_DFLAG_DUBIOUS_XFER;
}