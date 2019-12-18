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
typedef  int u64 ;
struct inode {int i_size; scalar_t__ i_nlink; int /*<<< orphan*/  i_mapping; } ;
struct btrfs_trans_handle {unsigned long blocks_used; struct btrfs_block_rsv* block_rsv; } ;
struct btrfs_root {int sectorsize; TYPE_1__* fs_info; struct btrfs_block_rsv* orphan_block_rsv; } ;
struct btrfs_block_rsv {int size; } ;
struct TYPE_4__ {int /*<<< orphan*/  runtime_flags; struct btrfs_root* root; } ;
struct TYPE_3__ {struct btrfs_block_rsv trans_block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_EXTENT_DATA_KEY ; 
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_ORDERED_DATA_CLOSE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_add_ordered_operation (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 struct btrfs_block_rsv* btrfs_alloc_block_rsv (struct btrfs_root*) ; 
 int btrfs_block_rsv_migrate (struct btrfs_block_rsv*,struct btrfs_block_rsv*,int) ; 
 int btrfs_block_rsv_refill (struct btrfs_root*,struct btrfs_block_rsv*,int) ; 
 int /*<<< orphan*/  btrfs_btree_balance_dirty (struct btrfs_root*,unsigned long) ; 
 int btrfs_calc_trunc_metadata_size (struct btrfs_root*,int) ; 
 int btrfs_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_free_block_rsv (struct btrfs_root*,struct btrfs_block_rsv*) ; 
 int /*<<< orphan*/  btrfs_ordered_update_i_size (struct inode*,int,int /*<<< orphan*/ *) ; 
 int btrfs_orphan_add (struct btrfs_trans_handle*,struct inode*) ; 
 int btrfs_orphan_del (struct btrfs_trans_handle*,struct inode*) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_truncate_inode_items (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,int,int /*<<< orphan*/ ) ; 
 int btrfs_truncate_page (int /*<<< orphan*/ ,int) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  btrfs_wait_ordered_range (struct inode*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_truncate(struct inode *inode)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_block_rsv *rsv;
	int ret;
	int err = 0;
	struct btrfs_trans_handle *trans;
	unsigned long nr;
	u64 mask = root->sectorsize - 1;
	u64 min_size = btrfs_calc_trunc_metadata_size(root, 1);

	ret = btrfs_truncate_page(inode->i_mapping, inode->i_size);
	if (ret)
		return ret;

	btrfs_wait_ordered_range(inode, inode->i_size & (~mask), (u64)-1);
	btrfs_ordered_update_i_size(inode, inode->i_size, NULL);

	/*
	 * Yes ladies and gentelment, this is indeed ugly.  The fact is we have
	 * 3 things going on here
	 *
	 * 1) We need to reserve space for our orphan item and the space to
	 * delete our orphan item.  Lord knows we don't want to have a dangling
	 * orphan item because we didn't reserve space to remove it.
	 *
	 * 2) We need to reserve space to update our inode.
	 *
	 * 3) We need to have something to cache all the space that is going to
	 * be free'd up by the truncate operation, but also have some slack
	 * space reserved in case it uses space during the truncate (thank you
	 * very much snapshotting).
	 *
	 * And we need these to all be seperate.  The fact is we can use alot of
	 * space doing the truncate, and we have no earthly idea how much space
	 * we will use, so we need the truncate reservation to be seperate so it
	 * doesn't end up using space reserved for updating the inode or
	 * removing the orphan item.  We also need to be able to stop the
	 * transaction and start a new one, which means we need to be able to
	 * update the inode several times, and we have no idea of knowing how
	 * many times that will be, so we can't just reserve 1 item for the
	 * entirety of the opration, so that has to be done seperately as well.
	 * Then there is the orphan item, which does indeed need to be held on
	 * to for the whole operation, and we need nobody to touch this reserved
	 * space except the orphan code.
	 *
	 * So that leaves us with
	 *
	 * 1) root->orphan_block_rsv - for the orphan deletion.
	 * 2) rsv - for the truncate reservation, which we will steal from the
	 * transaction reservation.
	 * 3) fs_info->trans_block_rsv - this will have 1 items worth left for
	 * updating the inode.
	 */
	rsv = btrfs_alloc_block_rsv(root);
	if (!rsv)
		return -ENOMEM;
	rsv->size = min_size;

	/*
	 * 1 for the truncate slack space
	 * 1 for the orphan item we're going to add
	 * 1 for the orphan item deletion
	 * 1 for updating the inode.
	 */
	trans = btrfs_start_transaction(root, 4);
	if (IS_ERR(trans)) {
		err = PTR_ERR(trans);
		goto out;
	}

	/* Migrate the slack space for the truncate to our reserve */
	ret = btrfs_block_rsv_migrate(&root->fs_info->trans_block_rsv, rsv,
				      min_size);
	BUG_ON(ret);

	ret = btrfs_orphan_add(trans, inode);
	if (ret) {
		btrfs_end_transaction(trans, root);
		goto out;
	}

	/*
	 * setattr is responsible for setting the ordered_data_close flag,
	 * but that is only tested during the last file release.  That
	 * could happen well after the next commit, leaving a great big
	 * window where new writes may get lost if someone chooses to write
	 * to this file after truncating to zero
	 *
	 * The inode doesn't have any dirty data here, and so if we commit
	 * this is a noop.  If someone immediately starts writing to the inode
	 * it is very likely we'll catch some of their writes in this
	 * transaction, and the commit will find this file on the ordered
	 * data list with good things to send down.
	 *
	 * This is a best effort solution, there is still a window where
	 * using truncate to replace the contents of the file will
	 * end up with a zero length file after a crash.
	 */
	if (inode->i_size == 0 && test_bit(BTRFS_INODE_ORDERED_DATA_CLOSE,
					   &BTRFS_I(inode)->runtime_flags))
		btrfs_add_ordered_operation(trans, root, inode);

	while (1) {
		ret = btrfs_block_rsv_refill(root, rsv, min_size);
		if (ret) {
			/*
			 * This can only happen with the original transaction we
			 * started above, every other time we shouldn't have a
			 * transaction started yet.
			 */
			if (ret == -EAGAIN)
				goto end_trans;
			err = ret;
			break;
		}

		if (!trans) {
			/* Just need the 1 for updating the inode */
			trans = btrfs_start_transaction(root, 1);
			if (IS_ERR(trans)) {
				ret = err = PTR_ERR(trans);
				trans = NULL;
				break;
			}
		}

		trans->block_rsv = rsv;

		ret = btrfs_truncate_inode_items(trans, root, inode,
						 inode->i_size,
						 BTRFS_EXTENT_DATA_KEY);
		if (ret != -EAGAIN) {
			err = ret;
			break;
		}

		trans->block_rsv = &root->fs_info->trans_block_rsv;
		ret = btrfs_update_inode(trans, root, inode);
		if (ret) {
			err = ret;
			break;
		}
end_trans:
		nr = trans->blocks_used;
		btrfs_end_transaction(trans, root);
		trans = NULL;
		btrfs_btree_balance_dirty(root, nr);
	}

	if (ret == 0 && inode->i_nlink > 0) {
		trans->block_rsv = root->orphan_block_rsv;
		ret = btrfs_orphan_del(trans, inode);
		if (ret)
			err = ret;
	} else if (ret && inode->i_nlink > 0) {
		/*
		 * Failed to do the truncate, remove us from the in memory
		 * orphan list.
		 */
		ret = btrfs_orphan_del(NULL, inode);
	}

	if (trans) {
		trans->block_rsv = &root->fs_info->trans_block_rsv;
		ret = btrfs_update_inode(trans, root, inode);
		if (ret && !err)
			err = ret;

		nr = trans->blocks_used;
		ret = btrfs_end_transaction(trans, root);
		btrfs_btree_balance_dirty(root, nr);
	}

out:
	btrfs_free_block_rsv(root, rsv);

	if (ret && !err)
		err = ret;

	return err;
}