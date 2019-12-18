#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int s_time_gran; int /*<<< orphan*/  s_flags; struct dentry* s_root; int /*<<< orphan*/  s_xattr; int /*<<< orphan*/ * s_export_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_maxbytes; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct btrfs_key {scalar_t__ offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_root; int /*<<< orphan*/  fs_root; } ;
struct btrfs_fs_devices {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FIRST_FREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_INODE_ITEM_KEY ; 
 int /*<<< orphan*/  BTRFS_SUPER_MAGIC ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  MS_ACTIVE ; 
 int /*<<< orphan*/  MS_I_VERSION ; 
 int /*<<< orphan*/  MS_POSIXACL ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  btrfs_export_ops ; 
 struct inode* btrfs_iget (struct super_block*,struct btrfs_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* btrfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  btrfs_super_ops ; 
 int /*<<< orphan*/  btrfs_xattr_handlers ; 
 int /*<<< orphan*/  close_ctree (int /*<<< orphan*/ ) ; 
 struct dentry* d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int open_ctree (struct super_block*,struct btrfs_fs_devices*,char*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  save_mount_options (struct super_block*,void*) ; 

__attribute__((used)) static int btrfs_fill_super(struct super_block *sb,
			    struct btrfs_fs_devices *fs_devices,
			    void *data, int silent)
{
	struct inode *inode;
	struct dentry *root_dentry;
	struct btrfs_fs_info *fs_info = btrfs_sb(sb);
	struct btrfs_key key;
	int err;

	sb->s_maxbytes = MAX_LFS_FILESIZE;
	sb->s_magic = BTRFS_SUPER_MAGIC;
	sb->s_op = &btrfs_super_ops;
	sb->s_export_op = &btrfs_export_ops;
	sb->s_xattr = btrfs_xattr_handlers;
	sb->s_time_gran = 1;
#ifdef CONFIG_BTRFS_FS_POSIX_ACL
	sb->s_flags |= MS_POSIXACL;
#endif
	sb->s_flags |= MS_I_VERSION;
	err = open_ctree(sb, fs_devices, (char *)data);
	if (err) {
		printk("btrfs: open_ctree failed\n");
		return err;
	}

	key.objectid = BTRFS_FIRST_FREE_OBJECTID;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;
	inode = btrfs_iget(sb, &key, fs_info->fs_root, NULL);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto fail_close;
	}

	root_dentry = d_alloc_root(inode);
	if (!root_dentry) {
		iput(inode);
		err = -ENOMEM;
		goto fail_close;
	}

	sb->s_root = root_dentry;

	save_mount_options(sb, data);
	sb->s_flags |= MS_ACTIVE;
	return 0;

fail_close:
	close_ctree(fs_info->tree_root);
	return err;
}