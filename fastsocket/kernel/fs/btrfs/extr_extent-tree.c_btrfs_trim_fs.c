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
struct fstrim_range {scalar_t__ len; scalar_t__ start; scalar_t__ minlen; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_root; int /*<<< orphan*/  super_copy; } ;
struct TYPE_2__ {scalar_t__ objectid; scalar_t__ offset; } ;
struct btrfs_block_group_cache {TYPE_1__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_group_cache_done (struct btrfs_block_group_cache*) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,scalar_t__) ; 
 struct btrfs_block_group_cache* btrfs_lookup_first_block_group (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 scalar_t__ btrfs_super_total_bytes (int /*<<< orphan*/ ) ; 
 int btrfs_trim_block_group (struct btrfs_block_group_cache*,scalar_t__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int cache_block_group (struct btrfs_block_group_cache*,int /*<<< orphan*/ *,struct btrfs_root*,int /*<<< orphan*/ ) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct btrfs_block_group_cache* next_block_group (int /*<<< orphan*/ ,struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  wait_block_group_cache_done (struct btrfs_block_group_cache*) ; 

int btrfs_trim_fs(struct btrfs_root *root, struct fstrim_range *range)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_block_group_cache *cache = NULL;
	u64 group_trimmed;
	u64 start;
	u64 end;
	u64 trimmed = 0;
	u64 total_bytes = btrfs_super_total_bytes(fs_info->super_copy);
	int ret = 0;

	/*
	 * try to trim all FS space, our block group may start from non-zero.
	 */
	if (range->len == total_bytes)
		cache = btrfs_lookup_first_block_group(fs_info, range->start);
	else
		cache = btrfs_lookup_block_group(fs_info, range->start);

	while (cache) {
		if (cache->key.objectid >= (range->start + range->len)) {
			btrfs_put_block_group(cache);
			break;
		}

		start = max(range->start, cache->key.objectid);
		end = min(range->start + range->len,
				cache->key.objectid + cache->key.offset);

		if (end - start >= range->minlen) {
			if (!block_group_cache_done(cache)) {
				ret = cache_block_group(cache, NULL, root, 0);
				if (!ret)
					wait_block_group_cache_done(cache);
			}
			ret = btrfs_trim_block_group(cache,
						     &group_trimmed,
						     start,
						     end,
						     range->minlen);

			trimmed += group_trimmed;
			if (ret) {
				btrfs_put_block_group(cache);
				break;
			}
		}

		cache = next_block_group(fs_info->tree_root, cache);
	}

	range->len = trimmed;
	return ret;
}