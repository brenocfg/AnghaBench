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
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_attr_flash ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  qlcnic_create_diag_entries (struct qlcnic_adapter*) ; 
 scalar_t__ sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void qlcnic_83xx_add_sysfs(struct qlcnic_adapter *adapter)
{
	struct device *dev = &adapter->pdev->dev;

	qlcnic_create_diag_entries(adapter);

	if (sysfs_create_bin_file(&dev->kobj, &bin_attr_flash))
		dev_info(dev, "failed to create flash sysfs entry\n");
}