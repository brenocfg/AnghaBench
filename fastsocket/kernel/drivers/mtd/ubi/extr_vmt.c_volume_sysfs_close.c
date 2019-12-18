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
struct ubi_volume {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_vol_alignment ; 
 int /*<<< orphan*/  attr_vol_corrupted ; 
 int /*<<< orphan*/  attr_vol_data_bytes ; 
 int /*<<< orphan*/  attr_vol_name ; 
 int /*<<< orphan*/  attr_vol_reserved_ebs ; 
 int /*<<< orphan*/  attr_vol_type ; 
 int /*<<< orphan*/  attr_vol_upd_marker ; 
 int /*<<< orphan*/  attr_vol_usable_eb_size ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void volume_sysfs_close(struct ubi_volume *vol)
{
	device_remove_file(&vol->dev, &attr_vol_upd_marker);
	device_remove_file(&vol->dev, &attr_vol_data_bytes);
	device_remove_file(&vol->dev, &attr_vol_usable_eb_size);
	device_remove_file(&vol->dev, &attr_vol_alignment);
	device_remove_file(&vol->dev, &attr_vol_corrupted);
	device_remove_file(&vol->dev, &attr_vol_name);
	device_remove_file(&vol->dev, &attr_vol_type);
	device_remove_file(&vol->dev, &attr_vol_reserved_ebs);
	device_unregister(&vol->dev);
}