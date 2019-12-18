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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 

void omap_pm_set_max_dev_wakeup_lat(struct device *dev, long t)
{
	if (!dev || t < -1) {
		WARN_ON(1);
		return;
	};

	if (t == -1)
		pr_debug("OMAP PM: remove max device latency constraint: "
			 "dev %s\n", dev_name(dev));
	else
		pr_debug("OMAP PM: add max device latency constraint: "
			 "dev %s, t = %ld usec\n", dev_name(dev), t);

	/*
	 * For current Linux, this needs to map the device to a
	 * powerdomain, then go through the list of current max lat
	 * constraints on that powerdomain and find the smallest.  If
	 * the latency constraint has changed, the code should
	 * recompute the state to enter for the next powerdomain
	 * state.  Conceivably, this code should also determine
	 * whether to actually disable the device clocks or not,
	 * depending on how long it takes to re-enable the clocks.
	 *
	 * TI CDP code can call constraint_set here.
	 */
}