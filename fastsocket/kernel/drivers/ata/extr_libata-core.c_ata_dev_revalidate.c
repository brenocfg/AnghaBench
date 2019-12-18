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
typedef  scalar_t__ u64 ;
struct ata_device {scalar_t__ n_sectors; scalar_t__ n_native_sectors; unsigned int class; } ;

/* Variables and functions */
 unsigned int ATA_DEV_ATA ; 
 unsigned int ATA_DEV_ATAPI ; 
 unsigned int ATA_DEV_SEMB ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ ata_class_enabled (unsigned int) ; 
 int ata_dev_configure (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_enabled (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,...) ; 
 int ata_dev_reread_id (struct ata_device*,unsigned int) ; 

int ata_dev_revalidate(struct ata_device *dev, unsigned int new_class,
		       unsigned int readid_flags)
{
	u64 n_sectors = dev->n_sectors;
	u64 n_native_sectors = dev->n_native_sectors;
	int rc;

	if (!ata_dev_enabled(dev))
		return -ENODEV;

	/* fail early if !ATA && !ATAPI to avoid issuing [P]IDENTIFY to PMP */
	if (ata_class_enabled(new_class) &&
	    new_class != ATA_DEV_ATA &&
	    new_class != ATA_DEV_ATAPI &&
	    new_class != ATA_DEV_SEMB) {
		ata_dev_printk(dev, KERN_INFO, "class mismatch %u != %u\n",
			       dev->class, new_class);
		rc = -ENODEV;
		goto fail;
	}

	/* re-read ID */
	rc = ata_dev_reread_id(dev, readid_flags);
	if (rc)
		goto fail;

	/* configure device according to the new ID */
	rc = ata_dev_configure(dev);
	if (rc)
		goto fail;

	/* verify n_sectors hasn't changed */
	if (dev->class == ATA_DEV_ATA && n_sectors &&
	    dev->n_sectors != n_sectors) {
		ata_dev_printk(dev, KERN_WARNING, "n_sectors mismatch "
			       "%llu != %llu\n",
			       (unsigned long long)n_sectors,
			       (unsigned long long)dev->n_sectors);
		/*
		 * Something could have caused HPA to be unlocked
		 * involuntarily.  If n_native_sectors hasn't changed
		 * and the new size matches it, keep the device.
		 */
		if (dev->n_native_sectors == n_native_sectors &&
		    dev->n_sectors > n_sectors &&
		    dev->n_sectors == n_native_sectors) {
			ata_dev_printk(dev, KERN_WARNING,
				       "new n_sectors matches native, probably "
				       "late HPA unlock, continuing\n");
			/* keep using the old n_sectors */
			dev->n_sectors = n_sectors;
		} else {
			/* restore original n_[native]_sectors and fail */
			dev->n_native_sectors = n_native_sectors;
			dev->n_sectors = n_sectors;
			rc = -ENODEV;
			goto fail;
		}
	}

	return 0;

 fail:
	ata_dev_printk(dev, KERN_ERR, "revalidation failed (errno=%d)\n", rc);
	return rc;
}