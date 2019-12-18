#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gendisk {int flags; TYPE_3__* queue; scalar_t__ minors; scalar_t__ first_minor; scalar_t__ major; int /*<<< orphan*/  part0; } ;
struct backing_dev_info {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_6__ {struct backing_dev_info backing_dev_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  devt; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int GENHD_FL_EXT_DEVT ; 
 int GENHD_FL_UP ; 
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdi_register_dev (struct backing_dev_info*,int /*<<< orphan*/ ) ; 
 int blk_alloc_devt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_get_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  blk_register_queue (struct gendisk*) ; 
 int /*<<< orphan*/  blk_register_region (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gendisk*) ; 
 int /*<<< orphan*/  disk_devt (struct gendisk*) ; 
 TYPE_2__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  exact_lock ; 
 int /*<<< orphan*/  exact_match ; 
 int /*<<< orphan*/  register_disk (struct gendisk*) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void add_disk(struct gendisk *disk)
{
	struct backing_dev_info *bdi;
	dev_t devt;
	int retval;

	/* minors == 0 indicates to use ext devt from part0 and should
	 * be accompanied with EXT_DEVT flag.  Make sure all
	 * parameters make sense.
	 */
	WARN_ON(disk->minors && !(disk->major || disk->first_minor));
	WARN_ON(!disk->minors && !(disk->flags & GENHD_FL_EXT_DEVT));

	disk->flags |= GENHD_FL_UP;

	retval = blk_alloc_devt(&disk->part0, &devt);
	if (retval) {
		WARN_ON(1);
		return;
	}
	disk_to_dev(disk)->devt = devt;

	/* ->major and ->first_minor aren't supposed to be
	 * dereferenced from here on, but set them just in case.
	 */
	disk->major = MAJOR(devt);
	disk->first_minor = MINOR(devt);

	/* Register BDI before referencing it from bdev */ 
	bdi = &disk->queue->backing_dev_info;
	bdi_register_dev(bdi, disk_devt(disk));

	blk_register_region(disk_devt(disk), disk->minors, NULL,
			    exact_match, exact_lock, disk);
	register_disk(disk);
	blk_register_queue(disk);

	/*
	 * Take an extra ref on queue which will be put on disk_release()
	 * so that it sticks around as long as @disk is there.
	 */
	WARN_ON_ONCE(blk_get_queue(disk->queue));

	retval = sysfs_create_link(&disk_to_dev(disk)->kobj, &bdi->dev->kobj,
				   "bdi");
	WARN_ON(retval);
}