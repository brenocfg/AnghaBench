#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  qeth_device_attr_group ; 
 int /*<<< orphan*/  qeth_device_blkt_group ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int qeth_core_create_device_attributes(struct device *dev)
{
	int ret;
	ret = sysfs_create_group(&dev->kobj, &qeth_device_attr_group);
	if (ret)
		return ret;
	ret = sysfs_create_group(&dev->kobj, &qeth_device_blkt_group);
	if (ret)
		sysfs_remove_group(&dev->kobj, &qeth_device_attr_group);

	return 0;
}