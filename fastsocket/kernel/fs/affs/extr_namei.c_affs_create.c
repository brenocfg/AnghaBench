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
struct super_block {int dummy; } ;
struct nameidata {int dummy; } ;
struct inode {int i_mode; scalar_t__ i_nlink; TYPE_2__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct dentry {TYPE_1__ d_name; } ;
struct TYPE_6__ {int s_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 TYPE_3__* AFFS_SB (struct super_block*) ; 
 int ENOSPC ; 
 int SF_OFS ; 
 int /*<<< orphan*/  ST_FILE ; 
 int affs_add_entry (struct inode*,struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_aops ; 
 int /*<<< orphan*/  affs_aops_ofs ; 
 int /*<<< orphan*/  affs_file_inode_operations ; 
 int /*<<< orphan*/  affs_file_operations ; 
 struct inode* affs_new_inode (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mode_to_prot (struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

int
affs_create(struct inode *dir, struct dentry *dentry, int mode, struct nameidata *nd)
{
	struct super_block *sb = dir->i_sb;
	struct inode	*inode;
	int		 error;

	pr_debug("AFFS: create(%lu,\"%.*s\",0%o)\n",dir->i_ino,(int)dentry->d_name.len,
		 dentry->d_name.name,mode);

	inode = affs_new_inode(dir);
	if (!inode)
		return -ENOSPC;

	inode->i_mode = mode;
	mode_to_prot(inode);
	mark_inode_dirty(inode);

	inode->i_op = &affs_file_inode_operations;
	inode->i_fop = &affs_file_operations;
	inode->i_mapping->a_ops = (AFFS_SB(sb)->s_flags & SF_OFS) ? &affs_aops_ofs : &affs_aops;
	error = affs_add_entry(dir, inode, dentry, ST_FILE);
	if (error) {
		inode->i_nlink = 0;
		iput(inode);
		return error;
	}
	return 0;
}