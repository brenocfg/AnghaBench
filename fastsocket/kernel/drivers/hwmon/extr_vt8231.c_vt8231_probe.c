#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vt8231_data {char* name; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  uch_config; int /*<<< orphan*/  update_lock; scalar_t__ addr; } ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ ISTEMP (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ISVOLT (int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT8231_EXTENT ; 
 int /*<<< orphan*/  VT8231_REG_UCH_CONFIG ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct vt8231_data*) ; 
 struct vt8231_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vt8231_data*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ vt8231_driver ; 
 int /*<<< orphan*/  vt8231_group ; 
 int /*<<< orphan*/ * vt8231_group_temps ; 
 int /*<<< orphan*/ * vt8231_group_volts ; 
 int /*<<< orphan*/  vt8231_init_device (struct vt8231_data*) ; 
 int /*<<< orphan*/  vt8231_read_value (struct vt8231_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vt8231_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct vt8231_data *data;
	int err = 0, i;

	/* Reserve the ISA region */
	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!request_region(res->start, VT8231_EXTENT,
			    vt8231_driver.driver.name)) {
		dev_err(&pdev->dev, "Region 0x%lx-0x%lx already in use!\n",
			(unsigned long)res->start, (unsigned long)res->end);
		return -ENODEV;
	}

	if (!(data = kzalloc(sizeof(struct vt8231_data), GFP_KERNEL))) {
		err = -ENOMEM;
		goto exit_release;
	}

	platform_set_drvdata(pdev, data);
	data->addr = res->start;
	data->name = "vt8231";

	mutex_init(&data->update_lock);
	vt8231_init_device(data);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&pdev->dev.kobj, &vt8231_group)))
		goto exit_free;

	/* Must update device information to find out the config field */
	data->uch_config = vt8231_read_value(data, VT8231_REG_UCH_CONFIG);

	for (i = 0; i < ARRAY_SIZE(vt8231_group_temps); i++) {
		if (ISTEMP(i, data->uch_config)) {
			if ((err = sysfs_create_group(&pdev->dev.kobj,
					&vt8231_group_temps[i])))
				goto exit_remove_files;
		}
	}

	for (i = 0; i < ARRAY_SIZE(vt8231_group_volts); i++) {
		if (ISVOLT(i, data->uch_config)) {
			if ((err = sysfs_create_group(&pdev->dev.kobj,
					&vt8231_group_volts[i])))
				goto exit_remove_files;
		}
	}

	data->hwmon_dev = hwmon_device_register(&pdev->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_files;
	}
	return 0;

exit_remove_files:
	for (i = 0; i < ARRAY_SIZE(vt8231_group_volts); i++)
		sysfs_remove_group(&pdev->dev.kobj, &vt8231_group_volts[i]);

	for (i = 0; i < ARRAY_SIZE(vt8231_group_temps); i++)
		sysfs_remove_group(&pdev->dev.kobj, &vt8231_group_temps[i]);

	sysfs_remove_group(&pdev->dev.kobj, &vt8231_group);

exit_free:
	platform_set_drvdata(pdev, NULL);
	kfree(data);

exit_release:
	release_region(res->start, VT8231_EXTENT);
	return err;
}