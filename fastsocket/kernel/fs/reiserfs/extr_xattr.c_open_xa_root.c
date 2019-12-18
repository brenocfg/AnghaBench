#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  xattr_root; struct dentry* priv_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int ENODATA ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  I_MUTEX_XATTR ; 
 TYPE_2__* REISERFS_SB (struct super_block*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ xattr_may_create (int) ; 
 int xattr_mkdir (TYPE_1__*,struct dentry*,int) ; 

__attribute__((used)) static struct dentry *open_xa_root(struct super_block *sb, int flags)
{
	struct dentry *privroot = REISERFS_SB(sb)->priv_root;
	struct dentry *xaroot;
	if (!privroot->d_inode)
		return ERR_PTR(-ENODATA);

	mutex_lock_nested(&privroot->d_inode->i_mutex, I_MUTEX_XATTR);

	xaroot = dget(REISERFS_SB(sb)->xattr_root);
	if (!xaroot)
		xaroot = ERR_PTR(-ENODATA);
	else if (!xaroot->d_inode) {
		int err = -ENODATA;
		if (xattr_may_create(flags))
			err = xattr_mkdir(privroot->d_inode, xaroot, 0700);
		if (err) {
			dput(xaroot);
			xaroot = ERR_PTR(err);
		}
	}

	mutex_unlock(&privroot->d_inode->i_mutex);
	return xaroot;
}