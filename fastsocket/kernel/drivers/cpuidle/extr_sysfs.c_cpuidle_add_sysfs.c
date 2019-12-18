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
struct sys_device {int id; int /*<<< orphan*/  kobj; } ;
struct cpuidle_device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  cpuidle_devices ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktype_cpuidle ; 
 struct cpuidle_device* per_cpu (int /*<<< orphan*/ ,int) ; 

int cpuidle_add_sysfs(struct sys_device *sysdev)
{
	int cpu = sysdev->id;
	struct cpuidle_device *dev;
	int error;

	dev = per_cpu(cpuidle_devices, cpu);
	error = kobject_init_and_add(&dev->kobj, &ktype_cpuidle, &sysdev->kobj,
				     "cpuidle");
	if (!error)
		kobject_uevent(&dev->kobj, KOBJ_ADD);
	return error;
}