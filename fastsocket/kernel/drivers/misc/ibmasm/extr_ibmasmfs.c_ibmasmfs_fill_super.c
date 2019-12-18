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
struct super_block {int s_time_gran; struct dentry* s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; } ;
struct inode {int /*<<< orphan*/  i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IBMASMFS_MAGIC ; 
 int /*<<< orphan*/  PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int S_IFDIR ; 
 struct dentry* d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  ibmasmfs_create_files (struct super_block*,struct dentry*) ; 
 int /*<<< orphan*/  ibmasmfs_dir_ops ; 
 struct inode* ibmasmfs_make_inode (struct super_block*,int) ; 
 int /*<<< orphan*/  ibmasmfs_s_ops ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 

__attribute__((used)) static int ibmasmfs_fill_super (struct super_block *sb, void *data, int silent)
{
	struct inode *root;
	struct dentry *root_dentry;

	sb->s_blocksize = PAGE_CACHE_SIZE;
	sb->s_blocksize_bits = PAGE_CACHE_SHIFT;
	sb->s_magic = IBMASMFS_MAGIC;
	sb->s_op = &ibmasmfs_s_ops;
	sb->s_time_gran = 1;

	root = ibmasmfs_make_inode (sb, S_IFDIR | 0500);
	if (!root)
		return -ENOMEM;

	root->i_op = &simple_dir_inode_operations;
	root->i_fop = ibmasmfs_dir_ops;

	root_dentry = d_alloc_root(root);
	if (!root_dentry) {
		iput(root);
		return -ENOMEM;
	}
	sb->s_root = root_dentry;

	ibmasmfs_create_files(sb, root_dentry);
	return 0;
}