#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct filename {char const* name; } ;
struct TYPE_7__ {TYPE_4__* dentry; TYPE_2__* mnt; } ;
struct file {TYPE_3__ f_path; } ;
struct TYPE_8__ {TYPE_1__* d_inode; } ;
struct TYPE_6__ {int mnt_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int EACCES ; 
 struct file* ERR_PTR (int) ; 
 int FMODE_EXEC ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int MAY_EXEC ; 
 int MAY_OPEN ; 
 int MNT_NOEXEC ; 
 int O_LARGEFILE ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int deny_write_access (struct file*) ; 
 struct file* do_filp_open (int /*<<< orphan*/ ,struct filename*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  fsnotify_open (TYPE_4__*) ; 

struct file *open_exec(const char *name)
{
	struct file *file;
	int err;
	struct filename filename = { .name = name };

	file = do_filp_open(AT_FDCWD, &filename,
				O_LARGEFILE | O_RDONLY | FMODE_EXEC, 0,
				MAY_EXEC | MAY_OPEN);
	if (IS_ERR(file))
		goto out;

	err = -EACCES;
	if (!S_ISREG(file->f_path.dentry->d_inode->i_mode))
		goto exit;

	if (file->f_path.mnt->mnt_flags & MNT_NOEXEC)
		goto exit;

	fsnotify_open(file->f_path.dentry);

	err = deny_write_access(file);
	if (err)
		goto exit;

out:
	return file;

exit:
	fput(file);
	return ERR_PTR(err);
}