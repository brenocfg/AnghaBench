#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_3__* i_sb; } ;
struct TYPE_6__ {scalar_t__ len; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/ * d_op; } ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; } ;
struct TYPE_9__ {struct btrfs_root* root; } ;
struct TYPE_8__ {int s_flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  cleanup_work_sem; int /*<<< orphan*/  subvol_srcu; } ;

/* Variables and functions */
 TYPE_5__* BTRFS_I (struct inode*) ; 
 scalar_t__ BTRFS_INODE_ITEM_KEY ; 
 scalar_t__ BTRFS_NAME_LEN ; 
 scalar_t__ BTRFS_ROOT_ITEM_KEY ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  btrfs_dentry_operations ; 
 struct inode* btrfs_iget (TYPE_3__*,struct btrfs_key*,struct btrfs_root*,int /*<<< orphan*/ *) ; 
 int btrfs_inode_by_name (struct inode*,struct dentry*,struct btrfs_key*) ; 
 int btrfs_orphan_cleanup (struct btrfs_root*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int fixup_tree_root_location (struct btrfs_root*,struct inode*,struct dentry*,struct btrfs_key*,struct btrfs_root**) ; 
 struct inode* new_simple_dir (TYPE_3__*,struct btrfs_key*,struct btrfs_root*) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct inode *btrfs_lookup_dentry(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode;
	struct btrfs_root *root = BTRFS_I(dir)->root;
	struct btrfs_root *sub_root = root;
	struct btrfs_key location;
	int index;
	int ret;

	dentry->d_op = &btrfs_dentry_operations;

	if (dentry->d_name.len > BTRFS_NAME_LEN)
		return ERR_PTR(-ENAMETOOLONG);

	ret = btrfs_inode_by_name(dir, dentry, &location);

	if (ret < 0)
		return ERR_PTR(ret);

	if (location.objectid == 0)
		return NULL;

	if (location.type == BTRFS_INODE_ITEM_KEY) {
		inode = btrfs_iget(dir->i_sb, &location, root, NULL);
		return inode;
	}

	BUG_ON(location.type != BTRFS_ROOT_ITEM_KEY);

	index = srcu_read_lock(&root->fs_info->subvol_srcu);
	ret = fixup_tree_root_location(root, dir, dentry,
				       &location, &sub_root);
	if (ret < 0) {
		if (ret != -ENOENT)
			inode = ERR_PTR(ret);
		else
			inode = new_simple_dir(dir->i_sb, &location, sub_root);
	} else {
		inode = btrfs_iget(dir->i_sb, &location, sub_root, NULL);
	}
	srcu_read_unlock(&root->fs_info->subvol_srcu, index);

	if (!IS_ERR(inode) && root != sub_root) {
		down_read(&root->fs_info->cleanup_work_sem);
		if (!(inode->i_sb->s_flags & MS_RDONLY))
			ret = btrfs_orphan_cleanup(sub_root);
		up_read(&root->fs_info->cleanup_work_sem);
		if (ret)
			inode = ERR_PTR(ret);
	}

	return inode;
}