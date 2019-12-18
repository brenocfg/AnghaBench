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
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_max_rss ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ device_create_file (struct device*,int /*<<< orphan*/ *) ; 

void qlcnic_sriov_vf_add_sysfs(struct qlcnic_adapter *adapter)
{
	struct device *dev = &adapter->pdev->dev;

	if (device_create_file(dev, &dev_attr_max_rss))
		dev_info(dev, "failed to create rss sysfs entry\n");
}