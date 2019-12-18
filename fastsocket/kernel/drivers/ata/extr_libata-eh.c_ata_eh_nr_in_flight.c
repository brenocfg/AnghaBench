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
struct ata_port {int dummy; } ;

/* Variables and functions */
 int ATA_MAX_QUEUE ; 
 scalar_t__ ata_qc_from_tag (struct ata_port*,unsigned int) ; 

__attribute__((used)) static int ata_eh_nr_in_flight(struct ata_port *ap)
{
	unsigned int tag;
	int nr = 0;

	/* count only non-internal commands */
	for (tag = 0; tag < ATA_MAX_QUEUE - 1; tag++)
		if (ata_qc_from_tag(ap, tag))
			nr++;

	return nr;
}