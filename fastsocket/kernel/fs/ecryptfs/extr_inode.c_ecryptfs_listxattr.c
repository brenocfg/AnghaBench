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
struct dentry {TYPE_2__* d_inode; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_mutex; TYPE_1__* i_op; } ;
struct TYPE_3__ {int (* listxattr ) (struct dentry*,char*,size_t) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct dentry*,char*,size_t) ; 

__attribute__((used)) static ssize_t
ecryptfs_listxattr(struct dentry *dentry, char *list, size_t size)
{
	int rc = 0;
	struct dentry *lower_dentry;

	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	if (!lower_dentry->d_inode->i_op->listxattr) {
		rc = -EOPNOTSUPP;
		goto out;
	}
	mutex_lock(&lower_dentry->d_inode->i_mutex);
	rc = lower_dentry->d_inode->i_op->listxattr(lower_dentry, list, size);
	mutex_unlock(&lower_dentry->d_inode->i_mutex);
out:
	return rc;
}