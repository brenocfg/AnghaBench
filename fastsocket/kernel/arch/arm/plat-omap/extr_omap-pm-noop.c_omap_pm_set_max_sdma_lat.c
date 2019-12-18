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

void omap_pm_set_max_sdma_lat(struct device *dev, long t)
{
	if (!dev || t < -1) {
		WARN_ON(1);
		return;
	};

	if (t == -1)
		pr_debug("OMAP PM: remove max DMA latency constraint: "
			 "dev %s\n", dev_name(dev));
	else
		pr_debug("OMAP PM: add max DMA latency constraint: "
			 "dev %s, t = %ld usec\n", dev_name(dev), t);

	/*
	 * For current Linux PM QOS params, this code should scan the
	 * list of maximum CPU and DMA latencies and select the
	 * smallest, then set cpu_dma_latency pm_qos_param
	 * accordingly.
	 *
	 * For future Linux PM QOS params, with separate CPU and DMA
	 * latency params, this code should just set the dma_latency param.
	 *
	 * TI CDP code can call constraint_set here.
	 */

}