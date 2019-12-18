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
struct device {TYPE_1__* driver; } ;
struct dev_pm_ops {int (* resume ) (struct device*) ;} ;
struct TYPE_2__ {struct dev_pm_ops* pm; } ;

/* Variables and functions */
 int stub1 (struct device*) ; 

__attribute__((used)) static int vio_pm_resume(struct device *dev)
{
	const struct dev_pm_ops *pm = dev->driver ? dev->driver->pm : NULL;

	if (pm && pm->resume)
		return pm->resume(dev);
	return 0;
}