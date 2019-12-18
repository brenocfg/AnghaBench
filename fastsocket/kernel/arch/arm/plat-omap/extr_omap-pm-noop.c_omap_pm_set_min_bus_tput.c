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
typedef  scalar_t__ u8 ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ OCP_INITIATOR_AGENT ; 
 scalar_t__ OCP_TARGET_AGENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 

void omap_pm_set_min_bus_tput(struct device *dev, u8 agent_id, unsigned long r)
{
	if (!dev || (agent_id != OCP_INITIATOR_AGENT &&
	    agent_id != OCP_TARGET_AGENT)) {
		WARN_ON(1);
		return;
	};

	if (r == 0)
		pr_debug("OMAP PM: remove min bus tput constraint: "
			 "dev %s for agent_id %d\n", dev_name(dev), agent_id);
	else
		pr_debug("OMAP PM: add min bus tput constraint: "
			 "dev %s for agent_id %d: rate %ld KiB\n",
			 dev_name(dev), agent_id, r);

	/*
	 * This code should model the interconnect and compute the
	 * required clock frequency, convert that to a VDD2 OPP ID, then
	 * set the VDD2 OPP appropriately.
	 *
	 * TI CDP code can call constraint_set here on the VDD2 OPP.
	 */
}