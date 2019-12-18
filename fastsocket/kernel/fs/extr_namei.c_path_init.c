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
struct TYPE_5__ {struct dentry* dentry; int /*<<< orphan*/ * mnt; } ;
struct nameidata {unsigned int flags; TYPE_2__ path; TYPE_2__ root; scalar_t__ depth; int /*<<< orphan*/  last_type; } ;
struct fs_struct {int /*<<< orphan*/  lock; TYPE_2__ pwd; } ;
struct file {TYPE_2__ f_path; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_6__ {struct fs_struct* fs; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int EBADF ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  LAST_ROOT ; 
 int /*<<< orphan*/  MAY_EXEC ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 struct file* fget_light (int,int*) ; 
 int file_permission (struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 
 int /*<<< orphan*/  path_get (TYPE_2__*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_root (struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int path_init(int dfd, const char *name, unsigned int flags, struct nameidata *nd)
{
	int retval = 0;
	int fput_needed;
	struct file *file;

	nd->last_type = LAST_ROOT; /* if there are only slashes... */
	nd->flags = flags;
	nd->depth = 0;
	nd->root.mnt = NULL;

	if (*name=='/') {
		set_root(nd);
		nd->path = nd->root;
		path_get(&nd->root);
	} else if (dfd == AT_FDCWD) {
		struct fs_struct *fs = current->fs;
		read_lock(&fs->lock);
		nd->path = fs->pwd;
		path_get(&fs->pwd);
		read_unlock(&fs->lock);
	} else {
		struct dentry *dentry;

		file = fget_light(dfd, &fput_needed);
		retval = -EBADF;
		if (!file)
			goto out_fail;

		dentry = file->f_path.dentry;

		retval = -ENOTDIR;
		if (!S_ISDIR(dentry->d_inode->i_mode))
			goto fput_fail;

		/*
		 * __link_path_walk will shortcut the permissions check if the
		 * pathname is empty, so we must handle it here.
		 */
		if (unlikely(*name == '\0')) {
			retval = file_permission(file, MAY_EXEC);
			if (retval)
				goto fput_fail;
		}

		nd->path = file->f_path;
		path_get(&file->f_path);

		fput_light(file, fput_needed);
	}
	return 0;

fput_fail:
	fput_light(file, fput_needed);
out_fail:
	return retval;
}