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
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; scalar_t__ i_size; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_2__ root_key; TYPE_1__* fs_info; } ;
struct btrfs_path {int /*<<< orphan*/ * slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ type; scalar_t__ objectid; scalar_t__ offset; } ;
struct btrfs_dir_item {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tree_root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_ROOT_ITEM_KEY ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR_OR_NULL (struct btrfs_dir_item*) ; 
 int PTR_ERR (struct btrfs_dir_item*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_del_root_ref (struct btrfs_trans_handle*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,char const*,int) ; 
 int btrfs_delete_delayed_dir_index (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,scalar_t__) ; 
 int btrfs_delete_one_dir_name (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_dir_item*) ; 
 int /*<<< orphan*/  btrfs_dir_item_key_to_cpu (struct extent_buffer*,struct btrfs_dir_item*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_i_size_write (struct inode*,scalar_t__) ; 
 scalar_t__ btrfs_ino (struct inode*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 struct btrfs_dir_item* btrfs_lookup_dir_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,scalar_t__,char const*,int,int) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 struct btrfs_dir_item* btrfs_search_dir_index_item (struct btrfs_root*,struct btrfs_path*,scalar_t__,char const*,int) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 

int btrfs_unlink_subvol(struct btrfs_trans_handle *trans,
			struct btrfs_root *root,
			struct inode *dir, u64 objectid,
			const char *name, int name_len)
{
	struct btrfs_path *path;
	struct extent_buffer *leaf;
	struct btrfs_dir_item *di;
	struct btrfs_key key;
	u64 index;
	int ret;
	u64 dir_ino = btrfs_ino(dir);

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	di = btrfs_lookup_dir_item(trans, root, path, dir_ino,
				   name, name_len, -1);
	if (IS_ERR_OR_NULL(di)) {
		if (!di)
			ret = -ENOENT;
		else
			ret = PTR_ERR(di);
		goto out;
	}

	leaf = path->nodes[0];
	btrfs_dir_item_key_to_cpu(leaf, di, &key);
	WARN_ON(key.type != BTRFS_ROOT_ITEM_KEY || key.objectid != objectid);
	ret = btrfs_delete_one_dir_name(trans, root, path, di);
	if (ret) {
		btrfs_abort_transaction(trans, root, ret);
		goto out;
	}
	btrfs_release_path(path);

	ret = btrfs_del_root_ref(trans, root->fs_info->tree_root,
				 objectid, root->root_key.objectid,
				 dir_ino, &index, name, name_len);
	if (ret < 0) {
		if (ret != -ENOENT) {
			btrfs_abort_transaction(trans, root, ret);
			goto out;
		}
		di = btrfs_search_dir_index_item(root, path, dir_ino,
						 name, name_len);
		if (IS_ERR_OR_NULL(di)) {
			if (!di)
				ret = -ENOENT;
			else
				ret = PTR_ERR(di);
			btrfs_abort_transaction(trans, root, ret);
			goto out;
		}

		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		btrfs_release_path(path);
		index = key.offset;
	}
	btrfs_release_path(path);

	ret = btrfs_delete_delayed_dir_index(trans, root, dir, index);
	if (ret) {
		btrfs_abort_transaction(trans, root, ret);
		goto out;
	}

	btrfs_i_size_write(dir, dir->i_size - name_len * 2);
	inode_inc_iversion(dir);
	dir->i_mtime = dir->i_ctime = CURRENT_TIME;
	ret = btrfs_update_inode(trans, root, dir);
	if (ret)
		btrfs_abort_transaction(trans, root, ret);
out:
	btrfs_free_path(path);
	return ret;
}