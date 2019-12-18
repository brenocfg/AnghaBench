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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct btrfs_root {struct btrfs_root* log_root; } ;
struct btrfs_path {int keep_locks; int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; scalar_t__ offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  logged_trans; } ;

/* Variables and functions */
 int BTRFS_DIR_LOG_INDEX_KEY ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 scalar_t__ BTRFS_INODE_ITEM_KEY ; 
 void* BTRFS_XATTR_ITEM_KEY ; 
 int ENOMEM ; 
 int LOG_INODE_ALL ; 
 int LOG_INODE_EXISTS ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_commit_inode_delayed_items (struct btrfs_trans_handle*,struct inode*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 scalar_t__ btrfs_ino (struct inode*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_forward (struct btrfs_root*,struct btrfs_key*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_truncate_inode_items (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int copy_items (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct extent_buffer*,int,int,int) ; 
 int drop_objectid_items (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,scalar_t__,int) ; 
 int log_directory_changes (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,struct btrfs_path*,struct btrfs_path*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_log_inode(struct btrfs_trans_handle *trans,
			     struct btrfs_root *root, struct inode *inode,
			     int inode_only)
{
	struct btrfs_path *path;
	struct btrfs_path *dst_path;
	struct btrfs_key min_key;
	struct btrfs_key max_key;
	struct btrfs_root *log = root->log_root;
	struct extent_buffer *src = NULL;
	int err = 0;
	int ret;
	int nritems;
	int ins_start_slot = 0;
	int ins_nr;
	u64 ino = btrfs_ino(inode);

	log = root->log_root;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;
	dst_path = btrfs_alloc_path();
	if (!dst_path) {
		btrfs_free_path(path);
		return -ENOMEM;
	}

	min_key.objectid = ino;
	min_key.type = BTRFS_INODE_ITEM_KEY;
	min_key.offset = 0;

	max_key.objectid = ino;

	/* today the code can only do partial logging of directories */
	if (!S_ISDIR(inode->i_mode))
	    inode_only = LOG_INODE_ALL;

	if (inode_only == LOG_INODE_EXISTS || S_ISDIR(inode->i_mode))
		max_key.type = BTRFS_XATTR_ITEM_KEY;
	else
		max_key.type = (u8)-1;
	max_key.offset = (u64)-1;

	ret = btrfs_commit_inode_delayed_items(trans, inode);
	if (ret) {
		btrfs_free_path(path);
		btrfs_free_path(dst_path);
		return ret;
	}

	mutex_lock(&BTRFS_I(inode)->log_mutex);

	/*
	 * a brute force approach to making sure we get the most uptodate
	 * copies of everything.
	 */
	if (S_ISDIR(inode->i_mode)) {
		int max_key_type = BTRFS_DIR_LOG_INDEX_KEY;

		if (inode_only == LOG_INODE_EXISTS)
			max_key_type = BTRFS_XATTR_ITEM_KEY;
		ret = drop_objectid_items(trans, log, path, ino, max_key_type);
	} else {
		ret = btrfs_truncate_inode_items(trans, log, inode, 0, 0);
	}
	if (ret) {
		err = ret;
		goto out_unlock;
	}
	path->keep_locks = 1;

	while (1) {
		ins_nr = 0;
		ret = btrfs_search_forward(root, &min_key, &max_key,
					   path, 0, trans->transid);
		if (ret != 0)
			break;
again:
		/* note, ins_nr might be > 0 here, cleanup outside the loop */
		if (min_key.objectid != ino)
			break;
		if (min_key.type > max_key.type)
			break;

		src = path->nodes[0];
		if (ins_nr && ins_start_slot + ins_nr == path->slots[0]) {
			ins_nr++;
			goto next_slot;
		} else if (!ins_nr) {
			ins_start_slot = path->slots[0];
			ins_nr = 1;
			goto next_slot;
		}

		ret = copy_items(trans, log, dst_path, src, ins_start_slot,
				 ins_nr, inode_only);
		if (ret) {
			err = ret;
			goto out_unlock;
		}
		ins_nr = 1;
		ins_start_slot = path->slots[0];
next_slot:

		nritems = btrfs_header_nritems(path->nodes[0]);
		path->slots[0]++;
		if (path->slots[0] < nritems) {
			btrfs_item_key_to_cpu(path->nodes[0], &min_key,
					      path->slots[0]);
			goto again;
		}
		if (ins_nr) {
			ret = copy_items(trans, log, dst_path, src,
					 ins_start_slot,
					 ins_nr, inode_only);
			if (ret) {
				err = ret;
				goto out_unlock;
			}
			ins_nr = 0;
		}
		btrfs_release_path(path);

		if (min_key.offset < (u64)-1)
			min_key.offset++;
		else if (min_key.type < (u8)-1)
			min_key.type++;
		else if (min_key.objectid < (u64)-1)
			min_key.objectid++;
		else
			break;
	}
	if (ins_nr) {
		ret = copy_items(trans, log, dst_path, src,
				 ins_start_slot,
				 ins_nr, inode_only);
		if (ret) {
			err = ret;
			goto out_unlock;
		}
		ins_nr = 0;
	}
	WARN_ON(ins_nr);
	if (inode_only == LOG_INODE_ALL && S_ISDIR(inode->i_mode)) {
		btrfs_release_path(path);
		btrfs_release_path(dst_path);
		ret = log_directory_changes(trans, root, inode, path, dst_path);
		if (ret) {
			err = ret;
			goto out_unlock;
		}
	}
	BTRFS_I(inode)->logged_trans = trans->transid;
out_unlock:
	mutex_unlock(&BTRFS_I(inode)->log_mutex);

	btrfs_free_path(path);
	btrfs_free_path(dst_path);
	return err;
}