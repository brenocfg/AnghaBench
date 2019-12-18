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
struct hpsb_protocol_driver {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodemgr_remove_drv_files (struct hpsb_protocol_driver*) ; 

void hpsb_unregister_protocol(struct hpsb_protocol_driver *driver)
{
	nodemgr_remove_drv_files(driver);
	/* This will subsequently disconnect all devices that our driver
	 * is attached to. */
	driver_unregister(&driver->driver);
}