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
struct ata_link {int sata_spd_limit; int sata_spd; } ;
struct ata_device {int horkage; } ;

/* Variables and functions */
 int ATA_HORKAGE_1_5_GBPS ; 
 int EAGAIN ; 
 int /*<<< orphan*/  KERN_INFO ; 
 struct ata_link* ata_dev_phys_link (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sata_scr_valid (struct ata_link*) ; 
 int /*<<< orphan*/  sata_spd_string (int) ; 

__attribute__((used)) static int ata_do_link_spd_horkage(struct ata_device *dev)
{
	struct ata_link *plink = ata_dev_phys_link(dev);
	u32 target, target_limit;

	if (!sata_scr_valid(plink))
		return 0;

	if (dev->horkage & ATA_HORKAGE_1_5_GBPS)
		target = 1;
	else
		return 0;

	target_limit = (1 << target) - 1;

	/* if already on stricter limit, no need to push further */
	if (plink->sata_spd_limit <= target_limit)
		return 0;

	plink->sata_spd_limit = target_limit;

	/* Request another EH round by returning -EAGAIN if link is
	 * going faster than the target speed.  Forward progress is
	 * guaranteed by setting sata_spd_limit to target_limit above.
	 */
	if (plink->sata_spd > target) {
		ata_dev_printk(dev, KERN_INFO,
			       "applying link speed limit horkage to %s\n",
			       sata_spd_string(target));
		return -EAGAIN;
	}
	return 0;
}