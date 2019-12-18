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
struct vme_bridge {int /*<<< orphan*/  num; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int VME_SLOTS_MAX ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  vme_free_bus_num (int /*<<< orphan*/ ) ; 

void vme_unregister_bridge (struct vme_bridge *bridge)
{
	int i;
	struct device *dev;


	for (i = 0; i < VME_SLOTS_MAX; i++) {
		dev = &(bridge->dev[i]);
		device_unregister(dev);
	}
	vme_free_bus_num(bridge->num);
}