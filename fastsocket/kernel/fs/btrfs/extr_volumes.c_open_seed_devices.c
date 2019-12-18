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
typedef  int /*<<< orphan*/  u8 ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct btrfs_fs_devices {struct btrfs_fs_devices* seed; int /*<<< orphan*/  seeding; int /*<<< orphan*/  fsid; } ;
struct TYPE_4__ {TYPE_1__* fs_devices; int /*<<< orphan*/  bdev_holder; } ;
struct TYPE_3__ {struct btrfs_fs_devices* seed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_UUID_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  FMODE_READ ; 
 scalar_t__ IS_ERR (struct btrfs_fs_devices*) ; 
 int PTR_ERR (struct btrfs_fs_devices*) ; 
 int /*<<< orphan*/  __btrfs_close_devices (struct btrfs_fs_devices*) ; 
 int __btrfs_open_devices (struct btrfs_fs_devices*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_fs_devices* clone_fs_devices (struct btrfs_fs_devices*) ; 
 struct btrfs_fs_devices* find_fsid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_fs_devices (struct btrfs_fs_devices*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_mutex ; 

__attribute__((used)) static int open_seed_devices(struct btrfs_root *root, u8 *fsid)
{
	struct btrfs_fs_devices *fs_devices;
	int ret;

	BUG_ON(!mutex_is_locked(&uuid_mutex));

	fs_devices = root->fs_info->fs_devices->seed;
	while (fs_devices) {
		if (!memcmp(fs_devices->fsid, fsid, BTRFS_UUID_SIZE)) {
			ret = 0;
			goto out;
		}
		fs_devices = fs_devices->seed;
	}

	fs_devices = find_fsid(fsid);
	if (!fs_devices) {
		ret = -ENOENT;
		goto out;
	}

	fs_devices = clone_fs_devices(fs_devices);
	if (IS_ERR(fs_devices)) {
		ret = PTR_ERR(fs_devices);
		goto out;
	}

	ret = __btrfs_open_devices(fs_devices, FMODE_READ,
				   root->fs_info->bdev_holder);
	if (ret) {
		free_fs_devices(fs_devices);
		goto out;
	}

	if (!fs_devices->seeding) {
		__btrfs_close_devices(fs_devices);
		free_fs_devices(fs_devices);
		ret = -EINVAL;
		goto out;
	}

	fs_devices->seed = root->fs_info->fs_devices->seed;
	root->fs_info->fs_devices->seed = fs_devices;
out:
	return ret;
}