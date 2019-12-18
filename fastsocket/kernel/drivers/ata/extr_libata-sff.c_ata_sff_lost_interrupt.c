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
typedef  int u8 ;
struct TYPE_4__ {int flags; } ;
struct ata_queued_cmd {TYPE_2__ tf; } ;
struct TYPE_3__ {int /*<<< orphan*/  active_tag; } ;
struct ata_port {TYPE_1__ link; } ;

/* Variables and functions */
 int ATA_BUSY ; 
 int ATA_TFLAG_POLLING ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  ata_port_printk (struct ata_port*,int /*<<< orphan*/ ,char*,int) ; 
 struct ata_queued_cmd* ata_qc_from_tag (struct ata_port*,int /*<<< orphan*/ ) ; 
 int ata_sff_altstatus (struct ata_port*) ; 
 int /*<<< orphan*/  ata_sff_host_intr (struct ata_port*,struct ata_queued_cmd*) ; 

void ata_sff_lost_interrupt(struct ata_port *ap)
{
	u8 status;
	struct ata_queued_cmd *qc;

	/* Only one outstanding command per SFF channel */
	qc = ata_qc_from_tag(ap, ap->link.active_tag);
	/* We cannot lose an interrupt on a non-existent or polled command */
	if (!qc || qc->tf.flags & ATA_TFLAG_POLLING)
		return;
	/* See if the controller thinks it is still busy - if so the command
	   isn't a lost IRQ but is still in progress */
	status = ata_sff_altstatus(ap);
	if (status & ATA_BUSY)
		return;

	/* There was a command running, we are no longer busy and we have
	   no interrupt. */
	ata_port_printk(ap, KERN_WARNING, "lost interrupt (Status 0x%x)\n",
								status);
	/* Run the host interrupt logic as if the interrupt had not been
	   lost */
	ata_sff_host_intr(ap, qc);
}