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
typedef  int /*<<< orphan*/  u64 ;
struct scrub_dev {int /*<<< orphan*/  stat; } ;
struct btrfs_scrub_progress {int dummy; } ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct btrfs_device {struct scrub_dev* scrub_device; } ;
struct TYPE_4__ {TYPE_1__* fs_devices; } ;
struct TYPE_3__ {int /*<<< orphan*/  device_list_mutex; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOTCONN ; 
 struct btrfs_device* btrfs_find_device (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct btrfs_scrub_progress*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int btrfs_scrub_progress(struct btrfs_root *root, u64 devid,
			 struct btrfs_scrub_progress *progress)
{
	struct btrfs_device *dev;
	struct scrub_dev *sdev = NULL;

	mutex_lock(&root->fs_info->fs_devices->device_list_mutex);
	dev = btrfs_find_device(root, devid, NULL, NULL);
	if (dev)
		sdev = dev->scrub_device;
	if (sdev)
		memcpy(progress, &sdev->stat, sizeof(*progress));
	mutex_unlock(&root->fs_info->fs_devices->device_list_mutex);

	return dev ? (sdev ? 0 : -ENOTCONN) : -ENODEV;
}