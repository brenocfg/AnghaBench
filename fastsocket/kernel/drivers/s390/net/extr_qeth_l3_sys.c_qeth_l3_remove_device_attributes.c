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
 int /*<<< orphan*/  qeth_device_ipato_group ; 
 int /*<<< orphan*/  qeth_device_rxip_group ; 
 int /*<<< orphan*/  qeth_device_vipa_group ; 
 int /*<<< orphan*/  qeth_l3_device_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void qeth_l3_remove_device_attributes(struct device *dev)
{
	sysfs_remove_group(&dev->kobj, &qeth_l3_device_attr_group);
	sysfs_remove_group(&dev->kobj, &qeth_device_ipato_group);
	sysfs_remove_group(&dev->kobj, &qeth_device_vipa_group);
	sysfs_remove_group(&dev->kobj, &qeth_device_rxip_group);
}