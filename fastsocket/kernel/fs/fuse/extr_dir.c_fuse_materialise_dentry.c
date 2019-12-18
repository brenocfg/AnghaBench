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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct fuse_conn {int /*<<< orphan*/  inst_mutex; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 struct dentry* d_materialise_unique (struct dentry*,struct inode*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *fuse_materialise_dentry(struct dentry *dentry,
					      struct inode *inode)
{
	struct dentry *newent;

	if (inode && S_ISDIR(inode->i_mode)) {
		struct fuse_conn *fc = get_fuse_conn(inode);

		mutex_lock(&fc->inst_mutex);
		newent = d_materialise_unique(dentry, inode);
		mutex_unlock(&fc->inst_mutex);
	} else {
		newent = d_materialise_unique(dentry, inode);
	}

	return newent;
}