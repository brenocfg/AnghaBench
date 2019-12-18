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
struct sys_device {int id; } ;
struct cpuidle_device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuidle_devices ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct cpuidle_device* per_cpu (int /*<<< orphan*/ ,int) ; 

void cpuidle_remove_sysfs(struct sys_device *sysdev)
{
	int cpu = sysdev->id;
	struct cpuidle_device *dev;

	dev = per_cpu(cpuidle_devices, cpu);
	kobject_put(&dev->kobj);
}