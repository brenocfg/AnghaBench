#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dasd_device {int /*<<< orphan*/  state; int /*<<< orphan*/ * debug_area; scalar_t__ debugfs_dentry; int /*<<< orphan*/  profile; TYPE_1__* block; } ;
struct TYPE_3__ {scalar_t__ debugfs_dentry; int /*<<< orphan*/  profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STATE_KNOWN ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,struct dasd_device*) ; 
 int /*<<< orphan*/  DBF_EMERG ; 
 int /*<<< orphan*/  dasd_block_clear_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  dasd_device_clear_timer (struct dasd_device*) ; 
 int dasd_flush_device_queue (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_gendisk_free (TYPE_1__*) ; 
 int /*<<< orphan*/  dasd_profile_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (scalar_t__) ; 

__attribute__((used)) static int dasd_state_basic_to_known(struct dasd_device *device)
{
	int rc;
	if (device->block) {
		dasd_profile_exit(&device->block->profile);
		if (device->block->debugfs_dentry)
			debugfs_remove(device->block->debugfs_dentry);
		dasd_gendisk_free(device->block);
		dasd_block_clear_timer(device->block);
	}
	rc = dasd_flush_device_queue(device);
	if (rc)
		return rc;
	dasd_device_clear_timer(device);
	dasd_profile_exit(&device->profile);
	if (device->debugfs_dentry)
		debugfs_remove(device->debugfs_dentry);

	DBF_DEV_EVENT(DBF_EMERG, device, "%p debug area deleted", device);
	if (device->debug_area != NULL) {
		debug_unregister(device->debug_area);
		device->debug_area = NULL;
	}
	device->state = DASD_STATE_KNOWN;
	return 0;
}