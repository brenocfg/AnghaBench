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
typedef  int u32 ;
struct ata_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCR_CONTROL ; 
 int /*<<< orphan*/  SCR_STATUS ; 
 int /*<<< orphan*/  ata_link_printk (struct ata_link*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 scalar_t__ ata_phys_link_online (struct ata_link*) ; 
 scalar_t__ sata_scr_read (struct ata_link*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sata_spd_string (int) ; 

__attribute__((used)) static void sata_print_link_status(struct ata_link *link)
{
	u32 sstatus, scontrol, tmp;

	if (sata_scr_read(link, SCR_STATUS, &sstatus))
		return;
	sata_scr_read(link, SCR_CONTROL, &scontrol);

	if (ata_phys_link_online(link)) {
		tmp = (sstatus >> 4) & 0xf;
		ata_link_printk(link, KERN_INFO,
				"SATA link up %s (SStatus %X SControl %X)\n",
				sata_spd_string(tmp), sstatus, scontrol);
	} else {
		ata_link_printk(link, KERN_INFO,
				"SATA link down (SStatus %X SControl %X)\n",
				sstatus, scontrol);
	}
}