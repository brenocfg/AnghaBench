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
 int /*<<< orphan*/  device_for_each_child (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_host_dev ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void nodemgr_remove_host_dev(struct device *dev)
{
	device_for_each_child(dev, NULL, remove_host_dev);
	sysfs_remove_link(&dev->kobj, "irm_id");
	sysfs_remove_link(&dev->kobj, "busmgr_id");
	sysfs_remove_link(&dev->kobj, "host_id");
}