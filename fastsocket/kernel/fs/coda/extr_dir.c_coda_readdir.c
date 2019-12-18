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
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {int /*<<< orphan*/  f_pos; TYPE_3__* f_op; TYPE_2__ f_path; } ;
struct coda_file_info {scalar_t__ cfi_magic; struct file* cfi_container; } ;
typedef  int /*<<< orphan*/  filldir_t ;
struct TYPE_6__ {int (* readdir ) (struct file*,void*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct coda_file_info* CODA_FTOC (struct file*) ; 
 scalar_t__ CODA_MAGIC ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  IS_DEADDIR (struct inode*) ; 
 int coda_venus_readdir (struct file*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct file*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_readdir(struct file *coda_file, void *buf, filldir_t filldir)
{
	struct coda_file_info *cfi;
	struct file *host_file;
	int ret;

	cfi = CODA_FTOC(coda_file);
	BUG_ON(!cfi || cfi->cfi_magic != CODA_MAGIC);
	host_file = cfi->cfi_container;

	if (!host_file->f_op)
		return -ENOTDIR;

	if (host_file->f_op->readdir)
	{
		/* potemkin case: we were handed a directory inode.
		 * We can't use vfs_readdir because we have to keep the file
		 * position in sync between the coda_file and the host_file.
		 * and as such we need grab the inode mutex. */
		struct inode *host_inode = host_file->f_path.dentry->d_inode;

		mutex_lock(&host_inode->i_mutex);
		host_file->f_pos = coda_file->f_pos;

		ret = -ENOENT;
		if (!IS_DEADDIR(host_inode)) {
			ret = host_file->f_op->readdir(host_file, buf, filldir);
			file_accessed(host_file);
		}

		coda_file->f_pos = host_file->f_pos;
		mutex_unlock(&host_inode->i_mutex);
	}
	else /* Venus: we must read Venus dirents from a file */
		ret = coda_venus_readdir(coda_file, buf, filldir);

	return ret;
}