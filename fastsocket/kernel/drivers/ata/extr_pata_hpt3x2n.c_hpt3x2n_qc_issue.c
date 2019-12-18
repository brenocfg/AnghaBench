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
struct ata_queued_cmd {TYPE_2__ tf; struct ata_port* ap; } ;
struct ata_port {TYPE_1__* host; } ;
struct TYPE_3__ {void* private_data; } ;

/* Variables and functions */
 int ATA_TFLAG_WRITE ; 
 int USE_DPLL ; 
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  hpt3x2n_set_clock (struct ata_port*,int) ; 
 int hpt3x2n_use_dpll (struct ata_port*,int) ; 

__attribute__((used)) static unsigned int hpt3x2n_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	int flags = (long)ap->host->private_data;
	int dpll = hpt3x2n_use_dpll(ap, qc->tf.flags & ATA_TFLAG_WRITE);

	if ((flags & USE_DPLL) != dpll) {
		flags &= ~USE_DPLL;
		flags |= dpll;
		ap->host->private_data = (void *)(long)flags;

		hpt3x2n_set_clock(ap, dpll ? 0x21 : 0x23);
	}
	return ata_sff_qc_issue(qc);
}