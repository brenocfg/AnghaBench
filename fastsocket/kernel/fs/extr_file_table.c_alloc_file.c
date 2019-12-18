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
struct path {int /*<<< orphan*/  mnt; TYPE_1__* dentry; } ;
struct file_operations {int dummy; } ;
struct file {int f_mode; struct file_operations const* f_op; int /*<<< orphan*/  f_mapping; struct path f_path; } ;
typedef  int fmode_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_mapping; } ;
struct TYPE_3__ {TYPE_2__* d_inode; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_take_write (struct file*) ; 
 struct file* get_empty_filp () ; 
 int /*<<< orphan*/  ima_counts_get (struct file*) ; 
 int /*<<< orphan*/  mnt_clone_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  special_file (int /*<<< orphan*/ ) ; 

struct file *alloc_file(struct path *path, fmode_t mode,
		const struct file_operations *fop)
{
	struct file *file;

	file = get_empty_filp();
	if (!file)
		return NULL;

	file->f_path = *path;
	file->f_mapping = path->dentry->d_inode->i_mapping;
	file->f_mode = mode;
	file->f_op = fop;

	/*
	 * These mounts don't really matter in practice
	 * for r/o bind mounts.  They aren't userspace-
	 * visible.  We do this for consistency, and so
	 * that we can do debugging checks at __fput()
	 */
	if ((mode & FMODE_WRITE) && !special_file(path->dentry->d_inode->i_mode)) {
		file_take_write(file);
		WARN_ON(mnt_clone_write(path->mnt));
	}
	ima_counts_get(file);
	return file;
}