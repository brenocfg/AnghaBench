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
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int __cpuidle_register_device (struct cpuidle_device*) ; 
 int /*<<< orphan*/  cpuidle_enable_device (struct cpuidle_device*) ; 
 int /*<<< orphan*/  cpuidle_install_idle_handler () ; 
 int /*<<< orphan*/  cpuidle_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cpuidle_register_device(struct cpuidle_device *dev)
{
	int ret;

	mutex_lock(&cpuidle_lock);

	if ((ret = __cpuidle_register_device(dev))) {
		mutex_unlock(&cpuidle_lock);
		return ret;
	}

	cpuidle_enable_device(dev);
	cpuidle_install_idle_handler();

	mutex_unlock(&cpuidle_lock);

	return 0;

}