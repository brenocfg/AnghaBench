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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_block_group_cache {scalar_t__ flags; TYPE_1__* space_info; int /*<<< orphan*/  ro; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHUNK_ALLOC_FORCE ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 struct btrfs_trans_handle* btrfs_join_transaction (struct btrfs_root*) ; 
 int do_chunk_alloc (struct btrfs_trans_handle*,struct btrfs_root*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ get_alloc_profile (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int set_block_group_ro (struct btrfs_block_group_cache*,int /*<<< orphan*/ ) ; 
 scalar_t__ update_block_group_flags (struct btrfs_root*,scalar_t__) ; 

int btrfs_set_block_group_ro(struct btrfs_root *root,
			     struct btrfs_block_group_cache *cache)

{
	struct btrfs_trans_handle *trans;
	u64 alloc_flags;
	int ret;

	BUG_ON(cache->ro);

	trans = btrfs_join_transaction(root);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	alloc_flags = update_block_group_flags(root, cache->flags);
	if (alloc_flags != cache->flags) {
		ret = do_chunk_alloc(trans, root, 2 * 1024 * 1024, alloc_flags,
				     CHUNK_ALLOC_FORCE);
		if (ret < 0)
			goto out;
	}

	ret = set_block_group_ro(cache, 0);
	if (!ret)
		goto out;
	alloc_flags = get_alloc_profile(root, cache->space_info->flags);
	ret = do_chunk_alloc(trans, root, 2 * 1024 * 1024, alloc_flags,
			     CHUNK_ALLOC_FORCE);
	if (ret < 0)
		goto out;
	ret = set_block_group_ro(cache, 0);
out:
	btrfs_end_transaction(trans, root);
	return ret;
}