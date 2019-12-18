#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_2__ root_key; TYPE_1__* fs_info; int /*<<< orphan*/  orphan_lock; int /*<<< orphan*/  orphan_inodes; int /*<<< orphan*/  orphan_item_inserted; struct btrfs_block_rsv* orphan_block_rsv; } ;
struct btrfs_block_rsv {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  runtime_flags; struct btrfs_root* root; } ;
struct TYPE_4__ {struct btrfs_root* tree_root; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_HAS_ORPHAN_ITEM ; 
 int /*<<< orphan*/  BTRFS_INODE_ORPHAN_META_RESERVED ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 struct btrfs_block_rsv* btrfs_alloc_block_rsv (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_free_block_rsv (struct btrfs_root*,struct btrfs_block_rsv*) ; 
 int /*<<< orphan*/  btrfs_ino (struct inode*) ; 
 int btrfs_insert_orphan_item (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int btrfs_orphan_reserve_metadata (struct btrfs_trans_handle*,struct inode*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,int) ; 

int btrfs_orphan_add(struct btrfs_trans_handle *trans, struct inode *inode)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_block_rsv *block_rsv = NULL;
	int reserve = 0;
	int insert = 0;
	int ret;

	if (!root->orphan_block_rsv) {
		block_rsv = btrfs_alloc_block_rsv(root);
		if (!block_rsv)
			return -ENOMEM;
	}

	spin_lock(&root->orphan_lock);
	if (!root->orphan_block_rsv) {
		root->orphan_block_rsv = block_rsv;
	} else if (block_rsv) {
		btrfs_free_block_rsv(root, block_rsv);
		block_rsv = NULL;
	}

	if (!test_and_set_bit(BTRFS_INODE_HAS_ORPHAN_ITEM,
			      &BTRFS_I(inode)->runtime_flags)) {
#if 0
		/*
		 * For proper ENOSPC handling, we should do orphan
		 * cleanup when mounting. But this introduces backward
		 * compatibility issue.
		 */
		if (!xchg(&root->orphan_item_inserted, 1))
			insert = 2;
		else
			insert = 1;
#endif
		insert = 1;
		atomic_dec(&root->orphan_inodes);
	}

	if (!test_and_set_bit(BTRFS_INODE_ORPHAN_META_RESERVED,
			      &BTRFS_I(inode)->runtime_flags))
		reserve = 1;
	spin_unlock(&root->orphan_lock);

	/* grab metadata reservation from transaction handle */
	if (reserve) {
		ret = btrfs_orphan_reserve_metadata(trans, inode);
		BUG_ON(ret); /* -ENOSPC in reservation; Logic error? JDM */
	}

	/* insert an orphan item to track this unlinked/truncated file */
	if (insert >= 1) {
		ret = btrfs_insert_orphan_item(trans, root, btrfs_ino(inode));
		if (ret && ret != -EEXIST) {
			clear_bit(BTRFS_INODE_HAS_ORPHAN_ITEM,
				  &BTRFS_I(inode)->runtime_flags);
			btrfs_abort_transaction(trans, root, ret);
			return ret;
		}
		ret = 0;
	}

	/* insert an orphan item to track subvolume contains orphan files */
	if (insert >= 2) {
		ret = btrfs_insert_orphan_item(trans, root->fs_info->tree_root,
					       root->root_key.objectid);
		if (ret && ret != -EEXIST) {
			btrfs_abort_transaction(trans, root, ret);
			return ret;
		}
	}
	return 0;
}