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
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; scalar_t__ i_size; } ;
struct btrfs_trans_handle {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_2__ root_key; TYPE_1__* fs_info; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_6__ {struct btrfs_root* root; } ;
struct TYPE_4__ {int /*<<< orphan*/  tree_root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_ITEM_KEY ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EEXIST ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 int btrfs_add_root_ref (struct btrfs_trans_handle*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,char const*,int) ; 
 int btrfs_del_inode_ref (struct btrfs_trans_handle*,struct btrfs_root*,char const*,int,scalar_t__,scalar_t__,scalar_t__*) ; 
 int btrfs_del_root_ref (struct btrfs_trans_handle*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,char const*,int) ; 
 int /*<<< orphan*/  btrfs_i_size_write (struct inode*,scalar_t__) ; 
 scalar_t__ btrfs_ino (struct inode*) ; 
 int /*<<< orphan*/  btrfs_inode_type (struct inode*) ; 
 int btrfs_insert_dir_item (struct btrfs_trans_handle*,struct btrfs_root*,char const*,int,struct inode*,struct btrfs_key*,int /*<<< orphan*/ ,scalar_t__) ; 
 int btrfs_insert_inode_ref (struct btrfs_trans_handle*,struct btrfs_root*,char const*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_set_key_type (struct btrfs_key*,int /*<<< orphan*/ ) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 int /*<<< orphan*/  memcpy (struct btrfs_key*,TYPE_2__*,int) ; 
 scalar_t__ unlikely (int) ; 

int btrfs_add_link(struct btrfs_trans_handle *trans,
		   struct inode *parent_inode, struct inode *inode,
		   const char *name, int name_len, int add_backref, u64 index)
{
	int ret = 0;
	struct btrfs_key key;
	struct btrfs_root *root = BTRFS_I(parent_inode)->root;
	u64 ino = btrfs_ino(inode);
	u64 parent_ino = btrfs_ino(parent_inode);

	if (unlikely(ino == BTRFS_FIRST_FREE_OBJECTID)) {
		memcpy(&key, &BTRFS_I(inode)->root->root_key, sizeof(key));
	} else {
		key.objectid = ino;
		btrfs_set_key_type(&key, BTRFS_INODE_ITEM_KEY);
		key.offset = 0;
	}

	if (unlikely(ino == BTRFS_FIRST_FREE_OBJECTID)) {
		ret = btrfs_add_root_ref(trans, root->fs_info->tree_root,
					 key.objectid, root->root_key.objectid,
					 parent_ino, index, name, name_len);
	} else if (add_backref) {
		ret = btrfs_insert_inode_ref(trans, root, name, name_len, ino,
					     parent_ino, index);
	}

	/* Nothing to clean up yet */
	if (ret)
		return ret;

	ret = btrfs_insert_dir_item(trans, root, name, name_len,
				    parent_inode, &key,
				    btrfs_inode_type(inode), index);
	if (ret == -EEXIST)
		goto fail_dir_item;
	else if (ret) {
		btrfs_abort_transaction(trans, root, ret);
		return ret;
	}

	btrfs_i_size_write(parent_inode, parent_inode->i_size +
			   name_len * 2);
	inode_inc_iversion(parent_inode);
	parent_inode->i_mtime = parent_inode->i_ctime = CURRENT_TIME;
	ret = btrfs_update_inode(trans, root, parent_inode);
	if (ret)
		btrfs_abort_transaction(trans, root, ret);
	return ret;

fail_dir_item:
	if (unlikely(ino == BTRFS_FIRST_FREE_OBJECTID)) {
		u64 local_index;
		int err;
		err = btrfs_del_root_ref(trans, root->fs_info->tree_root,
				 key.objectid, root->root_key.objectid,
				 parent_ino, &local_index, name, name_len);

	} else if (add_backref) {
		u64 local_index;
		int err;

		err = btrfs_del_inode_ref(trans, root, name, name_len,
					  ino, parent_ino, &local_index);
	}
	return ret;
}