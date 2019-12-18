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
 int create (TYPE_3__*,struct dentry*,int) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int mkdir (TYPE_3__*,struct dentry*,int) ; 
 TYPE_2__* mount ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int create_by_name(const char *name, mode_t mode,
			  struct dentry *parent,
			  struct dentry **dentry)
{
	int error = 0;

	*dentry = NULL;

	/* If the parent is not specified, we create it in the root.
	 * We need the root dentry to do this, which is in the super
	 * block. A pointer to that is in the struct vfsmount that we
	 * have around.
	 */
	if (!parent ) {
		if (mount && mount->mnt_sb) {
			parent = mount->mnt_sb->s_root;
		}
	}
	if (!parent) {
		pr_debug("securityfs: Ah! can not find a parent!\n");
		return -EFAULT;
	}

	mutex_lock(&parent->d_inode->i_mutex);
	*dentry = lookup_one_len(name, parent, strlen(name));
	if (!IS_ERR(*dentry)) {
		if ((mode & S_IFMT) == S_IFDIR)
			error = mkdir(parent->d_inode, *dentry, mode);
		else
			error = create(parent->d_inode, *dentry, mode);
	} else
		error = PTR_ERR(*dentry);
	mutex_unlock(&parent->d_inode->i_mutex);

	return error;
}