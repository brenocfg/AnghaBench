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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_fs_devices {struct btrfs_fs_devices* seed; int /*<<< orphan*/  devices; int /*<<< orphan*/  fsid; } ;
struct btrfs_device {int dummy; } ;
struct TYPE_2__ {struct btrfs_fs_devices* fs_devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_UUID_SIZE ; 
 struct btrfs_device* __find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct btrfs_device *btrfs_find_device(struct btrfs_root *root, u64 devid,
				       u8 *uuid, u8 *fsid)
{
	struct btrfs_device *device;
	struct btrfs_fs_devices *cur_devices;

	cur_devices = root->fs_info->fs_devices;
	while (cur_devices) {
		if (!fsid ||
		    !memcmp(cur_devices->fsid, fsid, BTRFS_UUID_SIZE)) {
			device = __find_device(&cur_devices->devices,
					       devid, uuid);
			if (device)
				return device;
		}
		cur_devices = cur_devices->seed;
	}
	return NULL;
}