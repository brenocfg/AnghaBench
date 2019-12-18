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
struct btrfs_space_info {int /*<<< orphan*/  lock; int /*<<< orphan*/ * block_groups; } ;

/* Variables and functions */
 int BTRFS_NR_RAID_TYPES ; 
 scalar_t__ __btrfs_get_ro_block_group_free_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

u64 btrfs_account_ro_block_groups_free_space(struct btrfs_space_info *sinfo)
{
	int i;
	u64 free_bytes = 0;

	spin_lock(&sinfo->lock);

	for(i = 0; i < BTRFS_NR_RAID_TYPES; i++)
		if (!list_empty(&sinfo->block_groups[i]))
			free_bytes += __btrfs_get_ro_block_group_free_space(
						&sinfo->block_groups[i]);

	spin_unlock(&sinfo->lock);

	return free_bytes;
}