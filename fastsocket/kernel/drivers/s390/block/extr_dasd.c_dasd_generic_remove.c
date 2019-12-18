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
struct dasd_device {struct dasd_block* block; int /*<<< orphan*/  flags; } ;
struct dasd_block {int dummy; } ;
struct ccw_device {int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FLAG_OFFLINE ; 
 int /*<<< orphan*/  DASD_FLAG_SAFE_OFFLINE_RUNNING ; 
 int /*<<< orphan*/  DASD_STATE_NEW ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_delete_device (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_free_block (struct dasd_block*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_remove_sysfs_files (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_set_target_state (struct dasd_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dasd_generic_remove(struct ccw_device *cdev)
{
	struct dasd_device *device;
	struct dasd_block *block;

	cdev->handler = NULL;

	device = dasd_device_from_cdev(cdev);
	if (IS_ERR(device))
		return;
	if (test_and_set_bit(DASD_FLAG_OFFLINE, &device->flags) &&
	    !test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) {
		/* Already doing offline processing */
		dasd_put_device(device);
		return;
	}
	/*
	 * This device is removed unconditionally. Set offline
	 * flag to prevent dasd_open from opening it while it is
	 * no quite down yet.
	 */
	dasd_set_target_state(device, DASD_STATE_NEW);
	/* dasd_delete_device destroys the device reference. */
	block = device->block;
	dasd_delete_device(device);
	/*
	 * life cycle of block is bound to device, so delete it after
	 * device was safely removed
	 */
	if (block)
		dasd_free_block(block);

	dasd_remove_sysfs_files(cdev);
}