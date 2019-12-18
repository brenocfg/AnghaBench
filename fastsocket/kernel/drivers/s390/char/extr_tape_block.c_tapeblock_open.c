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
struct tape_device {TYPE_1__* cdev; scalar_t__ required_tapemarks; } ;
struct gendisk {int /*<<< orphan*/  private_data; } ;
struct block_device {struct gendisk* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 
 int EPERM ; 
 int /*<<< orphan*/  TS_BLKUSE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 struct tape_device* tape_get_device_reference (int /*<<< orphan*/ ) ; 
 int tape_open (struct tape_device*) ; 
 int /*<<< orphan*/  tape_put_device (struct tape_device*) ; 
 int /*<<< orphan*/  tape_release (struct tape_device*) ; 
 int /*<<< orphan*/  tape_state_set (struct tape_device*,int /*<<< orphan*/ ) ; 
 int tapeblock_revalidate_disk (struct gendisk*) ; 

__attribute__((used)) static int
tapeblock_open(struct block_device *bdev, fmode_t mode)
{
	struct gendisk *	disk = bdev->bd_disk;
	struct tape_device *	device;
	int			rc;

	device = tape_get_device_reference(disk->private_data);

	if (device->required_tapemarks) {
		DBF_EVENT(2, "TBLOCK: missing tapemarks\n");
		pr_warning("%s: Opening the tape failed because of missing "
			   "end-of-file marks\n", dev_name(&device->cdev->dev));
		rc = -EPERM;
		goto put_device;
	}

	rc = tape_open(device);
	if (rc)
		goto put_device;

	rc = tapeblock_revalidate_disk(disk);
	if (rc)
		goto release;

	/*
	 * Note: The reference to <device> is hold until the release function
	 *       is called.
	 */
	tape_state_set(device, TS_BLKUSE);
	return 0;

release:
	tape_release(device);
 put_device:
	tape_put_device(device);
	return rc;
}