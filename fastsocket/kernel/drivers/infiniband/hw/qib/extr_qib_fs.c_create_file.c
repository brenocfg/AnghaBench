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
struct file_operations {int dummy; } ;
struct dentry {TYPE_1__* d_inode; } ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qibfs_mknod (TYPE_1__*,struct dentry*,int /*<<< orphan*/ ,struct file_operations const*,void*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int create_file(const char *name, mode_t mode,
		       struct dentry *parent, struct dentry **dentry,
		       const struct file_operations *fops, void *data)
{
	int error;

	*dentry = NULL;
	mutex_lock(&parent->d_inode->i_mutex);
	*dentry = lookup_one_len(name, parent, strlen(name));
	if (!IS_ERR(*dentry))
		error = qibfs_mknod(parent->d_inode, *dentry,
				    mode, fops, data);
	else
		error = PTR_ERR(*dentry);
	mutex_unlock(&parent->d_inode->i_mutex);

	return error;
}