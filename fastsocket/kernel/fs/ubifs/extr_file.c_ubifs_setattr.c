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
struct ubifs_info {int dummy; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int ATTR_SIZE ; 
 int dbg_check_synced_i_size (struct inode*) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int do_setattr (struct ubifs_info*,struct inode*,struct iattr*) ; 
 int do_truncation (struct ubifs_info*,struct inode*,struct iattr*) ; 
 int inode_change_ok (struct inode*,struct iattr*) ; 

int ubifs_setattr(struct dentry *dentry, struct iattr *attr)
{
	int err;
	struct inode *inode = dentry->d_inode;
	struct ubifs_info *c = inode->i_sb->s_fs_info;

	dbg_gen("ino %lu, mode %#x, ia_valid %#x",
		inode->i_ino, inode->i_mode, attr->ia_valid);
	err = inode_change_ok(inode, attr);
	if (err)
		return err;

	err = dbg_check_synced_i_size(inode);
	if (err)
		return err;

	if ((attr->ia_valid & ATTR_SIZE) && attr->ia_size < inode->i_size)
		/* Truncation to a smaller size */
		err = do_truncation(c, inode, attr);
	else
		err = do_setattr(c, inode, attr);

	return err;
}