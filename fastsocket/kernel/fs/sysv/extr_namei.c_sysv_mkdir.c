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
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {scalar_t__ s_link_max; } ;

/* Variables and functions */
 int EMLINK ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 TYPE_1__* SYSV_SB (int /*<<< orphan*/ ) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_link_count (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int sysv_add_link (struct dentry*,struct inode*) ; 
 int sysv_make_empty (struct inode*,struct inode*) ; 
 struct inode* sysv_new_inode (struct inode*,int) ; 
 int /*<<< orphan*/  sysv_set_inode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysv_mkdir(struct inode * dir, struct dentry *dentry, int mode)
{
	struct inode * inode;
	int err = -EMLINK;

	if (dir->i_nlink >= SYSV_SB(dir->i_sb)->s_link_max) 
		goto out;
	inode_inc_link_count(dir);

	inode = sysv_new_inode(dir, S_IFDIR|mode);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out_dir;

	sysv_set_inode(inode, 0);

	inode_inc_link_count(inode);

	err = sysv_make_empty(inode, dir);
	if (err)
		goto out_fail;

	err = sysv_add_link(dentry, inode);
	if (err)
		goto out_fail;

        d_instantiate(dentry, inode);
out:
	return err;

out_fail:
	inode_dec_link_count(inode);
	inode_dec_link_count(inode);
	iput(inode);
out_dir:
	inode_dec_link_count(dir);
	goto out;
}