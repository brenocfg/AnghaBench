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
struct device {int dummy; } ;

/* Variables and functions */
 int applesmc_device_init () ; 
 int applesmc_pm_resume (struct device*) ; 

__attribute__((used)) static int applesmc_pm_restore(struct device *dev)
{
	int ret = applesmc_device_init();
	if (ret)
		return ret;
	return applesmc_pm_resume(dev);
}