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
typedef  int /*<<< orphan*/  u32 ;
struct ata_link {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int SATA_PMP_PSCR_CONTROL ; 
 int /*<<< orphan*/  ata_link_printk (struct ata_link*,int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 unsigned int sata_pmp_write (struct ata_link*,int,int /*<<< orphan*/ ) ; 

int sata_pmp_scr_write(struct ata_link *link, int reg, u32 val)
{
	unsigned int err_mask;

	if (reg > SATA_PMP_PSCR_CONTROL)
		return -EINVAL;

	err_mask = sata_pmp_write(link, reg, val);
	if (err_mask) {
		ata_link_printk(link, KERN_WARNING, "failed to write SCR %d "
				"(Emask=0x%x)\n", reg, err_mask);
		return -EIO;
	}
	return 0;
}