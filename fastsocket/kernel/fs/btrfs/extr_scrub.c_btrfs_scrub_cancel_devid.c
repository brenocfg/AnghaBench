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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {TYPE_1__* fs_devices; } ;
struct btrfs_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_list_mutex; } ;

/* Variables and functions */
 int ENODEV ; 
 struct btrfs_device* btrfs_find_device (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int btrfs_scrub_cancel_dev (struct btrfs_root*,struct btrfs_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int btrfs_scrub_cancel_devid(struct btrfs_root *root, u64 devid)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_device *dev;
	int ret;

	/*
	 * we have to hold the device_list_mutex here so the device
	 * does not go away in cancel_dev. FIXME: find a better solution
	 */
	mutex_lock(&fs_info->fs_devices->device_list_mutex);
	dev = btrfs_find_device(root, devid, NULL, NULL);
	if (!dev) {
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		return -ENODEV;
	}
	ret = btrfs_scrub_cancel_dev(root, dev);
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);

	return ret;
}