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
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; struct inode* d_inode; } ;
struct btrfs_trans_handle {int /*<<< orphan*/ * block_rsv; int /*<<< orphan*/  bytes_reserved; } ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct btrfs_path {int skip_locking; int search_commit_root; int /*<<< orphan*/ * nodes; } ;
struct btrfs_inode_ref {int /*<<< orphan*/ * block_rsv; int /*<<< orphan*/  bytes_reserved; } ;
struct btrfs_dir_item {int /*<<< orphan*/ * block_rsv; int /*<<< orphan*/  bytes_reserved; } ;
struct TYPE_6__ {int /*<<< orphan*/  location; struct btrfs_root* root; } ;
struct TYPE_5__ {int /*<<< orphan*/  global_block_rsv; scalar_t__ enospc_unlink; } ;

/* Variables and functions */
 scalar_t__ BTRFS_EMPTY_SUBVOL_DIR_OBJECTID ; 
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct btrfs_trans_handle* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_block_rsv_migrate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 scalar_t__ btrfs_ino (struct inode*) ; 
 scalar_t__ btrfs_inode_ref_index (int /*<<< orphan*/ ,struct btrfs_trans_handle*) ; 
 struct btrfs_trans_handle* btrfs_lookup_dir_index_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_trans_handle* btrfs_lookup_dir_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_lookup_file_extent (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int btrfs_lookup_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct btrfs_trans_handle* btrfs_lookup_inode_ref (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int) ; 
 scalar_t__ check_path_shared (struct btrfs_root*,struct btrfs_path*) ; 
 scalar_t__ xchg (scalar_t__*,int) ; 

__attribute__((used)) static struct btrfs_trans_handle *__unlink_start_trans(struct inode *dir,
						       struct dentry *dentry)
{
	struct btrfs_trans_handle *trans;
	struct btrfs_root *root = BTRFS_I(dir)->root;
	struct btrfs_path *path;
	struct btrfs_inode_ref *ref;
	struct btrfs_dir_item *di;
	struct inode *inode = dentry->d_inode;
	u64 index;
	int check_link = 1;
	int err = -ENOSPC;
	int ret;
	u64 ino = btrfs_ino(inode);
	u64 dir_ino = btrfs_ino(dir);

	/*
	 * 1 for the possible orphan item
	 * 1 for the dir item
	 * 1 for the dir index
	 * 1 for the inode ref
	 * 1 for the inode ref in the tree log
	 * 2 for the dir entries in the log
	 * 1 for the inode
	 */
	trans = btrfs_start_transaction(root, 8);
	if (!IS_ERR(trans) || PTR_ERR(trans) != -ENOSPC)
		return trans;

	if (ino == BTRFS_EMPTY_SUBVOL_DIR_OBJECTID)
		return ERR_PTR(-ENOSPC);

	/* check if there is someone else holds reference */
	if (S_ISDIR(inode->i_mode) && atomic_read(&inode->i_count) > 1)
		return ERR_PTR(-ENOSPC);

	if (atomic_read(&inode->i_count) > 2)
		return ERR_PTR(-ENOSPC);

	if (xchg(&root->fs_info->enospc_unlink, 1))
		return ERR_PTR(-ENOSPC);

	path = btrfs_alloc_path();
	if (!path) {
		root->fs_info->enospc_unlink = 0;
		return ERR_PTR(-ENOMEM);
	}

	/* 1 for the orphan item */
	trans = btrfs_start_transaction(root, 1);
	if (IS_ERR(trans)) {
		btrfs_free_path(path);
		root->fs_info->enospc_unlink = 0;
		return trans;
	}

	path->skip_locking = 1;
	path->search_commit_root = 1;

	ret = btrfs_lookup_inode(trans, root, path,
				&BTRFS_I(dir)->location, 0);
	if (ret < 0) {
		err = ret;
		goto out;
	}
	if (ret == 0) {
		if (check_path_shared(root, path))
			goto out;
	} else {
		check_link = 0;
	}
	btrfs_release_path(path);

	ret = btrfs_lookup_inode(trans, root, path,
				&BTRFS_I(inode)->location, 0);
	if (ret < 0) {
		err = ret;
		goto out;
	}
	if (ret == 0) {
		if (check_path_shared(root, path))
			goto out;
	} else {
		check_link = 0;
	}
	btrfs_release_path(path);

	if (ret == 0 && S_ISREG(inode->i_mode)) {
		ret = btrfs_lookup_file_extent(trans, root, path,
					       ino, (u64)-1, 0);
		if (ret < 0) {
			err = ret;
			goto out;
		}
		BUG_ON(ret == 0); /* Corruption */
		if (check_path_shared(root, path))
			goto out;
		btrfs_release_path(path);
	}

	if (!check_link) {
		err = 0;
		goto out;
	}

	di = btrfs_lookup_dir_item(trans, root, path, dir_ino,
				dentry->d_name.name, dentry->d_name.len, 0);
	if (IS_ERR(di)) {
		err = PTR_ERR(di);
		goto out;
	}
	if (di) {
		if (check_path_shared(root, path))
			goto out;
	} else {
		err = 0;
		goto out;
	}
	btrfs_release_path(path);

	ref = btrfs_lookup_inode_ref(trans, root, path,
				dentry->d_name.name, dentry->d_name.len,
				ino, dir_ino, 0);
	if (IS_ERR(ref)) {
		err = PTR_ERR(ref);
		goto out;
	}
	BUG_ON(!ref); /* Logic error */
	if (check_path_shared(root, path))
		goto out;
	index = btrfs_inode_ref_index(path->nodes[0], ref);
	btrfs_release_path(path);

	/*
	 * This is a commit root search, if we can lookup inode item and other
	 * relative items in the commit root, it means the transaction of
	 * dir/file creation has been committed, and the dir index item that we
	 * delay to insert has also been inserted into the commit root. So
	 * we needn't worry about the delayed insertion of the dir index item
	 * here.
	 */
	di = btrfs_lookup_dir_index_item(trans, root, path, dir_ino, index,
				dentry->d_name.name, dentry->d_name.len, 0);
	if (IS_ERR(di)) {
		err = PTR_ERR(di);
		goto out;
	}
	BUG_ON(ret == -ENOENT);
	if (check_path_shared(root, path))
		goto out;

	err = 0;
out:
	btrfs_free_path(path);
	/* Migrate the orphan reservation over */
	if (!err)
		err = btrfs_block_rsv_migrate(trans->block_rsv,
				&root->fs_info->global_block_rsv,
				trans->bytes_reserved);

	if (err) {
		btrfs_end_transaction(trans, root);
		root->fs_info->enospc_unlink = 0;
		return ERR_PTR(err);
	}

	trans->block_rsv = &root->fs_info->global_block_rsv;
	return trans;
}