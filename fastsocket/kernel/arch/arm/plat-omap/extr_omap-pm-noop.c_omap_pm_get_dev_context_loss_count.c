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
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

int omap_pm_get_dev_context_loss_count(struct device *dev)
{
	if (!dev) {
		WARN_ON(1);
		return -EINVAL;
	};

	pr_debug("OMAP PM: returning context loss count for dev %s\n",
		 dev_name(dev));

	/*
	 * Map the device to the powerdomain.  Return the powerdomain
	 * off counter.
	 */

	return 0;
}