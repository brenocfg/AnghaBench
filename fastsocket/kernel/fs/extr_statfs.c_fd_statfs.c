#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kstatfs {int dummy; } ;
struct file {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int EBADF ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int vfs_statfs (int /*<<< orphan*/ *,struct kstatfs*) ; 

int fd_statfs(int fd, struct kstatfs *st)
{
	struct file *file = fget(fd);
	int error = -EBADF;
	if (file) {
		error = vfs_statfs(&file->f_path, st);
		fput(file);
	}
	return error;
}