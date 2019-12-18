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
struct ata_link {int sata_spd; int sata_spd_limit; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  SCR_STATUS ; 
 int /*<<< orphan*/  ata_link_printk (struct ata_link*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ata_sstatus_online (int) ; 
 int ffs (int) ; 
 int fls (int) ; 
 int sata_scr_read (struct ata_link*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sata_scr_valid (struct ata_link*) ; 
 int /*<<< orphan*/  sata_spd_string (int) ; 

int sata_down_spd_limit(struct ata_link *link, u32 spd_limit)
{
	u32 sstatus, spd, mask;
	int rc, bit;

	if (!sata_scr_valid(link))
		return -EOPNOTSUPP;

	/* If SCR can be read, use it to determine the current SPD.
	 * If not, use cached value in link->sata_spd.
	 */
	rc = sata_scr_read(link, SCR_STATUS, &sstatus);
	if (rc == 0 && ata_sstatus_online(sstatus))
		spd = (sstatus >> 4) & 0xf;
	else
		spd = link->sata_spd;

	mask = link->sata_spd_limit;
	if (mask <= 1)
		return -EINVAL;

	/* unconditionally mask off the highest bit */
	bit = fls(mask) - 1;
	mask &= ~(1 << bit);

	/* Mask off all speeds higher than or equal to the current
	 * one.  Force 1.5Gbps if current SPD is not available.
	 */
	if (spd > 1)
		mask &= (1 << (spd - 1)) - 1;
	else
		mask &= 1;

	/* were we already at the bottom? */
	if (!mask)
		return -EINVAL;

	if (spd_limit) {
		if (mask & ((1 << spd_limit) - 1))
			mask &= (1 << spd_limit) - 1;
		else {
			bit = ffs(mask) - 1;
			mask = 1 << bit;
		}
	}

	link->sata_spd_limit = mask;

	ata_link_printk(link, KERN_WARNING, "limiting SATA link speed to %s\n",
			sata_spd_string(fls(mask)));

	return 0;
}