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
struct TYPE_4__ {int flags; } ;
struct ata_queued_cmd {TYPE_2__ tf; } ;
struct TYPE_3__ {int /*<<< orphan*/  active_tag; } ;
struct ata_port {TYPE_1__ link; } ;
struct ata_host {unsigned int n_ports; int /*<<< orphan*/  lock; struct ata_port** ports; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ATA_TFLAG_POLLING ; 
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 struct ata_queued_cmd* ata_qc_from_tag (struct ata_port*,int /*<<< orphan*/ ) ; 
 unsigned int bfin_ata_host_intr (struct ata_port*,struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t bfin_ata_interrupt(int irq, void *dev_instance)
{
	struct ata_host *host = dev_instance;
	unsigned int i;
	unsigned int handled = 0;
	unsigned long flags;

	/* TODO: make _irqsave conditional on x86 PCI IDE legacy mode */
	spin_lock_irqsave(&host->lock, flags);

	for (i = 0; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];
		struct ata_queued_cmd *qc;

		qc = ata_qc_from_tag(ap, ap->link.active_tag);
		if (qc && (!(qc->tf.flags & ATA_TFLAG_POLLING)))
			handled |= bfin_ata_host_intr(ap, qc);
	}

	spin_unlock_irqrestore(&host->lock, flags);

	return IRQ_RETVAL(handled);
}