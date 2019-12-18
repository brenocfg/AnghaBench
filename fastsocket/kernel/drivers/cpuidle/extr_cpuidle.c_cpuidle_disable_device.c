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
struct cpuidle_device {scalar_t__ enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct cpuidle_device*) ;} ;

/* Variables and functions */
 TYPE_1__* cpuidle_curr_governor ; 
 int /*<<< orphan*/  cpuidle_get_driver () ; 
 int /*<<< orphan*/  cpuidle_remove_state_sysfs (struct cpuidle_device*) ; 
 int /*<<< orphan*/  enabled_devices ; 
 int /*<<< orphan*/  stub1 (struct cpuidle_device*) ; 

void cpuidle_disable_device(struct cpuidle_device *dev)
{
	if (!dev->enabled)
		return;
	if (!cpuidle_get_driver() || !cpuidle_curr_governor)
		return;

	dev->enabled = 0;

	if (cpuidle_curr_governor->disable)
		cpuidle_curr_governor->disable(dev);

	cpuidle_remove_state_sysfs(dev);
	enabled_devices--;
}