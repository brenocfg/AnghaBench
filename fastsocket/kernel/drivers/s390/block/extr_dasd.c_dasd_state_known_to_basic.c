#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dasd_device {int /*<<< orphan*/  state; int /*<<< orphan*/  debug_area; TYPE_2__* cdev; void* debugfs_dentry; int /*<<< orphan*/  profile; struct dasd_block* block; } ;
struct dasd_block {int /*<<< orphan*/  profile; void* debugfs_dentry; TYPE_1__* gdp; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 scalar_t__ DASD_PROFILE_ON ; 
 int /*<<< orphan*/  DASD_STATE_BASIC ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_EMERG ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int /*<<< orphan*/  dasd_debugfs_root_entry ; 
 void* dasd_debugfs_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dasd_gendisk_alloc (struct dasd_block*) ; 
 scalar_t__ dasd_global_profile_level ; 
 int /*<<< orphan*/  dasd_profile_init (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  dasd_profile_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_register (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  debug_register_view (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_sprintf_view ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dasd_state_known_to_basic(struct dasd_device *device)
{
	struct dasd_block *block = device->block;
	int rc;

	/* Allocate and register gendisk structure. */
	if (block) {
		rc = dasd_gendisk_alloc(block);
		if (rc)
			return rc;
		block->debugfs_dentry =
			dasd_debugfs_setup(block->gdp->disk_name,
					   dasd_debugfs_root_entry);
		dasd_profile_init(&block->profile, block->debugfs_dentry);
		if (dasd_global_profile_level == DASD_PROFILE_ON)
			dasd_profile_on(&device->block->profile);
	}
	device->debugfs_dentry =
		dasd_debugfs_setup(dev_name(&device->cdev->dev),
				   dasd_debugfs_root_entry);
	dasd_profile_init(&device->profile, device->debugfs_dentry);

	/* register 'device' debug area, used for all DBF_DEV_XXX calls */
	device->debug_area = debug_register(dev_name(&device->cdev->dev), 4, 1,
					    8 * sizeof(long));
	debug_register_view(device->debug_area, &debug_sprintf_view);
	debug_set_level(device->debug_area, DBF_WARNING);
	DBF_DEV_EVENT(DBF_EMERG, device, "%s", "debug area created");

	device->state = DASD_STATE_BASIC;
	return 0;
}