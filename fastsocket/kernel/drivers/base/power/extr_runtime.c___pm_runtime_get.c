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
struct TYPE_2__ {int /*<<< orphan*/  usage_count; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int pm_request_resume (struct device*) ; 
 int pm_runtime_resume (struct device*) ; 

int __pm_runtime_get(struct device *dev, bool sync)
{
	int retval = 1;

	if (atomic_add_return(1, &dev->power.usage_count) == 1)
		retval = sync ? pm_runtime_resume(dev) : pm_request_resume(dev);

	return retval;
}