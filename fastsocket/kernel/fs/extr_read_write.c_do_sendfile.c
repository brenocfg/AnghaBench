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
struct inode {TYPE_3__* i_sb; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {int f_mode; scalar_t__ f_pos; int f_flags; TYPE_2__ f_path; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  s_maxbytes; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 size_t EBADF ; 
 size_t EINVAL ; 
 size_t EOVERFLOW ; 
 size_t ESPIPE ; 
 int FMODE_PREAD ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  READ ; 
 int SPLICE_F_NONBLOCK ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  add_rchar (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  add_wchar (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  current ; 
 size_t do_splice_direct (struct file*,scalar_t__*,struct file*,size_t,int) ; 
 struct file* fget_light (int,int*) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 
 int /*<<< orphan*/  inc_syscr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_syscw (int /*<<< orphan*/ ) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t rw_verify_area (int /*<<< orphan*/ ,struct file*,scalar_t__*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t do_sendfile(int out_fd, int in_fd, loff_t *ppos,
			   size_t count, loff_t max)
{
	struct file * in_file, * out_file;
	struct inode * in_inode, * out_inode;
	loff_t pos;
	ssize_t retval;
	int fput_needed_in, fput_needed_out, fl;

	/*
	 * Get input file, and verify that it is ok..
	 */
	retval = -EBADF;
	in_file = fget_light(in_fd, &fput_needed_in);
	if (!in_file)
		goto out;
	if (!(in_file->f_mode & FMODE_READ))
		goto fput_in;
	retval = -ESPIPE;
	if (!ppos)
		ppos = &in_file->f_pos;
	else
		if (!(in_file->f_mode & FMODE_PREAD))
			goto fput_in;
	retval = rw_verify_area(READ, in_file, ppos, count);
	if (retval < 0)
		goto fput_in;
	count = retval;

	/*
	 * Get output file, and verify that it is ok..
	 */
	retval = -EBADF;
	out_file = fget_light(out_fd, &fput_needed_out);
	if (!out_file)
		goto fput_in;
	if (!(out_file->f_mode & FMODE_WRITE))
		goto fput_out;
	retval = -EINVAL;
	in_inode = in_file->f_path.dentry->d_inode;
	out_inode = out_file->f_path.dentry->d_inode;
	retval = rw_verify_area(WRITE, out_file, &out_file->f_pos, count);
	if (retval < 0)
		goto fput_out;
	count = retval;

	if (!max)
		max = min(in_inode->i_sb->s_maxbytes, out_inode->i_sb->s_maxbytes);

	pos = *ppos;
	if (unlikely(pos + count > max)) {
		retval = -EOVERFLOW;
		if (pos >= max)
			goto fput_out;
		count = max - pos;
	}

	fl = 0;
#if 0
	/*
	 * We need to debate whether we can enable this or not. The
	 * man page documents EAGAIN return for the output at least,
	 * and the application is arguably buggy if it doesn't expect
	 * EAGAIN on a non-blocking file descriptor.
	 */
	if (in_file->f_flags & O_NONBLOCK)
		fl = SPLICE_F_NONBLOCK;
#endif
	retval = do_splice_direct(in_file, ppos, out_file, count, fl);

	if (retval > 0) {
		add_rchar(current, retval);
		add_wchar(current, retval);
	}

	inc_syscr(current);
	inc_syscw(current);
	if (*ppos > max)
		retval = -EOVERFLOW;

fput_out:
	fput_light(out_file, fput_needed_out);
fput_in:
	fput_light(in_file, fput_needed_in);
out:
	return retval;
}