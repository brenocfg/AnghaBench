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
struct dasd_device {int stopped; int /*<<< orphan*/  flags; scalar_t__ block; TYPE_1__* discipline; } ;
struct ccw_device {int dummy; } ;
struct TYPE_2__ {int (* restore ) (struct dasd_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FLAG_SUSPENDED ; 
 int DASD_STOPPED_PM ; 
 int DASD_UNRESUMED_PM ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int PTR_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dasd_device* dasd_device_from_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_device_remove_stop_bits (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_schedule_block_bh (scalar_t__) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int stub1 (struct dasd_device*) ; 

int dasd_generic_restore_device(struct ccw_device *cdev)
{
	struct dasd_device *device = dasd_device_from_cdev(cdev);
	int rc = 0;

	if (IS_ERR(device))
		return PTR_ERR(device);

	/* allow new IO again */
	dasd_device_remove_stop_bits(device,
				     (DASD_STOPPED_PM | DASD_UNRESUMED_PM));

	dasd_schedule_device_bh(device);

	/*
	 * call discipline restore function
	 * if device is stopped do nothing e.g. for disconnected devices
	 */
	if (device->discipline->restore && !(device->stopped))
		rc = device->discipline->restore(device);
	if (rc || device->stopped)
		/*
		 * if the resume failed for the DASD we put it in
		 * an UNRESUMED stop state
		 */
		device->stopped |= DASD_UNRESUMED_PM;

	if (device->block)
		dasd_schedule_block_bh(device->block);

	clear_bit(DASD_FLAG_SUSPENDED, &device->flags);
	dasd_put_device(device);
	return 0;
}