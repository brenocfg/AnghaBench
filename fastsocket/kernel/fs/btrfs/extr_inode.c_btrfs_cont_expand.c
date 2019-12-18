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
struct extent_state {int dummy; } ;
struct extent_map {int /*<<< orphan*/  flags; } ;
struct extent_io_tree {int dummy; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  flags; } ;
struct btrfs_root {scalar_t__ sectorsize; } ;
struct btrfs_ordered_extent {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct extent_io_tree io_tree; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  EXTENT_FLAG_PREALLOC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct extent_map*) ; 
 int PTR_ERR (struct extent_map*) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct extent_map*,struct btrfs_root*,int) ; 
 int /*<<< orphan*/  btrfs_drop_extent_cache (struct inode*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_drop_extents (struct extent_map*,struct inode*,scalar_t__,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct extent_map*,struct btrfs_root*) ; 
 struct extent_map* btrfs_get_extent (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_ino (struct inode*) ; 
 int btrfs_insert_file_extent (struct extent_map*,struct btrfs_root*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_ordered_extent* btrfs_lookup_ordered_extent (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 struct extent_map* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int /*<<< orphan*/  btrfs_update_inode (struct extent_map*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  btrfs_wait_ordered_range (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  extent_map_end (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 int /*<<< orphan*/  lock_extent_bits (struct extent_io_tree*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct extent_state**) ; 
 scalar_t__ min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_extent_cached (struct extent_io_tree*,scalar_t__,scalar_t__,struct extent_state**,int /*<<< orphan*/ ) ; 

int btrfs_cont_expand(struct inode *inode, loff_t oldsize, loff_t size)
{
	struct btrfs_trans_handle *trans;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct extent_map *em = NULL;
	struct extent_state *cached_state = NULL;
	u64 mask = root->sectorsize - 1;
	u64 hole_start = (oldsize + mask) & ~mask;
	u64 block_end = (size + mask) & ~mask;
	u64 last_byte;
	u64 cur_offset;
	u64 hole_size;
	int err = 0;

	if (size <= hole_start)
		return 0;

	while (1) {
		struct btrfs_ordered_extent *ordered;
		btrfs_wait_ordered_range(inode, hole_start,
					 block_end - hole_start);
		lock_extent_bits(io_tree, hole_start, block_end - 1, 0,
				 &cached_state);
		ordered = btrfs_lookup_ordered_extent(inode, hole_start);
		if (!ordered)
			break;
		unlock_extent_cached(io_tree, hole_start, block_end - 1,
				     &cached_state, GFP_NOFS);
		btrfs_put_ordered_extent(ordered);
	}

	cur_offset = hole_start;
	while (1) {
		em = btrfs_get_extent(inode, NULL, 0, cur_offset,
				block_end - cur_offset, 0);
		if (IS_ERR(em)) {
			err = PTR_ERR(em);
			break;
		}
		last_byte = min(extent_map_end(em), block_end);
		last_byte = (last_byte + mask) & ~mask;
		if (!test_bit(EXTENT_FLAG_PREALLOC, &em->flags)) {
			u64 hint_byte = 0;
			hole_size = last_byte - cur_offset;

			trans = btrfs_start_transaction(root, 3);
			if (IS_ERR(trans)) {
				err = PTR_ERR(trans);
				break;
			}

			err = btrfs_drop_extents(trans, inode, cur_offset,
						 cur_offset + hole_size,
						 &hint_byte, 1);
			if (err) {
				btrfs_abort_transaction(trans, root, err);
				btrfs_end_transaction(trans, root);
				break;
			}

			err = btrfs_insert_file_extent(trans, root,
					btrfs_ino(inode), cur_offset, 0,
					0, hole_size, 0, hole_size,
					0, 0, 0);
			if (err) {
				btrfs_abort_transaction(trans, root, err);
				btrfs_end_transaction(trans, root);
				break;
			}

			btrfs_drop_extent_cache(inode, hole_start,
					last_byte - 1, 0);

			btrfs_update_inode(trans, root, inode);
			btrfs_end_transaction(trans, root);
		}
		free_extent_map(em);
		em = NULL;
		cur_offset = last_byte;
		if (cur_offset >= block_end)
			break;
	}

	free_extent_map(em);
	unlock_extent_cached(io_tree, hole_start, block_end - 1, &cached_state,
			     GFP_NOFS);
	return err;
}