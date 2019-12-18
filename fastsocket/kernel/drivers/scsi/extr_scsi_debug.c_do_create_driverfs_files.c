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

/* Variables and functions */
 int /*<<< orphan*/  driver_attr_add_host ; 
 int /*<<< orphan*/  driver_attr_ato ; 
 int /*<<< orphan*/  driver_attr_delay ; 
 int /*<<< orphan*/  driver_attr_dev_size_mb ; 
 int /*<<< orphan*/  driver_attr_dif ; 
 int /*<<< orphan*/  driver_attr_dix ; 
 int /*<<< orphan*/  driver_attr_dsense ; 
 int /*<<< orphan*/  driver_attr_every_nth ; 
 int /*<<< orphan*/  driver_attr_fake_rw ; 
 int /*<<< orphan*/  driver_attr_guard ; 
 int /*<<< orphan*/  driver_attr_map ; 
 int /*<<< orphan*/  driver_attr_max_luns ; 
 int /*<<< orphan*/  driver_attr_max_queue ; 
 int /*<<< orphan*/  driver_attr_no_lun_0 ; 
 int /*<<< orphan*/  driver_attr_no_uld ; 
 int /*<<< orphan*/  driver_attr_num_parts ; 
 int /*<<< orphan*/  driver_attr_num_tgts ; 
 int /*<<< orphan*/  driver_attr_opts ; 
 int /*<<< orphan*/  driver_attr_ptype ; 
 int /*<<< orphan*/  driver_attr_scsi_level ; 
 int /*<<< orphan*/  driver_attr_sector_size ; 
 int /*<<< orphan*/  driver_attr_virtual_gb ; 
 int /*<<< orphan*/  driver_attr_vpd_use_hostno ; 
 int driver_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdebug_driverfs_driver ; 

__attribute__((used)) static int do_create_driverfs_files(void)
{
	int ret;

	ret = driver_create_file(&sdebug_driverfs_driver, &driver_attr_add_host);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_delay);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_dev_size_mb);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_dsense);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_every_nth);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_fake_rw);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_max_luns);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_max_queue);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_no_lun_0);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_no_uld);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_num_parts);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_num_tgts);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_ptype);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_opts);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_scsi_level);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_virtual_gb);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_vpd_use_hostno);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_sector_size);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_dix);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_dif);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_guard);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_ato);
	ret |= driver_create_file(&sdebug_driverfs_driver, &driver_attr_map);
	return ret;
}