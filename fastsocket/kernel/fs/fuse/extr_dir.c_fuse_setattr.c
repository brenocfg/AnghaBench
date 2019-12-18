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
struct iattr {int ia_valid; int /*<<< orphan*/ * ia_file; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ATTR_FILE ; 
 int EACCES ; 
 int /*<<< orphan*/  fuse_allow_current_process (int /*<<< orphan*/ ) ; 
 int fuse_do_setattr (struct inode*,struct iattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_fuse_conn (struct inode*) ; 

__attribute__((used)) static int fuse_setattr(struct dentry *entry, struct iattr *attr)
{
	struct inode *inode = entry->d_inode;

	if (!fuse_allow_current_process(get_fuse_conn(inode)))
		return -EACCES;

	if (attr->ia_valid & ATTR_FILE)
		return fuse_do_setattr(inode, attr, attr->ia_file);
	else
		return fuse_do_setattr(inode, attr, NULL);
}