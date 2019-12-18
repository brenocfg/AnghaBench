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
struct kobject {int dummy; } ;
struct cpuidle_device {int /*<<< orphan*/  kobj_unregister; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct cpuidle_device* kobj_to_cpuidledev (struct kobject*) ; 

__attribute__((used)) static void cpuidle_sysfs_release(struct kobject *kobj)
{
	struct cpuidle_device *dev = kobj_to_cpuidledev(kobj);

	complete(&dev->kobj_unregister);
}