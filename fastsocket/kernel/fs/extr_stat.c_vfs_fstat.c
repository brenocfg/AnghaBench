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
struct kstat {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;
struct file {TYPE_1__ f_path; } ;

/* Variables and functions */
 int EBADF ; 
 struct file* fget (unsigned int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int vfs_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kstat*) ; 

int vfs_fstat(unsigned int fd, struct kstat *stat)
{
	struct file *f = fget(fd);
	int error = -EBADF;

	if (f) {
		error = vfs_getattr(f->f_path.mnt, f->f_path.dentry, stat);
		fput(f);
	}
	return error;
}