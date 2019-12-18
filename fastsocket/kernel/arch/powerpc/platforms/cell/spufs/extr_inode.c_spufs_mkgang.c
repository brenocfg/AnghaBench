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
struct spu_gang {int dummy; } ;
struct inode {int i_mode; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_sb; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {struct spu_gang* i_gang; int /*<<< orphan*/ * i_ctx; } ;

/* Variables and functions */
 int ENOSPC ; 
 TYPE_1__* SPUFS_I (struct inode*) ; 
 int S_IFDIR ; 
 int S_ISGID ; 
 struct spu_gang* alloc_spu_gang () ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 struct inode* spufs_new_inode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
spufs_mkgang(struct inode *dir, struct dentry *dentry, int mode)
{
	int ret;
	struct inode *inode;
	struct spu_gang *gang;

	ret = -ENOSPC;
	inode = spufs_new_inode(dir->i_sb, mode | S_IFDIR);
	if (!inode)
		goto out;

	ret = 0;
	if (dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;
		inode->i_mode &= S_ISGID;
	}
	gang = alloc_spu_gang();
	SPUFS_I(inode)->i_ctx = NULL;
	SPUFS_I(inode)->i_gang = gang;
	if (!gang)
		goto out_iput;

	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;

	d_instantiate(dentry, inode);
	inc_nlink(dir);
	inc_nlink(dentry->d_inode);
	return ret;

out_iput:
	iput(inode);
out:
	return ret;
}