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
struct inode {int i_generation; int /*<<< orphan*/  i_sb; } ;
struct dentry {TYPE_1__* d_inode; } ;
typedef  int /*<<< orphan*/  namebuf ;
struct TYPE_4__ {int /*<<< orphan*/  k_objectid; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int ENODATA ; 
 struct dentry* ERR_PTR (int) ; 
 TYPE_2__* INODE_PKEY (struct inode const*) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_XATTR ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dentry* open_xa_root (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ xattr_may_create (int) ; 
 int xattr_mkdir (TYPE_1__*,struct dentry*,int) ; 

__attribute__((used)) static struct dentry *open_xa_dir(const struct inode *inode, int flags)
{
	struct dentry *xaroot, *xadir;
	char namebuf[17];

	xaroot = open_xa_root(inode->i_sb, flags);
	if (IS_ERR(xaroot))
		return xaroot;

	snprintf(namebuf, sizeof(namebuf), "%X.%X",
		 le32_to_cpu(INODE_PKEY(inode)->k_objectid),
		 inode->i_generation);

	mutex_lock_nested(&xaroot->d_inode->i_mutex, I_MUTEX_XATTR);

	xadir = lookup_one_len(namebuf, xaroot, strlen(namebuf));
	if (!IS_ERR(xadir) && !xadir->d_inode) {
		int err = -ENODATA;
		if (xattr_may_create(flags))
			err = xattr_mkdir(xaroot->d_inode, xadir, 0700);
		if (err) {
			dput(xadir);
			xadir = ERR_PTR(err);
		}
	}

	mutex_unlock(&xaroot->d_inode->i_mutex);
	dput(xaroot);
	return xadir;
}