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
 scalar_t__ VXFS_NAMELEN ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 struct inode* vxfs_iget (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vxfs_inode_by_name (struct inode*,struct dentry*) ; 

__attribute__((used)) static struct dentry *
vxfs_lookup(struct inode *dip, struct dentry *dp, struct nameidata *nd)
{
	struct inode		*ip = NULL;
	ino_t			ino;
			 
	if (dp->d_name.len > VXFS_NAMELEN)
		return ERR_PTR(-ENAMETOOLONG);
				 
	lock_kernel();
	ino = vxfs_inode_by_name(dip, dp);
	if (ino) {
		ip = vxfs_iget(dip->i_sb, ino);
		if (IS_ERR(ip)) {
			unlock_kernel();
			return ERR_CAST(ip);
		}
	}
	unlock_kernel();
	d_add(dp, ip);
	return NULL;
}