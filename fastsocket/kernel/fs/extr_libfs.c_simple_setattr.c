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
struct inode {int dummy; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_size; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ATTR_SIZE ; 
 int /*<<< orphan*/  generic_setattr (struct inode*,struct iattr*) ; 
 int inode_change_ok (struct inode*,struct iattr*) ; 
 int simple_setsize (struct inode*,int /*<<< orphan*/ ) ; 

int simple_setattr(struct dentry *dentry, struct iattr *iattr)
{
	struct inode *inode = dentry->d_inode;
	int error;

	error = inode_change_ok(inode, iattr);
	if (error)
		return error;

	if (iattr->ia_valid & ATTR_SIZE) {
		error = simple_setsize(inode, iattr->ia_size);
		if (error)
			return error;
	}

	generic_setattr(inode, iattr);

	return error;
}