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
typedef  int u32 ;
struct extent_buffer {scalar_t__ start; } ;
struct btrfs_trans_handle {scalar_t__ transaction; scalar_t__ transid; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_disk_key {int dummy; } ;
struct TYPE_2__ {scalar_t__ running_transaction; scalar_t__ generation; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __btrfs_cow_block (struct btrfs_trans_handle*,struct btrfs_root*,struct extent_buffer*,struct extent_buffer*,int,struct extent_buffer**,scalar_t__,int /*<<< orphan*/ ) ; 
 int btrfs_buffer_uptodate (struct extent_buffer*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct extent_buffer* btrfs_find_tree_block (struct btrfs_root*,scalar_t__,int) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int btrfs_level_size (struct btrfs_root*,int) ; 
 scalar_t__ btrfs_node_blockptr (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_node_key (struct extent_buffer*,struct btrfs_disk_key*,int) ; 
 scalar_t__ btrfs_node_ptr_generation (struct extent_buffer*,int) ; 
 int btrfs_read_buffer (struct extent_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_unlock (struct extent_buffer*) ; 
 int close_blocks (scalar_t__,scalar_t__,int) ; 
 scalar_t__ comp_keys (struct btrfs_disk_key*,struct btrfs_key*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  min (int,int) ; 
 struct extent_buffer* read_tree_block (struct btrfs_root*,scalar_t__,int,scalar_t__) ; 

int btrfs_realloc_node(struct btrfs_trans_handle *trans,
		       struct btrfs_root *root, struct extent_buffer *parent,
		       int start_slot, int cache_only, u64 *last_ret,
		       struct btrfs_key *progress)
{
	struct extent_buffer *cur;
	u64 blocknr;
	u64 gen;
	u64 search_start = *last_ret;
	u64 last_block = 0;
	u64 other;
	u32 parent_nritems;
	int end_slot;
	int i;
	int err = 0;
	int parent_level;
	int uptodate;
	u32 blocksize;
	int progress_passed = 0;
	struct btrfs_disk_key disk_key;

	parent_level = btrfs_header_level(parent);
	if (cache_only && parent_level != 1)
		return 0;

	if (trans->transaction != root->fs_info->running_transaction)
		WARN_ON(1);
	if (trans->transid != root->fs_info->generation)
		WARN_ON(1);

	parent_nritems = btrfs_header_nritems(parent);
	blocksize = btrfs_level_size(root, parent_level - 1);
	end_slot = parent_nritems;

	if (parent_nritems == 1)
		return 0;

	btrfs_set_lock_blocking(parent);

	for (i = start_slot; i < end_slot; i++) {
		int close = 1;

		btrfs_node_key(parent, &disk_key, i);
		if (!progress_passed && comp_keys(&disk_key, progress) < 0)
			continue;

		progress_passed = 1;
		blocknr = btrfs_node_blockptr(parent, i);
		gen = btrfs_node_ptr_generation(parent, i);
		if (last_block == 0)
			last_block = blocknr;

		if (i > 0) {
			other = btrfs_node_blockptr(parent, i - 1);
			close = close_blocks(blocknr, other, blocksize);
		}
		if (!close && i < end_slot - 2) {
			other = btrfs_node_blockptr(parent, i + 1);
			close = close_blocks(blocknr, other, blocksize);
		}
		if (close) {
			last_block = blocknr;
			continue;
		}

		cur = btrfs_find_tree_block(root, blocknr, blocksize);
		if (cur)
			uptodate = btrfs_buffer_uptodate(cur, gen, 0);
		else
			uptodate = 0;
		if (!cur || !uptodate) {
			if (cache_only) {
				free_extent_buffer(cur);
				continue;
			}
			if (!cur) {
				cur = read_tree_block(root, blocknr,
							 blocksize, gen);
				if (!cur)
					return -EIO;
			} else if (!uptodate) {
				err = btrfs_read_buffer(cur, gen);
				if (err) {
					free_extent_buffer(cur);
					return err;
				}
			}
		}
		if (search_start == 0)
			search_start = last_block;

		btrfs_tree_lock(cur);
		btrfs_set_lock_blocking(cur);
		err = __btrfs_cow_block(trans, root, cur, parent, i,
					&cur, search_start,
					min(16 * blocksize,
					    (end_slot - i) * blocksize));
		if (err) {
			btrfs_tree_unlock(cur);
			free_extent_buffer(cur);
			break;
		}
		search_start = cur->start;
		last_block = cur->start;
		*last_ret = search_start;
		btrfs_tree_unlock(cur);
		free_extent_buffer(cur);
	}
	return err;
}