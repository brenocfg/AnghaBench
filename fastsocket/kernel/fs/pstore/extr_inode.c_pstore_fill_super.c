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
struct super_block {int s_time_gran; struct dentry* s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_maxbytes; } ;
struct inode {int /*<<< orphan*/ * i_op; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PSTOREFS_MAGIC ; 
 int S_IFDIR ; 
 struct dentry* d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  parse_options (void*) ; 
 int /*<<< orphan*/  pstore_dir_inode_operations ; 
 struct inode* pstore_get_inode (struct super_block*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstore_get_records (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstore_ops ; 
 struct super_block* pstore_sb ; 
 int /*<<< orphan*/  save_mount_options (struct super_block*,void*) ; 

int pstore_fill_super(struct super_block *sb, void *data, int silent)
{
	struct inode *inode = NULL;
	struct dentry *root;
	int err;

	save_mount_options(sb, data);

	pstore_sb = sb;

	sb->s_maxbytes		= MAX_LFS_FILESIZE;
	sb->s_blocksize		= PAGE_CACHE_SIZE;
	sb->s_blocksize_bits	= PAGE_CACHE_SHIFT;
	sb->s_magic		= PSTOREFS_MAGIC;
	sb->s_op		= &pstore_ops;
	sb->s_time_gran		= 1;

	parse_options(data);

	inode = pstore_get_inode(sb, NULL, S_IFDIR | 0755, 0);
	if (!inode) {
		err = -ENOMEM;
		goto fail;
	}
	/* override ramfs "dir" options so we catch unlink(2) */
	inode->i_op = &pstore_dir_inode_operations;

	root = d_alloc_root(inode);
	sb->s_root = root;
	if (!root) {
		err = -ENOMEM;
		goto fail;
	}

	pstore_get_records(0);

	return 0;
fail:
	iput(inode);
	return err;
}