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
struct ata_port {int flags; } ;
struct TYPE_2__ {int action; } ;
struct ata_eh_context {TYPE_1__ i; } ;
struct ata_link {struct ata_eh_context eh_context; struct ata_port* ap; } ;

/* Variables and functions */
 int ATA_EH_HARDRESET ; 
 int ATA_EH_SOFTRESET ; 
 int ATA_FLAG_SATA ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  ata_link_printk (struct ata_link*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ata_phys_link_offline (struct ata_link*) ; 
 unsigned long* sata_ehc_deb_timing (struct ata_eh_context*) ; 
 int sata_link_resume (struct ata_link*,unsigned long const*,unsigned long) ; 

int ata_std_prereset(struct ata_link *link, unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct ata_eh_context *ehc = &link->eh_context;
	const unsigned long *timing = sata_ehc_deb_timing(ehc);
	int rc;

	/* if we're about to do hardreset, nothing more to do */
	if (ehc->i.action & ATA_EH_HARDRESET)
		return 0;

	/* if SATA, resume link */
	if (ap->flags & ATA_FLAG_SATA) {
		rc = sata_link_resume(link, timing, deadline);
		/* whine about phy resume failure but proceed */
		if (rc && rc != -EOPNOTSUPP)
			ata_link_printk(link, KERN_WARNING, "failed to resume "
					"link for reset (errno=%d)\n", rc);
	}

	/* no point in trying softreset on offline link */
	if (ata_phys_link_offline(link))
		ehc->i.action &= ~ATA_EH_SOFTRESET;

	return 0;
}