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
struct ata_link {int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  ata_link_printk (struct ata_link*,int /*<<< orphan*/ ,char*) ; 
 int sata_std_hardreset (struct ata_link*,unsigned int*,unsigned long) ; 
 int sil24_init_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sil24_pmp_hardreset(struct ata_link *link, unsigned int *class,
			       unsigned long deadline)
{
	int rc;

	rc = sil24_init_port(link->ap);
	if (rc) {
		ata_link_printk(link, KERN_ERR,
				"hardreset failed (port not ready)\n");
		return rc;
	}

	return sata_std_hardreset(link, class, deadline);
}