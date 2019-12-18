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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  bytes_reserved; struct btrfs_block_rsv* block_rsv; int /*<<< orphan*/  transid; } ;
struct TYPE_4__ {scalar_t__ objectid; } ;
struct btrfs_root {scalar_t__ cached; TYPE_2__* fs_info; int /*<<< orphan*/  cache_lock; int /*<<< orphan*/  root_item; TYPE_1__ root_key; struct btrfs_free_space_ctl* free_ino_ctl; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_free_space_ctl {int free_extents; int total_bitmaps; int /*<<< orphan*/  tree_lock; } ;
struct btrfs_free_space {int dummy; } ;
struct btrfs_block_rsv {int dummy; } ;
struct TYPE_6__ {scalar_t__ generation; } ;
struct TYPE_5__ {struct btrfs_block_rsv trans_block_rsv; struct btrfs_root* tree_root; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 scalar_t__ BTRFS_CACHE_FINISHED ; 
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 scalar_t__ BTRFS_FS_TREE_OBJECTID ; 
 TYPE_3__* BTRFS_I (struct inode*) ; 
 scalar_t__ BTRFS_LAST_FREE_OBJECTID ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INODE_MAP_CACHE ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PAGE_CACHE_SIZE ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_block_rsv_add_noflush (struct btrfs_root*,struct btrfs_block_rsv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_block_rsv_release (struct btrfs_root*,struct btrfs_block_rsv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_calc_trans_metadata_size (struct btrfs_root*,int) ; 
 int /*<<< orphan*/  btrfs_delalloc_release_space (struct inode*,int) ; 
 int btrfs_delalloc_reserve_space (struct inode*,int) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_free_reserved_data_space (struct inode*,int) ; 
 int btrfs_prealloc_file_range_trans (struct inode*,struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_root_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int btrfs_truncate_free_space_cache (struct btrfs_root*,struct btrfs_trans_handle*,struct btrfs_path*,struct inode*) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int btrfs_write_out_ino_cache (struct btrfs_root*,struct btrfs_trans_handle*,struct btrfs_path*) ; 
 int create_free_ino_inode (struct btrfs_root*,struct btrfs_trans_handle*,struct btrfs_path*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* lookup_free_ino_inode (struct btrfs_root*,struct btrfs_path*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int btrfs_save_ino_cache(struct btrfs_root *root,
			 struct btrfs_trans_handle *trans)
{
	struct btrfs_free_space_ctl *ctl = root->free_ino_ctl;
	struct btrfs_path *path;
	struct inode *inode;
	struct btrfs_block_rsv *rsv;
	u64 num_bytes;
	u64 alloc_hint = 0;
	int ret;
	int prealloc;
	bool retry = false;

	/* only fs tree and subvol/snap needs ino cache */
	if (root->root_key.objectid != BTRFS_FS_TREE_OBJECTID &&
	    (root->root_key.objectid < BTRFS_FIRST_FREE_OBJECTID ||
	     root->root_key.objectid > BTRFS_LAST_FREE_OBJECTID))
		return 0;

	/* Don't save inode cache if we are deleting this root */
	if (btrfs_root_refs(&root->root_item) == 0 &&
	    root != root->fs_info->tree_root)
		return 0;

	if (!btrfs_test_opt(root, INODE_MAP_CACHE))
		return 0;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	rsv = trans->block_rsv;
	trans->block_rsv = &root->fs_info->trans_block_rsv;

	num_bytes = trans->bytes_reserved;
	/*
	 * 1 item for inode item insertion if need
	 * 3 items for inode item update (in the worst case)
	 * 1 item for free space object
	 * 3 items for pre-allocation
	 */
	trans->bytes_reserved = btrfs_calc_trans_metadata_size(root, 8);
	ret = btrfs_block_rsv_add_noflush(root, trans->block_rsv,
					  trans->bytes_reserved);
	if (ret)
		goto out;
	trace_btrfs_space_reservation(root->fs_info, "ino_cache",
				      trans->transid, trans->bytes_reserved, 1);
again:
	inode = lookup_free_ino_inode(root, path);
	if (IS_ERR(inode) && (PTR_ERR(inode) != -ENOENT || retry)) {
		ret = PTR_ERR(inode);
		goto out_release;
	}

	if (IS_ERR(inode)) {
		BUG_ON(retry); /* Logic error */
		retry = true;

		ret = create_free_ino_inode(root, trans, path);
		if (ret)
			goto out_release;
		goto again;
	}

	BTRFS_I(inode)->generation = 0;
	ret = btrfs_update_inode(trans, root, inode);
	if (ret) {
		btrfs_abort_transaction(trans, root, ret);
		goto out_put;
	}

	if (i_size_read(inode) > 0) {
		ret = btrfs_truncate_free_space_cache(root, trans, path, inode);
		if (ret) {
			btrfs_abort_transaction(trans, root, ret);
			goto out_put;
		}
	}

	spin_lock(&root->cache_lock);
	if (root->cached != BTRFS_CACHE_FINISHED) {
		ret = -1;
		spin_unlock(&root->cache_lock);
		goto out_put;
	}
	spin_unlock(&root->cache_lock);

	spin_lock(&ctl->tree_lock);
	prealloc = sizeof(struct btrfs_free_space) * ctl->free_extents;
	prealloc = ALIGN(prealloc, PAGE_CACHE_SIZE);
	prealloc += ctl->total_bitmaps * PAGE_CACHE_SIZE;
	spin_unlock(&ctl->tree_lock);

	/* Just to make sure we have enough space */
	prealloc += 8 * PAGE_CACHE_SIZE;

	ret = btrfs_delalloc_reserve_space(inode, prealloc);
	if (ret)
		goto out_put;

	ret = btrfs_prealloc_file_range_trans(inode, trans, 0, 0, prealloc,
					      prealloc, prealloc, &alloc_hint);
	if (ret) {
		btrfs_delalloc_release_space(inode, prealloc);
		goto out_put;
	}
	btrfs_free_reserved_data_space(inode, prealloc);

	ret = btrfs_write_out_ino_cache(root, trans, path);
out_put:
	iput(inode);
out_release:
	trace_btrfs_space_reservation(root->fs_info, "ino_cache",
				      trans->transid, trans->bytes_reserved, 0);
	btrfs_block_rsv_release(root, trans->block_rsv, trans->bytes_reserved);
out:
	trans->block_rsv = rsv;
	trans->bytes_reserved = num_bytes;

	btrfs_free_path(path);
	return ret;
}