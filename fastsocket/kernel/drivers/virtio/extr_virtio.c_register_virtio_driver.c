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
struct virtio_driver {TYPE_1__ driver; int /*<<< orphan*/  feature_table; scalar_t__ feature_table_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  virtio_bus ; 

int register_virtio_driver(struct virtio_driver *driver)
{
	/* Catch this early. */
	BUG_ON(driver->feature_table_size && !driver->feature_table);
	driver->driver.bus = &virtio_bus;
	return driver_register(&driver->driver);
}