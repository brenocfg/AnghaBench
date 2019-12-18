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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int flags; } ;
struct ata_eh_context {TYPE_2__ i; } ;
struct ata_device {scalar_t__ class; int horkage; int /*<<< orphan*/  id; scalar_t__ n_native_sectors; TYPE_1__* link; } ;
struct TYPE_3__ {struct ata_eh_context eh_context; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 int ATA_EHI_PRINTINFO ; 
 int ATA_HORKAGE_BROKEN_HPA ; 
 int EACCES ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,...) ; 
 int ata_dev_reread_id (struct ata_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_id_has_lba (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_id_hpa_enabled (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_n_sectors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_ignore_hpa ; 
 int ata_read_native_max_address (struct ata_device*,scalar_t__*) ; 
 int ata_set_max_sectors (struct ata_device*,scalar_t__) ; 

__attribute__((used)) static int ata_hpa_resize(struct ata_device *dev)
{
	struct ata_eh_context *ehc = &dev->link->eh_context;
	int print_info = ehc->i.flags & ATA_EHI_PRINTINFO;
	u64 sectors = ata_id_n_sectors(dev->id);
	u64 native_sectors;
	int rc;

	/* do we need to do it? */
	if (dev->class != ATA_DEV_ATA ||
	    !ata_id_has_lba(dev->id) || !ata_id_hpa_enabled(dev->id) ||
	    (dev->horkage & ATA_HORKAGE_BROKEN_HPA))
		return 0;

	/* read native max address */
	rc = ata_read_native_max_address(dev, &native_sectors);
	if (rc) {
		/* If device aborted the command or HPA isn't going to
		 * be unlocked, skip HPA resizing.
		 */
		if (rc == -EACCES || !ata_ignore_hpa) {
			ata_dev_printk(dev, KERN_WARNING, "HPA support seems "
				       "broken, skipping HPA handling\n");
			dev->horkage |= ATA_HORKAGE_BROKEN_HPA;

			/* we can continue if device aborted the command */
			if (rc == -EACCES)
				rc = 0;
		}

		return rc;
	}
	dev->n_native_sectors = native_sectors;

	/* nothing to do? */
	if (native_sectors <= sectors || !ata_ignore_hpa) {
		if (!print_info || native_sectors == sectors)
			return 0;

		if (native_sectors > sectors)
			ata_dev_printk(dev, KERN_INFO,
				"HPA detected: current %llu, native %llu\n",
				(unsigned long long)sectors,
				(unsigned long long)native_sectors);
		else if (native_sectors < sectors)
			ata_dev_printk(dev, KERN_WARNING,
				"native sectors (%llu) is smaller than "
				"sectors (%llu)\n",
				(unsigned long long)native_sectors,
				(unsigned long long)sectors);
		return 0;
	}

	/* let's unlock HPA */
	rc = ata_set_max_sectors(dev, native_sectors);
	if (rc == -EACCES) {
		/* if device aborted the command, skip HPA resizing */
		ata_dev_printk(dev, KERN_WARNING, "device aborted resize "
			       "(%llu -> %llu), skipping HPA handling\n",
			       (unsigned long long)sectors,
			       (unsigned long long)native_sectors);
		dev->horkage |= ATA_HORKAGE_BROKEN_HPA;
		return 0;
	} else if (rc)
		return rc;

	/* re-read IDENTIFY data */
	rc = ata_dev_reread_id(dev, 0);
	if (rc) {
		ata_dev_printk(dev, KERN_ERR, "failed to re-read IDENTIFY "
			       "data after HPA resizing\n");
		return rc;
	}

	if (print_info) {
		u64 new_sectors = ata_id_n_sectors(dev->id);
		ata_dev_printk(dev, KERN_INFO,
			"HPA unlocked: %llu -> %llu, native %llu\n",
			(unsigned long long)sectors,
			(unsigned long long)new_sectors,
			(unsigned long long)native_sectors);
	}

	return 0;
}