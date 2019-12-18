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
struct vme_bridge {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int VME_SLOTS_MAX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct vme_bridge* dev_to_bridge (struct device*) ; 

int vme_calc_slot(struct device *dev)
{
	struct vme_bridge *bridge;
	int num;

	bridge = dev_to_bridge(dev);

	/* Determine slot number */
	num = 0;
	while(num < VME_SLOTS_MAX) {
		if(&(bridge->dev[num]) == dev) {
			break;
		}
		num++;
	}
	if (num == VME_SLOTS_MAX) {
		dev_err(dev, "Failed to identify slot\n");
		num = 0;
		goto err_dev;
	}
	num++;

err_dev:
	return num;
}