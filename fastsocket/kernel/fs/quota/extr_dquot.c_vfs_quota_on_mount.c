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
struct super_block {TYPE_2__* s_root; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct TYPE_4__ {TYPE_1__* d_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int DQUOT_LIMITS_ENABLED ; 
 int DQUOT_USAGE_ENABLED ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* lookup_one_len (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int security_quota_on (struct dentry*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int vfs_load_quota_inode (int /*<<< orphan*/ ,int,int,int) ; 

int vfs_quota_on_mount(struct super_block *sb, char *qf_name,
		int format_id, int type)
{
	struct dentry *dentry;
	int error;

	mutex_lock(&sb->s_root->d_inode->i_mutex);
	dentry = lookup_one_len(qf_name, sb->s_root, strlen(qf_name));
	mutex_unlock(&sb->s_root->d_inode->i_mutex);
	if (IS_ERR(dentry))
		return PTR_ERR(dentry);

	if (!dentry->d_inode) {
		error = -ENOENT;
		goto out;
	}

	error = security_quota_on(dentry);
	if (!error)
		error = vfs_load_quota_inode(dentry->d_inode, type, format_id,
				DQUOT_USAGE_ENABLED | DQUOT_LIMITS_ENABLED);

out:
	dput(dentry);
	return error;
}