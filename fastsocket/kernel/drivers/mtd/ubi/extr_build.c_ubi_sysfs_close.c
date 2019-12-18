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
struct ubi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_avail_eraseblocks ; 
 int /*<<< orphan*/  dev_bad_peb_count ; 
 int /*<<< orphan*/  dev_bgt_enabled ; 
 int /*<<< orphan*/  dev_eraseblock_size ; 
 int /*<<< orphan*/  dev_max_ec ; 
 int /*<<< orphan*/  dev_max_vol_count ; 
 int /*<<< orphan*/  dev_min_io_size ; 
 int /*<<< orphan*/  dev_mtd_num ; 
 int /*<<< orphan*/  dev_reserved_for_bad ; 
 int /*<<< orphan*/  dev_total_eraseblocks ; 
 int /*<<< orphan*/  dev_volumes_count ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ubi_sysfs_close(struct ubi_device *ubi)
{
	device_remove_file(&ubi->dev, &dev_mtd_num);
	device_remove_file(&ubi->dev, &dev_bgt_enabled);
	device_remove_file(&ubi->dev, &dev_min_io_size);
	device_remove_file(&ubi->dev, &dev_max_vol_count);
	device_remove_file(&ubi->dev, &dev_bad_peb_count);
	device_remove_file(&ubi->dev, &dev_reserved_for_bad);
	device_remove_file(&ubi->dev, &dev_max_ec);
	device_remove_file(&ubi->dev, &dev_volumes_count);
	device_remove_file(&ubi->dev, &dev_total_eraseblocks);
	device_remove_file(&ubi->dev, &dev_avail_eraseblocks);
	device_remove_file(&ubi->dev, &dev_eraseblock_size);
	device_unregister(&ubi->dev);
}