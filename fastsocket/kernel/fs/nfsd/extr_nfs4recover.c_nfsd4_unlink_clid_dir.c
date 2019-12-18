#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dentry {TYPE_2__* d_inode; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct TYPE_6__ {TYPE_1__ f_path; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  dprintk (char*,int,char*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* rec_file ; 
 int vfs_rmdir (TYPE_2__*,struct dentry*) ; 

__attribute__((used)) static int
nfsd4_unlink_clid_dir(char *name, int namlen)
{
	struct dentry *dir, *dentry;
	int status;

	dprintk("NFSD: nfsd4_unlink_clid_dir. name %.*s\n", namlen, name);

	dir = rec_file->f_path.dentry;
	mutex_lock_nested(&dir->d_inode->i_mutex, I_MUTEX_PARENT);
	dentry = lookup_one_len(name, dir, namlen);
	if (IS_ERR(dentry)) {
		status = PTR_ERR(dentry);
		goto out_unlock;
	}
	status = -ENOENT;
	if (!dentry->d_inode)
		goto out;
	status = vfs_rmdir(dir->d_inode, dentry);
out:
	dput(dentry);
out_unlock:
	mutex_unlock(&dir->d_inode->i_mutex);
	return status;
}