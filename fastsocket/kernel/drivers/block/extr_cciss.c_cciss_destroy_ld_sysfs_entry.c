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
struct device {int dummy; } ;
struct ctlr_info {TYPE_1__** drv; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static void cciss_destroy_ld_sysfs_entry(struct ctlr_info *h, int drv_index,
	int ctlr_exiting)
{
	struct device *dev = &h->drv[drv_index]->dev;

	/* special case for c*d0, we only destroy it on controller exit */
	if (drv_index == 0 && !ctlr_exiting)
		return;

	device_del(dev);
	put_device(dev); /* the "final" put. */
	h->drv[drv_index] = NULL;
}