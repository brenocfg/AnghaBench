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
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct w1_slave {TYPE_2__ dev; } ;
struct TYPE_3__ {TYPE_2__* parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct platform_device*) ; 
 int new_bat_id () ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  release_bat_id (int) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w1_ds2760_bin_attr ; 

__attribute__((used)) static int w1_ds2760_add_slave(struct w1_slave *sl)
{
	int ret;
	int id;
	struct platform_device *pdev;

	id = new_bat_id();
	if (id < 0) {
		ret = id;
		goto noid;
	}

	pdev = platform_device_alloc("ds2760-battery", id);
	if (!pdev) {
		ret = -ENOMEM;
		goto pdev_alloc_failed;
	}
	pdev->dev.parent = &sl->dev;

	ret = platform_device_add(pdev);
	if (ret)
		goto pdev_add_failed;

	ret = sysfs_create_bin_file(&sl->dev.kobj, &w1_ds2760_bin_attr);
	if (ret)
		goto bin_attr_failed;

	dev_set_drvdata(&sl->dev, pdev);

	goto success;

bin_attr_failed:
pdev_add_failed:
	platform_device_unregister(pdev);
pdev_alloc_failed:
	release_bat_id(id);
noid:
success:
	return ret;
}