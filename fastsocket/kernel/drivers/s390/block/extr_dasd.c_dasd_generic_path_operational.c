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
struct dasd_device {int stopped; scalar_t__ block; TYPE_1__* cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DASD_STOPPED_DC_WAIT ; 
 int DASD_UNRESUMED_PM ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int /*<<< orphan*/  dasd_device_remove_stop_bits (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dasd_restore_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_schedule_block_bh (scalar_t__) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

int dasd_generic_path_operational(struct dasd_device *device)
{
	dev_info(&device->cdev->dev, "A channel path to the device has become "
		 "operational\n");
	DBF_DEV_EVENT(DBF_WARNING, device, "%s", "path operational");
	dasd_device_remove_stop_bits(device, DASD_STOPPED_DC_WAIT);
	if (device->stopped & DASD_UNRESUMED_PM) {
		dasd_device_remove_stop_bits(device, DASD_UNRESUMED_PM);
		dasd_restore_device(device);
		return 1;
	}
	dasd_schedule_device_bh(device);
	if (device->block)
		dasd_schedule_block_bh(device->block);
	return 1;
}