#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct sysdev_class {TYPE_1__ kset; } ;
struct TYPE_5__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 TYPE_2__ cpuclass_attr_group ; 
 int /*<<< orphan*/  cpuclass_switch_attrs ; 
 int sysfs_create_group (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ sysfs_switch ; 

int cpuidle_add_class_sysfs(struct sysdev_class *cls)
{
	if (sysfs_switch)
		cpuclass_attr_group.attrs = cpuclass_switch_attrs;

	return sysfs_create_group(&cls->kset.kobj, &cpuclass_attr_group);
}