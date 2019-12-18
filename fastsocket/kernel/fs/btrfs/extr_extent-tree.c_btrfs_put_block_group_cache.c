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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_root; } ;
struct TYPE_2__ {scalar_t__ objectid; scalar_t__ offset; } ;
struct btrfs_block_group_cache {TYPE_1__ key; int /*<<< orphan*/  lock; struct inode* inode; scalar_t__ iref; } ;

/* Variables and functions */
 struct btrfs_block_group_cache* btrfs_lookup_first_block_group (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct btrfs_block_group_cache* next_block_group (int /*<<< orphan*/ ,struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_put_block_group_cache(struct btrfs_fs_info *info)
{
	struct btrfs_block_group_cache *block_group;
	u64 last = 0;

	while (1) {
		struct inode *inode;

		block_group = btrfs_lookup_first_block_group(info, last);
		while (block_group) {
			spin_lock(&block_group->lock);
			if (block_group->iref)
				break;
			spin_unlock(&block_group->lock);
			block_group = next_block_group(info->tree_root,
						       block_group);
		}
		if (!block_group) {
			if (last == 0)
				break;
			last = 0;
			continue;
		}

		inode = block_group->inode;
		block_group->iref = 0;
		block_group->inode = NULL;
		spin_unlock(&block_group->lock);
		iput(inode);
		last = block_group->key.objectid + block_group->key.offset;
		btrfs_put_block_group(block_group);
	}
}