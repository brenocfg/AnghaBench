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
struct device_driver {int dummy; } ;
struct hpsb_protocol_driver {struct device_driver driver; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_remove_file (struct device_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fw_drv_attrs ; 

__attribute__((used)) static void nodemgr_remove_drv_files(struct hpsb_protocol_driver *driver)
{
	struct device_driver *drv = &driver->driver;
	int i;

	for (i = 0; i < ARRAY_SIZE(fw_drv_attrs); i++)
		driver_remove_file(drv, fw_drv_attrs[i]);
}