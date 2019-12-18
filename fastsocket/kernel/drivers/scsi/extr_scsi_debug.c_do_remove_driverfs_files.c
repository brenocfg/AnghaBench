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
 int /*<<< orphan*/  driver_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdebug_driverfs_driver ; 

__attribute__((used)) static void do_remove_driverfs_files(void)
{
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_map);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_ato);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_guard);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_dif);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_dix);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_sector_size);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_vpd_use_hostno);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_virtual_gb);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_scsi_level);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_opts);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_ptype);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_num_tgts);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_num_parts);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_no_uld);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_no_lun_0);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_max_queue);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_max_luns);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_fake_rw);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_every_nth);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_dsense);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_dev_size_mb);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_delay);
	driver_remove_file(&sdebug_driverfs_driver, &driver_attr_add_host);
}