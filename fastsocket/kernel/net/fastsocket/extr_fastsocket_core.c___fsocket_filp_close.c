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
struct TYPE_2__ {int /*<<< orphan*/ * mnt; struct file* dentry; } ;
struct file {int /*<<< orphan*/  f_count; int /*<<< orphan*/  i_count; struct file* d_inode; int /*<<< orphan*/  d_count; TYPE_1__ f_path; int /*<<< orphan*/ * private_data; } ;
struct dentry {int /*<<< orphan*/  f_count; int /*<<< orphan*/  i_count; struct dentry* d_inode; int /*<<< orphan*/  d_count; TYPE_1__ f_path; int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPRINTK_LIMIT (int /*<<< orphan*/ ,char*,struct file*) ; 
 int /*<<< orphan*/  ERR ; 
 scalar_t__ atomic_long_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (struct file*) ; 
 int /*<<< orphan*/  eventpoll_release (struct file*) ; 
 int /*<<< orphan*/  put_empty_filp (struct file*) ; 

__attribute__((used)) static int __fsocket_filp_close(struct file *file)
{
	struct dentry *dentry = file->f_path.dentry;

	if (atomic_long_dec_and_test(&file->f_count)) {

		eventpoll_release(file);

		file->private_data = NULL;
		file->f_path.dentry = NULL;
		file->f_path.mnt = NULL;

		put_empty_filp(file);

		DPRINTK(DEBUG, "Free file 0x%p[%ld]\n", file, atomic_long_read(&file->f_count));

		if (dentry) {
			DPRINTK(DEBUG, "Release dentry 0x%p[%d]\n", dentry, atomic_read(&dentry->d_count));
			DPRINTK(DEBUG, "Release inode 0x%p[%d]\n", dentry->d_inode, atomic_read(&dentry->d_inode->i_count));
		} else {
			EPRINTK_LIMIT(ERR, "No dentry for file 0x%p\n", file);
			return 1;
		}

		dput(dentry);
	} else {
		DPRINTK(DEBUG, "Next time to release file 0x%p[%ld]\n", file, atomic_long_read(&file->f_count));
	}

	return 0;
}