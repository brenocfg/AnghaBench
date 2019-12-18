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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct iattr {int ia_valid; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 TYPE_1__* AFFS_SB (int /*<<< orphan*/ ) ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int EPERM ; 
 int SF_IMMUTABLE ; 
 int SF_QUIET ; 
 int SF_SETGID ; 
 int SF_SETMODE ; 
 int SF_SETUID ; 
 int inode_change_ok (struct inode*,struct iattr*) ; 
 int inode_setattr (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  mode_to_prot (struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

int
affs_notify_change(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = dentry->d_inode;
	int error;

	pr_debug("AFFS: notify_change(%lu,0x%x)\n",inode->i_ino,attr->ia_valid);

	error = inode_change_ok(inode,attr);
	if (error)
		goto out;

	if (((attr->ia_valid & ATTR_UID) && (AFFS_SB(inode->i_sb)->s_flags & SF_SETUID)) ||
	    ((attr->ia_valid & ATTR_GID) && (AFFS_SB(inode->i_sb)->s_flags & SF_SETGID)) ||
	    ((attr->ia_valid & ATTR_MODE) &&
	     (AFFS_SB(inode->i_sb)->s_flags & (SF_SETMODE | SF_IMMUTABLE)))) {
		if (!(AFFS_SB(inode->i_sb)->s_flags & SF_QUIET))
			error = -EPERM;
		goto out;
	}

	error = inode_setattr(inode, attr);
	if (!error && (attr->ia_valid & ATTR_MODE))
		mode_to_prot(inode);
out:
	return error;
}