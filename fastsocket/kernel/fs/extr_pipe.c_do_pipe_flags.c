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
struct file {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  audit_fd_pair (int,int) ; 
 struct file* create_read_pipe (struct file*,int) ; 
 struct file* create_write_pipe (int) ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 int /*<<< orphan*/  free_write_pipe (struct file*) ; 
 int get_unused_fd_flags (int) ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_filp (struct file*) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 

int do_pipe_flags(int *fd, int flags)
{
	struct file *fw, *fr;
	int error;
	int fdw, fdr;

	if (flags & ~(O_CLOEXEC | O_NONBLOCK))
		return -EINVAL;

	fw = create_write_pipe(flags);
	if (IS_ERR(fw))
		return PTR_ERR(fw);
	fr = create_read_pipe(fw, flags);
	error = PTR_ERR(fr);
	if (IS_ERR(fr))
		goto err_write_pipe;

	error = get_unused_fd_flags(flags);
	if (error < 0)
		goto err_read_pipe;
	fdr = error;

	error = get_unused_fd_flags(flags);
	if (error < 0)
		goto err_fdr;
	fdw = error;

	audit_fd_pair(fdr, fdw);
	fd_install(fdr, fr);
	fd_install(fdw, fw);
	fd[0] = fdr;
	fd[1] = fdw;

	return 0;

 err_fdr:
	put_unused_fd(fdr);
 err_read_pipe:
	path_put(&fr->f_path);
	put_filp(fr);
 err_write_pipe:
	free_write_pipe(fw);
	return error;
}