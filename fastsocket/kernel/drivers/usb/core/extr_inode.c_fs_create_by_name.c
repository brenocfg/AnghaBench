#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dentry {TYPE_3__* d_inode; } ;
typedef  int mode_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_6__ {TYPE_1__* mnt_sb; } ;
struct TYPE_5__ {struct dentry* s_root; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int /*<<< orphan*/  dbg (char*) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int usbfs_create (TYPE_3__*,struct dentry*,int) ; 
 int usbfs_mkdir (TYPE_3__*,struct dentry*,int) ; 
 TYPE_2__* usbfs_mount ; 

__attribute__((used)) static int fs_create_by_name (const char *name, mode_t mode,
			      struct dentry *parent, struct dentry **dentry)
{
	int error = 0;

	/* If the parent is not specified, we create it in the root.
	 * We need the root dentry to do this, which is in the super 
	 * block. A pointer to that is in the struct vfsmount that we
	 * have around.
	 */
	if (!parent ) {
		if (usbfs_mount && usbfs_mount->mnt_sb) {
			parent = usbfs_mount->mnt_sb->s_root;
		}
	}

	if (!parent) {
		dbg("Ah! can not find a parent!");
		return -EFAULT;
	}

	*dentry = NULL;
	mutex_lock(&parent->d_inode->i_mutex);
	*dentry = lookup_one_len(name, parent, strlen(name));
	if (!IS_ERR(*dentry)) {
		if ((mode & S_IFMT) == S_IFDIR)
			error = usbfs_mkdir (parent->d_inode, *dentry, mode);
		else 
			error = usbfs_create (parent->d_inode, *dentry, mode);
	} else
		error = PTR_ERR(*dentry);
	mutex_unlock(&parent->d_inode->i_mutex);

	return error;
}