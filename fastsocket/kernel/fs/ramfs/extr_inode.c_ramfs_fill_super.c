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
struct super_block {int s_time_gran; struct ramfs_fs_info* s_fs_info; struct dentry* s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_maxbytes; } ;
struct TYPE_2__ {int mode; } ;
struct ramfs_fs_info {TYPE_1__ mount_opts; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  RAMFS_MAGIC ; 
 int S_IFDIR ; 
 struct dentry* d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ramfs_fs_info*) ; 
 struct ramfs_fs_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct inode* ramfs_get_inode (struct super_block*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ramfs_ops ; 
 int ramfs_parse_options (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  save_mount_options (struct super_block*,void*) ; 

__attribute__((used)) static int ramfs_fill_super(struct super_block * sb, void * data, int silent)
{
	struct ramfs_fs_info *fsi;
	struct inode *inode = NULL;
	struct dentry *root;
	int err;

	save_mount_options(sb, data);

	fsi = kzalloc(sizeof(struct ramfs_fs_info), GFP_KERNEL);
	sb->s_fs_info = fsi;
	if (!fsi) {
		err = -ENOMEM;
		goto fail;
	}

	err = ramfs_parse_options(data, &fsi->mount_opts);
	if (err)
		goto fail;

	sb->s_maxbytes		= MAX_LFS_FILESIZE;
	sb->s_blocksize		= PAGE_CACHE_SIZE;
	sb->s_blocksize_bits	= PAGE_CACHE_SHIFT;
	sb->s_magic		= RAMFS_MAGIC;
	sb->s_op		= &ramfs_ops;
	sb->s_time_gran		= 1;

	inode = ramfs_get_inode(sb, S_IFDIR | fsi->mount_opts.mode, 0);
	if (!inode) {
		err = -ENOMEM;
		goto fail;
	}

	root = d_alloc_root(inode);
	sb->s_root = root;
	if (!root) {
		err = -ENOMEM;
		goto fail;
	}

	return 0;
fail:
	kfree(fsi);
	sb->s_fs_info = NULL;
	iput(inode);
	return err;
}