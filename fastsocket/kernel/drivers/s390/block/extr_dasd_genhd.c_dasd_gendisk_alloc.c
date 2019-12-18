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
struct gendisk {int first_minor; int /*<<< orphan*/  queue; scalar_t__ disk_name; int /*<<< orphan*/ * driverfs_dev; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;
struct dasd_device {int devindex; int features; int /*<<< orphan*/  flags; TYPE_1__* cdev; } ;
struct dasd_block {struct gendisk* gdp; int /*<<< orphan*/  request_queue; struct dasd_device* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DASD_FEATURE_READONLY ; 
 int /*<<< orphan*/  DASD_FLAG_DEVICE_RO ; 
 int /*<<< orphan*/  DASD_MAJOR ; 
 int DASD_PARTN_BITS ; 
 int DASD_PER_MAJOR ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  add_disk (struct gendisk*) ; 
 struct gendisk* alloc_disk (int) ; 
 int /*<<< orphan*/  dasd_add_link_to_gendisk (struct gendisk*,struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_device_operations ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_disk_ro (struct gendisk*,int) ; 
 int sprintf (scalar_t__,char*,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dasd_gendisk_alloc(struct dasd_block *block)
{
	struct gendisk *gdp;
	struct dasd_device *base;
	int len;

	/* Make sure the minor for this device exists. */
	base = block->base;
	if (base->devindex >= DASD_PER_MAJOR)
		return -EBUSY;

	gdp = alloc_disk(1 << DASD_PARTN_BITS);
	if (!gdp)
		return -ENOMEM;

	/* Initialize gendisk structure. */
	gdp->major = DASD_MAJOR;
	gdp->first_minor = base->devindex << DASD_PARTN_BITS;
	gdp->fops = &dasd_device_operations;
	gdp->driverfs_dev = &base->cdev->dev;

	/*
	 * Set device name.
	 *   dasda - dasdz : 26 devices
	 *   dasdaa - dasdzz : 676 devices, added up = 702
	 *   dasdaaa - dasdzzz : 17576 devices, added up = 18278
	 *   dasdaaaa - dasdzzzz : 456976 devices, added up = 475252
	 */
	len = sprintf(gdp->disk_name, "dasd");
	if (base->devindex > 25) {
		if (base->devindex > 701) {
			if (base->devindex > 18277)
			        len += sprintf(gdp->disk_name + len, "%c",
					       'a'+(((base->devindex-18278)
						     /17576)%26));
			len += sprintf(gdp->disk_name + len, "%c",
				       'a'+(((base->devindex-702)/676)%26));
		}
		len += sprintf(gdp->disk_name + len, "%c",
			       'a'+(((base->devindex-26)/26)%26));
	}
	len += sprintf(gdp->disk_name + len, "%c", 'a'+(base->devindex%26));

	if (base->features & DASD_FEATURE_READONLY ||
	    test_bit(DASD_FLAG_DEVICE_RO, &base->flags))
		set_disk_ro(gdp, 1);
	dasd_add_link_to_gendisk(gdp, base);
	gdp->queue = block->request_queue;
	block->gdp = gdp;
	set_capacity(block->gdp, 0);
	add_disk(block->gdp);
	return 0;
}