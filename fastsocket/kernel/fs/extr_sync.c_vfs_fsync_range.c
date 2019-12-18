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
struct file_operations {int (* fsync ) (struct file*,struct dentry*,int) ;} ;
struct file {struct file_operations* f_op; struct address_space* f_mapping; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct address_space {TYPE_2__* host; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_3__ {struct file_operations* i_fop; struct address_space* i_mapping; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int filemap_write_and_wait_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct file*,struct dentry*,int) ; 

int vfs_fsync_range(struct file *file, struct dentry *dentry, loff_t start,
		    loff_t end, int datasync)
{
	const struct file_operations *fop;
	struct address_space *mapping;
	int err, ret;

	/*
	 * Get mapping and operations from the file in case we have
	 * as file, or get the default values for them in case we
	 * don't have a struct file available.  Damn nfsd..
	 */
	if (file) {
		mapping = file->f_mapping;
		fop = file->f_op;
	} else {
		mapping = dentry->d_inode->i_mapping;
		fop = dentry->d_inode->i_fop;
	}

	if (!fop || !fop->fsync) {
		ret = -EINVAL;
		goto out;
	}

	ret = filemap_write_and_wait_range(mapping, start, end);

	/*
	 * We need to protect against concurrent writers, which could cause
	 * livelocks in fsync_buffers_list().
	 */
	mutex_lock(&mapping->host->i_mutex);
	err = fop->fsync(file, dentry, datasync);
	if (!ret || (err && ret == -EIO))
		ret = err;
	mutex_unlock(&mapping->host->i_mutex);

out:
	return ret;
}