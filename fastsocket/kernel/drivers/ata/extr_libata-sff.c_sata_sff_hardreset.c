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
struct ata_eh_context {int dummy; } ;
struct ata_link {int /*<<< orphan*/  device; struct ata_eh_context eh_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,unsigned int) ; 
 int /*<<< orphan*/  ata_sff_check_ready ; 
 unsigned int ata_sff_dev_classify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 unsigned long* sata_ehc_deb_timing (struct ata_eh_context*) ; 
 int sata_link_hardreset (struct ata_link*,unsigned long const*,unsigned long,int*,int /*<<< orphan*/ ) ; 

int sata_sff_hardreset(struct ata_link *link, unsigned int *class,
		       unsigned long deadline)
{
	struct ata_eh_context *ehc = &link->eh_context;
	const unsigned long *timing = sata_ehc_deb_timing(ehc);
	bool online;
	int rc;

	rc = sata_link_hardreset(link, timing, deadline, &online,
				 ata_sff_check_ready);
	if (online)
		*class = ata_sff_dev_classify(link->device, 1, NULL);

	DPRINTK("EXIT, class=%u\n", *class);
	return rc;
}