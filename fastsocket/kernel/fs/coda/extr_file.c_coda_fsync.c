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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {struct inode* d_inode; } ;
struct coda_file_info {scalar_t__ cfi_magic; struct file* cfi_container; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct coda_file_info* CODA_FTOC (struct file*) ; 
 scalar_t__ CODA_MAGIC ; 
 int EINVAL ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int venus_fsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfs_fsync (struct file*,int /*<<< orphan*/ ,int) ; 

int coda_fsync(struct file *coda_file, struct dentry *coda_dentry, int datasync)
{
	struct file *host_file;
	struct inode *coda_inode = coda_dentry->d_inode;
	struct coda_file_info *cfi;
	int err = 0;

	if (!(S_ISREG(coda_inode->i_mode) || S_ISDIR(coda_inode->i_mode) ||
	      S_ISLNK(coda_inode->i_mode)))
		return -EINVAL;

	cfi = CODA_FTOC(coda_file);
	BUG_ON(!cfi || cfi->cfi_magic != CODA_MAGIC);
	host_file = cfi->cfi_container;

	err = vfs_fsync(host_file, host_file->f_path.dentry, datasync);
	if ( !err && !datasync ) {
		lock_kernel();
		err = venus_fsync(coda_inode->i_sb, coda_i2f(coda_inode));
		unlock_kernel();
	}

	return err;
}