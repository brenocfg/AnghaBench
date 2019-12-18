#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  owner; } ;
struct osd_uld_device {int minor; TYPE_1__ cdev; struct device* class_member; int /*<<< orphan*/  od; struct gendisk* disk; int /*<<< orphan*/  kref; } ;
struct gendisk {int first_minor; int /*<<< orphan*/  disk_name; int /*<<< orphan*/  major; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSD_ERR (char*) ; 
 int /*<<< orphan*/  OSD_INFO (char*,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  SCSI_OSD_MAJOR ; 
 int SCSI_OSD_MAX_MINOR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ TYPE_OSD ; 
 int __detect_osd (struct osd_uld_device*) ; 
 struct gendisk* alloc_disk (int) ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct osd_uld_device*) ; 
 struct device* device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ida_get_new (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ida_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct osd_uld_device*) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct osd_uld_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_dev_init (int /*<<< orphan*/ *,struct scsi_device*) ; 
 int /*<<< orphan*/  osd_fops ; 
 int /*<<< orphan*/  osd_minor_ida ; 
 int /*<<< orphan*/  osd_sysfs_class ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  scsi_device_get (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int osd_probe(struct device *dev)
{
	struct scsi_device *scsi_device = to_scsi_device(dev);
	struct gendisk *disk;
	struct osd_uld_device *oud;
	int minor;
	int error;

	if (scsi_device->type != TYPE_OSD)
		return -ENODEV;

	do {
		if (!ida_pre_get(&osd_minor_ida, GFP_KERNEL))
			return -ENODEV;

		error = ida_get_new(&osd_minor_ida, &minor);
	} while (error == -EAGAIN);

	if (error)
		return error;
	if (minor >= SCSI_OSD_MAX_MINOR) {
		error = -EBUSY;
		goto err_retract_minor;
	}

	error = -ENOMEM;
	oud = kzalloc(sizeof(*oud), GFP_KERNEL);
	if (NULL == oud)
		goto err_retract_minor;

	kref_init(&oud->kref);
	dev_set_drvdata(dev, oud);
	oud->minor = minor;

	/* allocate a disk and set it up */
	/* FIXME: do we need this since sg has already done that */
	disk = alloc_disk(1);
	if (!disk) {
		OSD_ERR("alloc_disk failed\n");
		goto err_free_osd;
	}
	disk->major = SCSI_OSD_MAJOR;
	disk->first_minor = oud->minor;
	sprintf(disk->disk_name, "osd%d", oud->minor);
	oud->disk = disk;

	/* hold one more reference to the scsi_device that will get released
	 * in __release, in case a logout is happening while fs is mounted
	 */
	scsi_device_get(scsi_device);
	osd_dev_init(&oud->od, scsi_device);

	/* Detect the OSD Version */
	error = __detect_osd(oud);
	if (error) {
		OSD_ERR("osd detection failed, non-compatible OSD device\n");
		goto err_put_disk;
	}

	/* init the char-device for communication with user-mode */
	cdev_init(&oud->cdev, &osd_fops);
	oud->cdev.owner = THIS_MODULE;
	error = cdev_add(&oud->cdev,
			 MKDEV(SCSI_OSD_MAJOR, oud->minor), 1);
	if (error) {
		OSD_ERR("cdev_add failed\n");
		goto err_put_disk;
	}
	kobject_get(&oud->cdev.kobj); /* 2nd ref see osd_remove() */

	/* class_member */
	oud->class_member = device_create(osd_sysfs_class, dev,
		MKDEV(SCSI_OSD_MAJOR, oud->minor), "%s", disk->disk_name);
	if (IS_ERR(oud->class_member)) {
		OSD_ERR("class_device_create failed\n");
		error = PTR_ERR(oud->class_member);
		goto err_put_cdev;
	}

	dev_set_drvdata(oud->class_member, oud);

	OSD_INFO("osd_probe %s\n", disk->disk_name);
	return 0;

err_put_cdev:
	cdev_del(&oud->cdev);
err_put_disk:
	scsi_device_put(scsi_device);
	put_disk(disk);
err_free_osd:
	dev_set_drvdata(dev, NULL);
	kfree(oud);
err_retract_minor:
	ida_remove(&osd_minor_ida, minor);
	return error;
}