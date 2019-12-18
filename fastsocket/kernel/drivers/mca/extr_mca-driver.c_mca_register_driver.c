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
struct TYPE_2__ {int /*<<< orphan*/ * bus; } ;
struct mca_driver {scalar_t__ integrated_id; TYPE_1__ driver; } ;

/* Variables and functions */
 scalar_t__ MCA_bus ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mca_bus_type ; 

int mca_register_driver(struct mca_driver *mca_drv)
{
	int r;

	if (MCA_bus) {
		mca_drv->driver.bus = &mca_bus_type;
		if ((r = driver_register(&mca_drv->driver)) < 0)
			return r;
		mca_drv->integrated_id = 0;
	}

	return 0;
}