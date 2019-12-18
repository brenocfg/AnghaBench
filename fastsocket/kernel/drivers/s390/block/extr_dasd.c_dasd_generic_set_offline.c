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
struct dasd_device {int /*<<< orphan*/  flags; struct dasd_block* block; } ;
struct dasd_block {scalar_t__ bdev; int /*<<< orphan*/  open_count; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FLAG_OFFLINE ; 
 int /*<<< orphan*/  DASD_FLAG_SAFE_OFFLINE ; 
 int /*<<< orphan*/  DASD_FLAG_SAFE_OFFLINE_RUNNING ; 
 int /*<<< orphan*/  DASD_STATE_NEW ; 
 int EBUSY ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int PTR_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  _wait_for_empty_queues (struct dasd_device*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_delete_device (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_free_block (struct dasd_block*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_set_target_state (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int fsync_bdev (scalar_t__) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_waitq ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dasd_generic_set_offline(struct ccw_device *cdev)
{
	struct dasd_device *device;
	struct dasd_block *block;
	int max_count, open_count, rc;

	rc = 0;
	device = dasd_device_from_cdev(cdev);
	if (IS_ERR(device))
		return PTR_ERR(device);

	/*
	 * We must make sure that this device is currently not in use.
	 * The open_count is increased for every opener, that includes
	 * the blkdev_get in dasd_scan_partitions. We are only interested
	 * in the other openers.
	 */
	if (device->block) {
		max_count = device->block->bdev ? 0 : -1;
		open_count = atomic_read(&device->block->open_count);
		if (open_count > max_count) {
			if (open_count > 0)
				pr_warning("%s: The DASD cannot be set offline "
					   "with open count %i\n",
					   dev_name(&cdev->dev), open_count);
			else
				pr_warning("%s: The DASD cannot be set offline "
					   "while it is in use\n",
					   dev_name(&cdev->dev));
			clear_bit(DASD_FLAG_OFFLINE, &device->flags);
			dasd_put_device(device);
			return -EBUSY;
		}
	}

	if (test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) {
		/*
		 * safe offline allready running
		 * could only be called by normal offline so safe_offline flag
		 * needs to be removed to run normal offline and kill all I/O
		 */
		if (test_and_set_bit(DASD_FLAG_OFFLINE, &device->flags)) {
			/* Already doing normal offline processing */
			dasd_put_device(device);
			return -EBUSY;
		} else
			clear_bit(DASD_FLAG_SAFE_OFFLINE, &device->flags);

	} else
		if (test_bit(DASD_FLAG_OFFLINE, &device->flags)) {
			/* Already doing offline processing */
			dasd_put_device(device);
			return -EBUSY;
		}

	/*
	 * if safe_offline called set safe_offline_running flag and
	 * clear safe_offline so that a call to normal offline
	 * can overrun safe_offline processing
	 */
	if (test_and_clear_bit(DASD_FLAG_SAFE_OFFLINE, &device->flags) &&
	    !test_and_set_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) {
		/*
		 * If we want to set the device safe offline all IO operations
		 * should be finished before continuing the offline process
		 * so sync bdev first and then wait for our queues to become
		 * empty
		 */
		/* sync blockdev and partitions */
		rc = fsync_bdev(device->block->bdev);
		if (rc != 0)
			goto interrupted;

		/* schedule device tasklet and wait for completion */
		dasd_schedule_device_bh(device);
		rc = wait_event_interruptible(shutdown_waitq,
					      _wait_for_empty_queues(device));
		if (rc != 0)
			goto interrupted;
	}

	set_bit(DASD_FLAG_OFFLINE, &device->flags);
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
	return 0;

interrupted:
	/* interrupted by signal */
	clear_bit(DASD_FLAG_SAFE_OFFLINE, &device->flags);
	clear_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags);
	clear_bit(DASD_FLAG_OFFLINE, &device->flags);
	dasd_put_device(device);
	return rc;
}