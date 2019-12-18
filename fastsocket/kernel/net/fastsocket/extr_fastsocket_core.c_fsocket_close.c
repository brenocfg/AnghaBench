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
struct files_struct {int /*<<< orphan*/  file_lock; } ;
struct file {int dummy; } ;
struct fdtable {unsigned int max_fds; int /*<<< orphan*/  close_on_exec; struct file** fd; } ;
struct TYPE_2__ {struct files_struct* files; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  FD_CLR (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __put_unused_fd (struct files_struct*,unsigned int) ; 
 TYPE_1__* current ; 
 struct fdtable* files_fdtable (struct files_struct*) ; 
 int fsocket_filp_close (struct file*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int fsocket_close(unsigned int fd)
{
	struct file *filp;
	struct files_struct *files = current->files;
	struct fdtable *fdt;
	int retval = 0;

	spin_lock(&files->file_lock);
	fdt = files_fdtable(files);
	if (fd >= fdt->max_fds)
		goto out_unlock;
	filp = fdt->fd[fd];
	if (!filp)
		goto out_unlock;
	rcu_assign_pointer(fdt->fd[fd], NULL);
	FD_CLR(fd, fdt->close_on_exec);
	__put_unused_fd(files, fd);
	spin_unlock(&files->file_lock);

	retval = fsocket_filp_close(filp);

	return retval;

out_unlock:
	spin_unlock(&files->file_lock);
	return -EBADF;
}