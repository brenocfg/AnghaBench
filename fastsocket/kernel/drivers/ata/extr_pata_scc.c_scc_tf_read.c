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
struct ata_taskfile {int flags; int ctl; void* hob_lbah; void* hob_lbam; void* hob_lbal; void* hob_nsect; void* hob_feature; void* device; void* lbah; void* lbam; void* lbal; void* nsect; void* feature; int /*<<< orphan*/  command; } ;
struct ata_ioports {int /*<<< orphan*/  ctl_addr; int /*<<< orphan*/  lbah_addr; int /*<<< orphan*/  lbam_addr; int /*<<< orphan*/  lbal_addr; int /*<<< orphan*/  nsect_addr; int /*<<< orphan*/  error_addr; int /*<<< orphan*/  device_addr; } ;
struct ata_port {int last_ctl; struct ata_ioports ioaddr; } ;

/* Variables and functions */
 int ATA_HOB ; 
 int ATA_TFLAG_LBA48 ; 
 void* in_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scc_check_status (struct ata_port*) ; 

__attribute__((used)) static void scc_tf_read (struct ata_port *ap, struct ata_taskfile *tf)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;

	tf->command = scc_check_status(ap);
	tf->feature = in_be32(ioaddr->error_addr);
	tf->nsect = in_be32(ioaddr->nsect_addr);
	tf->lbal = in_be32(ioaddr->lbal_addr);
	tf->lbam = in_be32(ioaddr->lbam_addr);
	tf->lbah = in_be32(ioaddr->lbah_addr);
	tf->device = in_be32(ioaddr->device_addr);

	if (tf->flags & ATA_TFLAG_LBA48) {
		out_be32(ioaddr->ctl_addr, tf->ctl | ATA_HOB);
		tf->hob_feature = in_be32(ioaddr->error_addr);
		tf->hob_nsect = in_be32(ioaddr->nsect_addr);
		tf->hob_lbal = in_be32(ioaddr->lbal_addr);
		tf->hob_lbam = in_be32(ioaddr->lbam_addr);
		tf->hob_lbah = in_be32(ioaddr->lbah_addr);
		out_be32(ioaddr->ctl_addr, tf->ctl);
		ap->last_ctl = tf->ctl;
	}
}