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
struct cpuidle_device {int enabled; int state_count; scalar_t__ registered; int /*<<< orphan*/ * last_state; scalar_t__ last_residency; TYPE_1__* states; } ;
struct TYPE_4__ {int (* enable ) (struct cpuidle_device*) ;} ;
struct TYPE_3__ {scalar_t__ time; scalar_t__ usage; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int __cpuidle_register_device (struct cpuidle_device*) ; 
 int cpuidle_add_state_sysfs (struct cpuidle_device*) ; 
 TYPE_2__* cpuidle_curr_governor ; 
 int /*<<< orphan*/  cpuidle_get_driver () ; 
 int /*<<< orphan*/  cpuidle_remove_state_sysfs (struct cpuidle_device*) ; 
 int /*<<< orphan*/  enabled_devices ; 
 int /*<<< orphan*/  poll_idle_init (struct cpuidle_device*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int stub1 (struct cpuidle_device*) ; 

int cpuidle_enable_device(struct cpuidle_device *dev)
{
	int ret, i;

	if (dev->enabled)
		return 0;
	if (!cpuidle_get_driver() || !cpuidle_curr_governor)
		return -EIO;
	if (!dev->state_count)
		return -EINVAL;

	if (dev->registered == 0) {
		ret = __cpuidle_register_device(dev);
		if (ret)
			return ret;
	}

	poll_idle_init(dev);

	if ((ret = cpuidle_add_state_sysfs(dev)))
		return ret;

	if (cpuidle_curr_governor->enable &&
	    (ret = cpuidle_curr_governor->enable(dev)))
		goto fail_sysfs;

	for (i = 0; i < dev->state_count; i++) {
		dev->states[i].usage = 0;
		dev->states[i].time = 0;
	}
	dev->last_residency = 0;
	dev->last_state = NULL;

	smp_wmb();

	dev->enabled = 1;

	enabled_devices++;
	return 0;

fail_sysfs:
	cpuidle_remove_state_sysfs(dev);

	return ret;
}