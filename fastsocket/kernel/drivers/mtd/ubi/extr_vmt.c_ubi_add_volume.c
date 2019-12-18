#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  owner; } ;
struct TYPE_8__ {int /*<<< orphan*/  class; int /*<<< orphan*/  devt; int /*<<< orphan*/ * parent; int /*<<< orphan*/  release; } ;
struct ubi_volume {int vol_id; TYPE_4__ cdev; TYPE_2__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct ubi_device {int /*<<< orphan*/  ubi_name; int /*<<< orphan*/  dev; TYPE_1__ cdev; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_4__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_err (char*,int) ; 
 int /*<<< orphan*/  dbg_gen (char*,int) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int) ; 
 int device_register (TYPE_2__*) ; 
 scalar_t__ paranoid_check_volumes (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_class ; 
 int /*<<< orphan*/  ubi_err (char*,int,int) ; 
 int /*<<< orphan*/  ubi_vol_cdev_operations ; 
 int /*<<< orphan*/  vol_release ; 
 int /*<<< orphan*/  volume_sysfs_close (struct ubi_volume*) ; 
 int volume_sysfs_init (struct ubi_device*,struct ubi_volume*) ; 

int ubi_add_volume(struct ubi_device *ubi, struct ubi_volume *vol)
{
	int err, vol_id = vol->vol_id;
	dev_t dev;

	dbg_gen("add volume %d", vol_id);

	/* Register character device for the volume */
	cdev_init(&vol->cdev, &ubi_vol_cdev_operations);
	vol->cdev.owner = THIS_MODULE;
	dev = MKDEV(MAJOR(ubi->cdev.dev), vol->vol_id + 1);
	err = cdev_add(&vol->cdev, dev, 1);
	if (err) {
		ubi_err("cannot add character device for volume %d, error %d",
			vol_id, err);
		return err;
	}

	vol->dev.release = vol_release;
	vol->dev.parent = &ubi->dev;
	vol->dev.devt = dev;
	vol->dev.class = ubi_class;
	dev_set_name(&vol->dev, "%s_%d", ubi->ubi_name, vol->vol_id);
	err = device_register(&vol->dev);
	if (err)
		goto out_cdev;

	err = volume_sysfs_init(ubi, vol);
	if (err) {
		cdev_del(&vol->cdev);
		volume_sysfs_close(vol);
		return err;
	}

	if (paranoid_check_volumes(ubi))
		dbg_err("check failed while adding volume %d", vol_id);
	return err;

out_cdev:
	cdev_del(&vol->cdev);
	return err;
}