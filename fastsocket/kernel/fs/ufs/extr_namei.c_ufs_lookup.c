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
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ UFS_MAXNAMLEN ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 struct inode* ufs_iget (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ufs_inode_by_name (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static struct dentry *ufs_lookup(struct inode * dir, struct dentry *dentry, struct nameidata *nd)
{
	struct inode * inode = NULL;
	ino_t ino;
	
	if (dentry->d_name.len > UFS_MAXNAMLEN)
		return ERR_PTR(-ENAMETOOLONG);

	lock_kernel();
	ino = ufs_inode_by_name(dir, dentry);
	if (ino) {
		inode = ufs_iget(dir->i_sb, ino);
		if (IS_ERR(inode)) {
			unlock_kernel();
			return ERR_CAST(inode);
		}
	}
	unlock_kernel();
	d_add(dentry, inode);
	return NULL;
}