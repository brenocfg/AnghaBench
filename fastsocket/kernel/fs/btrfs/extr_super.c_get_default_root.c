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
typedef  void* u64 ;
struct super_block {TYPE_1__* s_root; } ;
struct inode {int /*<<< orphan*/  root_item; } ;
struct dentry {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  root_item; } ;
struct btrfs_path {int leave_spinning; int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {void* offset; int /*<<< orphan*/  type; void* objectid; } ;
struct btrfs_fs_info {struct inode* fs_root; int /*<<< orphan*/  super_copy; struct inode* tree_root; } ;
struct btrfs_dir_item {int /*<<< orphan*/  root_item; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 void* BTRFS_FIRST_FREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_INODE_ITEM_KEY ; 
 int /*<<< orphan*/  BTRFS_ROOT_ITEM_KEY ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_dir_item_key_to_cpu (int /*<<< orphan*/ ,struct inode*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 struct inode* btrfs_iget (struct super_block*,struct btrfs_key*,struct inode*,int*) ; 
 struct inode* btrfs_lookup_dir_item (int /*<<< orphan*/ *,struct inode*,struct btrfs_path*,void*,char*,int,int /*<<< orphan*/ ) ; 
 struct inode* btrfs_read_fs_root_no_name (struct btrfs_fs_info*,struct btrfs_key*) ; 
 void* btrfs_root_dirid (int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_root_refs (int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* btrfs_sb (struct super_block*) ; 
 void* btrfs_super_root_dir (int /*<<< orphan*/ ) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 struct dentry* dget (TYPE_1__*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static struct dentry *get_default_root(struct super_block *sb,
				       u64 subvol_objectid)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(sb);
	struct btrfs_root *root = fs_info->tree_root;
	struct btrfs_root *new_root;
	struct btrfs_dir_item *di;
	struct btrfs_path *path;
	struct btrfs_key location;
	struct inode *inode;
	u64 dir_id;
	int new = 0;

	/*
	 * We have a specific subvol we want to mount, just setup location and
	 * go look up the root.
	 */
	if (subvol_objectid) {
		location.objectid = subvol_objectid;
		location.type = BTRFS_ROOT_ITEM_KEY;
		location.offset = (u64)-1;
		goto find_root;
	}

	path = btrfs_alloc_path();
	if (!path)
		return ERR_PTR(-ENOMEM);
	path->leave_spinning = 1;

	/*
	 * Find the "default" dir item which points to the root item that we
	 * will mount by default if we haven't been given a specific subvolume
	 * to mount.
	 */
	dir_id = btrfs_super_root_dir(fs_info->super_copy);
	di = btrfs_lookup_dir_item(NULL, root, path, dir_id, "default", 7, 0);
	if (IS_ERR(di)) {
		btrfs_free_path(path);
		return ERR_CAST(di);
	}
	if (!di) {
		/*
		 * Ok the default dir item isn't there.  This is weird since
		 * it's always been there, but don't freak out, just try and
		 * mount to root most subvolume.
		 */
		btrfs_free_path(path);
		dir_id = BTRFS_FIRST_FREE_OBJECTID;
		new_root = fs_info->fs_root;
		goto setup_root;
	}

	btrfs_dir_item_key_to_cpu(path->nodes[0], di, &location);
	btrfs_free_path(path);

find_root:
	new_root = btrfs_read_fs_root_no_name(fs_info, &location);
	if (IS_ERR(new_root))
		return ERR_CAST(new_root);

	if (btrfs_root_refs(&new_root->root_item) == 0)
		return ERR_PTR(-ENOENT);

	dir_id = btrfs_root_dirid(&new_root->root_item);
setup_root:
	location.objectid = dir_id;
	location.type = BTRFS_INODE_ITEM_KEY;
	location.offset = 0;

	inode = btrfs_iget(sb, &location, new_root, &new);
	if (IS_ERR(inode))
		return ERR_CAST(inode);

	/*
	 * If we're just mounting the root most subvol put the inode and return
	 * a reference to the dentry.  We will have already gotten a reference
	 * to the inode in btrfs_fill_super so we're good to go.
	 */
	if (!new && sb->s_root->d_inode == inode) {
		iput(inode);
		return dget(sb->s_root);
	}

	return d_obtain_alias(inode);
}