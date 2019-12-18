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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_device {int /*<<< orphan*/  dev_root; } ;

/* Variables and functions */
 int __btrfs_grow_device (struct btrfs_trans_handle*,struct btrfs_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_chunks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_chunks (int /*<<< orphan*/ ) ; 

int btrfs_grow_device(struct btrfs_trans_handle *trans,
		      struct btrfs_device *device, u64 new_size)
{
	int ret;
	lock_chunks(device->dev_root);
	ret = __btrfs_grow_device(trans, device, new_size);
	unlock_chunks(device->dev_root);
	return ret;
}