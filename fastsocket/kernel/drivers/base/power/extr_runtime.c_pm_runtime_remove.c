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
struct TYPE_2__ {scalar_t__ runtime_status; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 scalar_t__ RPM_ACTIVE ; 
 int /*<<< orphan*/  __pm_runtime_disable (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 

void pm_runtime_remove(struct device *dev)
{
	__pm_runtime_disable(dev, false);

	/* Change the status back to 'suspended' to match the initial status. */
	if (dev->power.runtime_status == RPM_ACTIVE)
		pm_runtime_set_suspended(dev);
}