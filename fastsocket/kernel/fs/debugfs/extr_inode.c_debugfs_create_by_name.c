#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct file_operations {int dummy; } ;
struct dentry {TYPE_3__* d_inode; } ;
typedef  int mode_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_7__ {TYPE_1__* mnt_sb; } ;
struct TYPE_6__ {struct dentry* s_root; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
#define  S_IFDIR 129 
#define  S_IFLNK 128 
 int S_IFMT ; 
 int debugfs_create (TYPE_3__*,struct dentry*,int,void*,struct file_operations const*) ; 
 int debugfs_link (TYPE_3__*,struct dentry*,int,void*,struct file_operations const*) ; 
 int debugfs_mkdir (TYPE_3__*,struct dentry*,int,void*,struct file_operations const*) ; 
 TYPE_2__* debugfs_mount ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int debugfs_create_by_name(const char *name, mode_t mode,
				  struct dentry *parent,
				  struct dentry **dentry,
				  void *data,
				  const struct file_operations *fops)
{
	int error = 0;

	/* If the parent is not specified, we create it in the root.
	 * We need the root dentry to do this, which is in the super 
	 * block. A pointer to that is in the struct vfsmount that we
	 * have around.
	 */
	if (!parent) {
		if (debugfs_mount && debugfs_mount->mnt_sb) {
			parent = debugfs_mount->mnt_sb->s_root;
		}
	}
	if (!parent) {
		pr_debug("debugfs: Ah! can not find a parent!\n");
		return -EFAULT;
	}

	*dentry = NULL;
	mutex_lock(&parent->d_inode->i_mutex);
	*dentry = lookup_one_len(name, parent, strlen(name));
	if (!IS_ERR(*dentry)) {
		switch (mode & S_IFMT) {
		case S_IFDIR:
			error = debugfs_mkdir(parent->d_inode, *dentry, mode,
					      data, fops);
			break;
		case S_IFLNK:
			error = debugfs_link(parent->d_inode, *dentry, mode,
					     data, fops);
			break;
		default:
			error = debugfs_create(parent->d_inode, *dentry, mode,
					       data, fops);
			break;
		}
		dput(*dentry);
	} else
		error = PTR_ERR(*dentry);
	mutex_unlock(&parent->d_inode->i_mutex);

	return error;
}