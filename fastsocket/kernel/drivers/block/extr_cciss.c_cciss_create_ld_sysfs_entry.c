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
struct device {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * type; } ;
struct ctlr_info {TYPE_1__** drv; int /*<<< orphan*/  dev; int /*<<< orphan*/  ctlr; } ;
struct TYPE_2__ {int device_initialized; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cciss_bus_type ; 
 int /*<<< orphan*/  cciss_dev_type ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 long device_add (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 

__attribute__((used)) static long cciss_create_ld_sysfs_entry(struct ctlr_info *h,
				       int drv_index)
{
	struct device *dev;

	if (h->drv[drv_index]->device_initialized)
		return 0;

	dev = &h->drv[drv_index]->dev;
	device_initialize(dev);
	dev->type = &cciss_dev_type;
	dev->bus = &cciss_bus_type;
	dev_set_name(dev, "c%dd%d", h->ctlr, drv_index);
	dev->parent = &h->dev;
	h->drv[drv_index]->device_initialized = 1;
	return device_add(dev);
}