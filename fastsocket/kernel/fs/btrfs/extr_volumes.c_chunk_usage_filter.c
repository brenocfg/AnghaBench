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
struct btrfs_fs_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;
struct btrfs_block_group_cache {TYPE_1__ key; int /*<<< orphan*/  item; } ;
struct btrfs_balance_args {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 scalar_t__ btrfs_block_group_used (int /*<<< orphan*/ *) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 scalar_t__ div_factor_fine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chunk_usage_filter(struct btrfs_fs_info *fs_info, u64 chunk_offset,
			      struct btrfs_balance_args *bargs)
{
	struct btrfs_block_group_cache *cache;
	u64 chunk_used, user_thresh;
	int ret = 1;

	cache = btrfs_lookup_block_group(fs_info, chunk_offset);
	chunk_used = btrfs_block_group_used(&cache->item);

	user_thresh = div_factor_fine(cache->key.offset, bargs->usage);
	if (chunk_used < user_thresh)
		ret = 0;

	btrfs_put_block_group(cache);
	return ret;
}