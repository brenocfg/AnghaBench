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
typedef  int u32 ;
struct super_block {int dummy; } ;
struct nameidata {int dummy; } ;
struct inode {int b_blocknr; struct super_block* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct dentry {int /*<<< orphan*/ * d_op; void* d_fsdata; TYPE_1__ d_name; } ;
struct buffer_head {int b_blocknr; struct super_block* i_sb; } ;
struct TYPE_6__ {int s_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  original; int /*<<< orphan*/  stype; } ;

/* Variables and functions */
 TYPE_3__* AFFS_SB (struct super_block*) ; 
 TYPE_2__* AFFS_TAIL (struct super_block*,struct inode*) ; 
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  PTR_ERR (struct inode*) ; 
 int SF_INTL ; 
#define  ST_LINKFILE 128 
 int /*<<< orphan*/  affs_brelse (struct inode*) ; 
 int /*<<< orphan*/  affs_dentry_operations ; 
 struct inode* affs_find_entry (struct inode*,struct dentry*) ; 
 struct inode* affs_iget (struct super_block*,int) ; 
 int /*<<< orphan*/  affs_intl_dentry_operations ; 
 int /*<<< orphan*/  affs_lock_dir (struct inode*) ; 
 int /*<<< orphan*/  affs_unlock_dir (struct inode*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 

struct dentry *
affs_lookup(struct inode *dir, struct dentry *dentry, struct nameidata *nd)
{
	struct super_block *sb = dir->i_sb;
	struct buffer_head *bh;
	struct inode *inode = NULL;

	pr_debug("AFFS: lookup(\"%.*s\")\n",(int)dentry->d_name.len,dentry->d_name.name);

	affs_lock_dir(dir);
	bh = affs_find_entry(dir, dentry);
	affs_unlock_dir(dir);
	if (IS_ERR(bh))
		return ERR_CAST(bh);
	if (bh) {
		u32 ino = bh->b_blocknr;

		/* store the real header ino in d_fsdata for faster lookups */
		dentry->d_fsdata = (void *)(long)ino;
		switch (be32_to_cpu(AFFS_TAIL(sb, bh)->stype)) {
		//link to dirs disabled
		//case ST_LINKDIR:
		case ST_LINKFILE:
			ino = be32_to_cpu(AFFS_TAIL(sb, bh)->original);
		}
		affs_brelse(bh);
		inode = affs_iget(sb, ino);
		if (IS_ERR(inode))
			return ERR_PTR(PTR_ERR(inode));
	}
	dentry->d_op = AFFS_SB(sb)->s_flags & SF_INTL ? &affs_intl_dentry_operations : &affs_dentry_operations;
	d_add(dentry, inode);
	return NULL;
}