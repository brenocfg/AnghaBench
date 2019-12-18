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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct w1_slave {TYPE_1__ dev; } ;
struct platform_device {int id; } ;

/* Variables and functions */
 struct platform_device* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  release_bat_id (int) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w1_ds2760_bin_attr ; 

__attribute__((used)) static void w1_ds2760_remove_slave(struct w1_slave *sl)
{
	struct platform_device *pdev = dev_get_drvdata(&sl->dev);
	int id = pdev->id;

	platform_device_unregister(pdev);
	release_bat_id(id);
	sysfs_remove_bin_file(&sl->dev.kobj, &w1_ds2760_bin_attr);
}