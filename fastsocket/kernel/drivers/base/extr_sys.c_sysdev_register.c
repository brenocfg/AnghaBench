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
struct sysdev_class {TYPE_1__ kset; } ;
struct sys_device {struct sysdev_class* cls; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int sysdev_add (struct sys_device*) ; 
 scalar_t__ sysdev_initialize (struct sys_device*) ; 

int sysdev_register(struct sys_device *sysdev)
{
	struct sysdev_class *cls = sysdev->cls;

	if (sysdev_initialize(sysdev))
		return -EINVAL;

	pr_debug("Registering sys device of class '%s'\n",
		 kobject_name(&cls->kset.kobj));

	return sysdev_add(sysdev);
}