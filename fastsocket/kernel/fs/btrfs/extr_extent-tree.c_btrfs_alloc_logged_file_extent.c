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
typedef  scalar_t__ u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  fs_info; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ offset; } ;
struct btrfs_caching_control {scalar_t__ progress; int /*<<< orphan*/  mutex; } ;
struct btrfs_block_group_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RESERVE_ALLOC_NO_ACCOUNT ; 
 int add_excluded_extent (struct btrfs_root*,scalar_t__,scalar_t__) ; 
 int alloc_reserved_file_extent (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  block_group_cache_done (struct btrfs_block_group_cache*) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int btrfs_remove_free_space (struct btrfs_block_group_cache*,scalar_t__,scalar_t__) ; 
 int btrfs_update_reserved_bytes (struct btrfs_block_group_cache*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_block_group (struct btrfs_block_group_cache*,struct btrfs_trans_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct btrfs_caching_control* get_caching_control (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_caching_control (struct btrfs_caching_control*) ; 

int btrfs_alloc_logged_file_extent(struct btrfs_trans_handle *trans,
				   struct btrfs_root *root,
				   u64 root_objectid, u64 owner, u64 offset,
				   struct btrfs_key *ins)
{
	int ret;
	struct btrfs_block_group_cache *block_group;
	struct btrfs_caching_control *caching_ctl;
	u64 start = ins->objectid;
	u64 num_bytes = ins->offset;

	block_group = btrfs_lookup_block_group(root->fs_info, ins->objectid);
	cache_block_group(block_group, trans, NULL, 0);
	caching_ctl = get_caching_control(block_group);

	if (!caching_ctl) {
		BUG_ON(!block_group_cache_done(block_group));
		ret = btrfs_remove_free_space(block_group, start, num_bytes);
		BUG_ON(ret); /* -ENOMEM */
	} else {
		mutex_lock(&caching_ctl->mutex);

		if (start >= caching_ctl->progress) {
			ret = add_excluded_extent(root, start, num_bytes);
			BUG_ON(ret); /* -ENOMEM */
		} else if (start + num_bytes <= caching_ctl->progress) {
			ret = btrfs_remove_free_space(block_group,
						      start, num_bytes);
			BUG_ON(ret); /* -ENOMEM */
		} else {
			num_bytes = caching_ctl->progress - start;
			ret = btrfs_remove_free_space(block_group,
						      start, num_bytes);
			BUG_ON(ret); /* -ENOMEM */

			start = caching_ctl->progress;
			num_bytes = ins->objectid + ins->offset -
				    caching_ctl->progress;
			ret = add_excluded_extent(root, start, num_bytes);
			BUG_ON(ret); /* -ENOMEM */
		}

		mutex_unlock(&caching_ctl->mutex);
		put_caching_control(caching_ctl);
	}

	ret = btrfs_update_reserved_bytes(block_group, ins->offset,
					  RESERVE_ALLOC_NO_ACCOUNT);
	BUG_ON(ret); /* logic error */
	btrfs_put_block_group(block_group);
	ret = alloc_reserved_file_extent(trans, root, 0, root_objectid,
					 0, owner, offset, ins, 1);
	return ret;
}