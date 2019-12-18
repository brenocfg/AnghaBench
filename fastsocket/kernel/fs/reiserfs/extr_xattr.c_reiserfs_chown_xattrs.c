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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct iattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chown_one_xattr ; 
 int reiserfs_for_each_xattr (struct inode*,int /*<<< orphan*/ ,struct iattr*) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ ,char*,char*,int) ; 

int reiserfs_chown_xattrs(struct inode *inode, struct iattr *attrs)
{
	int err = reiserfs_for_each_xattr(inode, chown_one_xattr, attrs);
	if (err)
		reiserfs_warning(inode->i_sb, "jdm-20007",
				 "Couldn't chown all xattrs (%d)\n", err);
	return err;
}