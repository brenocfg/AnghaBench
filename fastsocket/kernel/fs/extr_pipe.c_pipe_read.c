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
struct pipe_inode_info {int nrbufs; int curbuf; int /*<<< orphan*/  fasync_writers; int /*<<< orphan*/  wait; int /*<<< orphan*/  waiting_writers; int /*<<< orphan*/  writers; struct pipe_buffer* bufs; } ;
struct pipe_buffer {size_t len; int offset; struct pipe_buf_operations* ops; } ;
struct pipe_buf_operations {int (* confirm ) (struct pipe_inode_info*,struct pipe_buffer*) ;int /*<<< orphan*/  (* release ) (struct pipe_inode_info*,struct pipe_buffer*) ;int /*<<< orphan*/  (* unmap ) (struct pipe_inode_info*,struct pipe_buffer*,void*) ;void* (* map ) (struct pipe_inode_info*,struct pipe_buffer*,int) ;} ;
struct kiocb {struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; struct pipe_inode_info* i_pipe; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {int f_flags; TYPE_2__ f_path; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 size_t EAGAIN ; 
 size_t ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int PIPE_BUFFERS ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  iov_fault_in_pages_write (struct iovec*,size_t) ; 
 size_t iov_length (struct iovec*,unsigned long) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pipe_iov_copy_to_user (struct iovec*,void*,size_t,int) ; 
 int /*<<< orphan*/  pipe_wait (struct pipe_inode_info*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int stub1 (struct pipe_inode_info*,struct pipe_buffer*) ; 
 void* stub2 (struct pipe_inode_info*,struct pipe_buffer*,int) ; 
 int /*<<< orphan*/  stub3 (struct pipe_inode_info*,struct pipe_buffer*,void*) ; 
 int /*<<< orphan*/  stub4 (struct pipe_inode_info*,struct pipe_buffer*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
pipe_read(struct kiocb *iocb, const struct iovec *_iov,
	   unsigned long nr_segs, loff_t pos)
{
	struct file *filp = iocb->ki_filp;
	struct inode *inode = filp->f_path.dentry->d_inode;
	struct pipe_inode_info *pipe;
	int do_wakeup;
	ssize_t ret;
	struct iovec *iov = (struct iovec *)_iov;
	size_t total_len;

	total_len = iov_length(iov, nr_segs);
	/* Null read succeeds. */
	if (unlikely(total_len == 0))
		return 0;

	do_wakeup = 0;
	ret = 0;
	mutex_lock(&inode->i_mutex);
	pipe = inode->i_pipe;
	for (;;) {
		int bufs = pipe->nrbufs;
		if (bufs) {
			int curbuf = pipe->curbuf;
			struct pipe_buffer *buf = pipe->bufs + curbuf;
			const struct pipe_buf_operations *ops = buf->ops;
			void *addr;
			size_t chars = buf->len;
			int error, atomic;

			if (chars > total_len)
				chars = total_len;

			error = ops->confirm(pipe, buf);
			if (error) {
				if (!ret)
					error = ret;
				break;
			}

			atomic = !iov_fault_in_pages_write(iov, chars);
redo:
			addr = ops->map(pipe, buf, atomic);
			error = pipe_iov_copy_to_user(iov, addr + buf->offset, chars, atomic);
			ops->unmap(pipe, buf, addr);
			if (unlikely(error)) {
				/*
				 * Just retry with the slow path if we failed.
				 */
				if (atomic) {
					atomic = 0;
					goto redo;
				}
				if (!ret)
					ret = error;
				break;
			}
			ret += chars;
			buf->offset += chars;
			buf->len -= chars;
			if (!buf->len) {
				buf->ops = NULL;
				ops->release(pipe, buf);
				curbuf = (curbuf + 1) & (PIPE_BUFFERS-1);
				pipe->curbuf = curbuf;
				pipe->nrbufs = --bufs;
				do_wakeup = 1;
			}
			total_len -= chars;
			if (!total_len)
				break;	/* common path: read succeeded */
		}
		if (bufs)	/* More to do? */
			continue;
		if (!pipe->writers)
			break;
		if (!pipe->waiting_writers) {
			/* syscall merging: Usually we must not sleep
			 * if O_NONBLOCK is set, or if we got some data.
			 * But if a writer sleeps in kernel space, then
			 * we can wait for that data without violating POSIX.
			 */
			if (ret)
				break;
			if (filp->f_flags & O_NONBLOCK) {
				ret = -EAGAIN;
				break;
			}
		}
		if (signal_pending(current)) {
			if (!ret)
				ret = -ERESTARTSYS;
			break;
		}
		if (do_wakeup) {
			wake_up_interruptible_sync(&pipe->wait);
 			kill_fasync(&pipe->fasync_writers, SIGIO, POLL_OUT);
		}
		pipe_wait(pipe);
	}
	mutex_unlock(&inode->i_mutex);

	/* Signal writers asynchronously that there is more room. */
	if (do_wakeup) {
		wake_up_interruptible_sync(&pipe->wait);
		kill_fasync(&pipe->fasync_writers, SIGIO, POLL_OUT);
	}
	if (ret > 0)
		file_accessed(filp);
	return ret;
}