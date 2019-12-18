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
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_vol_alignment ; 
 int /*<<< orphan*/  attr_vol_corrupted ; 
 int /*<<< orphan*/  attr_vol_data_bytes ; 
 int /*<<< orphan*/  attr_vol_name ; 
 int /*<<< orphan*/  attr_vol_reserved_ebs ; 
 int /*<<< orphan*/  attr_vol_type ; 
 int /*<<< orphan*/  attr_vol_upd_marker ; 
 int /*<<< orphan*/  attr_vol_usable_eb_size ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int volume_sysfs_init(struct ubi_device *ubi, struct ubi_volume *vol)
{
	int err;

	err = device_create_file(&vol->dev, &attr_vol_reserved_ebs);
	if (err)
		return err;
	err = device_create_file(&vol->dev, &attr_vol_type);
	if (err)
		return err;
	err = device_create_file(&vol->dev, &attr_vol_name);
	if (err)
		return err;
	err = device_create_file(&vol->dev, &attr_vol_corrupted);
	if (err)
		return err;
	err = device_create_file(&vol->dev, &attr_vol_alignment);
	if (err)
		return err;
	err = device_create_file(&vol->dev, &attr_vol_usable_eb_size);
	if (err)
		return err;
	err = device_create_file(&vol->dev, &attr_vol_data_bytes);
	if (err)
		return err;
	err = device_create_file(&vol->dev, &attr_vol_upd_marker);
	return err;
}