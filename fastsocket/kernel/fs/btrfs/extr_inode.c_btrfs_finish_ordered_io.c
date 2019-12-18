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
struct inode {int dummy; } ;
struct extent_state {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct btrfs_trans_handle {int /*<<< orphan*/ * block_rsv; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_ordered_extent {int compress_type; scalar_t__ len; scalar_t__ file_offset; int /*<<< orphan*/  flags; int /*<<< orphan*/  list; int /*<<< orphan*/  disk_len; int /*<<< orphan*/  start; struct inode* inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  extent_tree; struct extent_io_tree io_tree; struct btrfs_root* root; } ;
struct TYPE_3__ {struct btrfs_root* tree_root; int /*<<< orphan*/  delalloc_block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FILE_EXTENT_REG ; 
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_ORDERED_COMPRESSED ; 
 int /*<<< orphan*/  BTRFS_ORDERED_IOERR ; 
 int /*<<< orphan*/  BTRFS_ORDERED_NOCOW ; 
 int /*<<< orphan*/  BTRFS_ORDERED_PREALLOC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  add_pending_csums (struct btrfs_trans_handle*,struct inode*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 int /*<<< orphan*/  btrfs_delalloc_release_metadata (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_end_transaction_nolock (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int btrfs_is_free_space_inode (struct btrfs_root*,struct inode*) ; 
 struct btrfs_trans_handle* btrfs_join_transaction (struct btrfs_root*) ; 
 struct btrfs_trans_handle* btrfs_join_transaction_nolock (struct btrfs_root*) ; 
 int btrfs_mark_extent_written (struct btrfs_trans_handle*,struct inode*,scalar_t__,scalar_t__) ; 
 int btrfs_ordered_update_i_size (struct inode*,int /*<<< orphan*/ ,struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  btrfs_remove_ordered_extent (struct inode*,struct btrfs_ordered_extent*) ; 
 int btrfs_update_inode_fallback (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  clear_extent_uptodate (struct extent_io_tree*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int insert_reserved_file_extent (struct btrfs_trans_handle*,struct inode*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_extent_bits (struct extent_io_tree*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct extent_state**) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_extent_cached (struct extent_io_tree*,scalar_t__,scalar_t__,struct extent_state**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpin_extent_cache (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int btrfs_finish_ordered_io(struct btrfs_ordered_extent *ordered_extent)
{
	struct inode *inode = ordered_extent->inode;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_trans_handle *trans = NULL;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct extent_state *cached_state = NULL;
	int compress_type = 0;
	int ret;
	bool nolock;

	nolock = btrfs_is_free_space_inode(root, inode);

	if (test_bit(BTRFS_ORDERED_IOERR, &ordered_extent->flags)) {
		ret = -EIO;
		goto out;
	}

	if (test_bit(BTRFS_ORDERED_NOCOW, &ordered_extent->flags)) {
		BUG_ON(!list_empty(&ordered_extent->list)); /* Logic error */
		ret = btrfs_ordered_update_i_size(inode, 0, ordered_extent);
		if (!ret) {
			if (nolock)
				trans = btrfs_join_transaction_nolock(root);
			else
				trans = btrfs_join_transaction(root);
			if (IS_ERR(trans))
				return PTR_ERR(trans);
			trans->block_rsv = &root->fs_info->delalloc_block_rsv;
			ret = btrfs_update_inode_fallback(trans, root, inode);
			if (ret) /* -ENOMEM or corruption */
				btrfs_abort_transaction(trans, root, ret);
		}
		goto out;
	}

	lock_extent_bits(io_tree, ordered_extent->file_offset,
			 ordered_extent->file_offset + ordered_extent->len - 1,
			 0, &cached_state);

	if (nolock)
		trans = btrfs_join_transaction_nolock(root);
	else
		trans = btrfs_join_transaction(root);
	if (IS_ERR(trans)) {
		ret = PTR_ERR(trans);
		trans = NULL;
		goto out_unlock;
	}
	trans->block_rsv = &root->fs_info->delalloc_block_rsv;

	if (test_bit(BTRFS_ORDERED_COMPRESSED, &ordered_extent->flags))
		compress_type = ordered_extent->compress_type;
	if (test_bit(BTRFS_ORDERED_PREALLOC, &ordered_extent->flags)) {
		BUG_ON(compress_type);
		ret = btrfs_mark_extent_written(trans, inode,
						ordered_extent->file_offset,
						ordered_extent->file_offset +
						ordered_extent->len);
	} else {
		BUG_ON(root == root->fs_info->tree_root);
		ret = insert_reserved_file_extent(trans, inode,
						ordered_extent->file_offset,
						ordered_extent->start,
						ordered_extent->disk_len,
						ordered_extent->len,
						ordered_extent->len,
						compress_type, 0, 0,
						BTRFS_FILE_EXTENT_REG);
		unpin_extent_cache(&BTRFS_I(inode)->extent_tree,
				   ordered_extent->file_offset,
				   ordered_extent->len);
	}

	if (ret < 0) {
		btrfs_abort_transaction(trans, root, ret);
		goto out_unlock;
	}

	add_pending_csums(trans, inode, ordered_extent->file_offset,
			  &ordered_extent->list);

	ret = btrfs_ordered_update_i_size(inode, 0, ordered_extent);
	if (!ret || !test_bit(BTRFS_ORDERED_PREALLOC, &ordered_extent->flags)) {
		ret = btrfs_update_inode_fallback(trans, root, inode);
		if (ret) { /* -ENOMEM or corruption */
			btrfs_abort_transaction(trans, root, ret);
			goto out_unlock;
		}
	}
	ret = 0;
out_unlock:
	unlock_extent_cached(io_tree, ordered_extent->file_offset,
			     ordered_extent->file_offset +
			     ordered_extent->len - 1, &cached_state, GFP_NOFS);
out:
	if (root != root->fs_info->tree_root)
		btrfs_delalloc_release_metadata(inode, ordered_extent->len);
	if (trans) {
		if (nolock)
			btrfs_end_transaction_nolock(trans, root);
		else
			btrfs_end_transaction(trans, root);
	}

	if (ret)
		clear_extent_uptodate(io_tree, ordered_extent->file_offset,
				      ordered_extent->file_offset +
				      ordered_extent->len - 1, NULL, GFP_NOFS);

	/*
	 * This needs to be dont to make sure anybody waiting knows we are done
	 * upating everything for this ordered extent.
	 */
	btrfs_remove_ordered_extent(inode, ordered_extent);

	/* once for us */
	btrfs_put_ordered_extent(ordered_extent);
	/* once for the tree */
	btrfs_put_ordered_extent(ordered_extent);

	return ret;
}