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
 int /*<<< orphan*/  qlcnic_remove_diag_entries (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void qlcnic_83xx_remove_sysfs(struct qlcnic_adapter *adapter)
{
	struct device *dev = &adapter->pdev->dev;

	qlcnic_remove_diag_entries(adapter);
	sysfs_remove_bin_file(&dev->kobj, &bin_attr_flash);
}