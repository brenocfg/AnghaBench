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
struct ata_queued_cmd {struct ata_port* ap; } ;
struct TYPE_2__ {scalar_t__ bmdma_addr; } ;
struct ata_port {int /*<<< orphan*/  lock; TYPE_1__ ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_bmdma_stop (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void ata_sff_post_internal_cmd(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	unsigned long flags;

	spin_lock_irqsave(ap->lock, flags);

	if (ap->ioaddr.bmdma_addr)
		ata_bmdma_stop(qc);

	spin_unlock_irqrestore(ap->lock, flags);
}