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
struct qlcnic_adapter {TYPE_2__* ahw; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int capabilities; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int QLCNIC_FW_CAPABILITY_BDG ; 
 int /*<<< orphan*/  dev_attr_bridged_mode ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 

void qlcnic_remove_sysfs_entries(struct qlcnic_adapter *adapter)
{
	struct device *dev = &adapter->pdev->dev;

	if (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_BDG)
		device_remove_file(dev, &dev_attr_bridged_mode);
}