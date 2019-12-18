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
struct pipe_inode_info {int nrbufs; int curbuf; int /*<<< orphan*/  fasync_readers; int /*<<< orphan*/  wait; int /*<<< orphan*/  waiting_writers; struct page* tmp_page; struct pipe_buffer* bufs; int /*<<< orphan*/  readers; } ;
struct pipe_buffer {int offset; int len; struct pipe_buf_operations* ops; struct page* page; } ;
struct pipe_buf_operations {int (* confirm ) (struct pipe_inode_info*,struct pipe_buffer*) ;int /*<<< orphan*/  (* unmap ) (struct pipe_inode_info*,struct pipe_buffer*,void*) ;void* (* map ) (struct pipe_inode_info*,struct pipe_buffer*,int) ;scalar_t__ can_merge; } ;
struct page {int dummy; } ;
struct kiocb {struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mutex; struct pipe_inode_info* i_pipe; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {int f_flags; TYPE_2__ f_path; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int EPIPE ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_HIGHUSER ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int O_NONBLOCK ; 
 int PAGE_SIZE ; 
 int PIPE_BUFFERS ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGPIPE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 struct pipe_buf_operations anon_pipe_buf_ops ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  file_update_time (struct file*) ; 
 int /*<<< orphan*/  iov_fault_in_pages_read (struct iovec*,int) ; 
 size_t iov_length (struct iovec*,unsigned long) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kmap (struct page*) ; 
 char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pipe_iov_copy_from_user (char*,struct iovec*,int,int) ; 
 int /*<<< orphan*/  pipe_wait (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  sb_end_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int stub1 (struct pipe_inode_info*,struct pipe_buffer*) ; 
 void* stub2 (struct pipe_inode_info*,struct pipe_buffer*,int) ; 
 int /*<<< orphan*/  stub3 (struct pipe_inode_info*,struct pipe_buffer*,void*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
pipe_write(struct kiocb *iocb, const struct iovec *_iov,
	    unsigned long nr_segs, loff_t ppos)
{
	struct file *filp = iocb->ki_filp;
	struct inode *inode = filp->f_path.dentry->d_inode;
	struct pipe_inode_info *pipe;
	ssize_t ret;
	int do_wakeup;
	struct iovec *iov = (struct iovec *)_iov;
	size_t total_len;
	ssize_t chars;

	total_len = iov_length(iov, nr_segs);
	/* Null write succeeds. */
	if (unlikely(total_len == 0))
		return 0;

	do_wakeup = 0;
	ret = 0;
	sb_start_write(inode->i_sb);
	mutex_lock(&inode->i_mutex);
	pipe = inode->i_pipe;

	if (!pipe->readers) {
		send_sig(SIGPIPE, current, 0);
		ret = -EPIPE;
		goto out;
	}

	/* We try to merge small writes */
	chars = total_len & (PAGE_SIZE-1); /* size of the last buffer */
	if (pipe->nrbufs && chars != 0) {
		int lastbuf = (pipe->curbuf + pipe->nrbufs - 1) &
							(PIPE_BUFFERS-1);
		struct pipe_buffer *buf = pipe->bufs + lastbuf;
		const struct pipe_buf_operations *ops = buf->ops;
		int offset = buf->offset + buf->len;

		if (ops->can_merge && offset + chars <= PAGE_SIZE) {
			int error, atomic = 1;
			void *addr;

			error = ops->confirm(pipe, buf);
			if (error)
				goto out;

			iov_fault_in_pages_read(iov, chars);
redo1:
			addr = ops->map(pipe, buf, atomic);
			error = pipe_iov_copy_from_user(offset + addr, iov,
							chars, atomic);
			ops->unmap(pipe, buf, addr);
			ret = error;
			do_wakeup = 1;
			if (error) {
				if (atomic) {
					atomic = 0;
					goto redo1;
				}
				goto out;
			}
			buf->len += chars;
			total_len -= chars;
			ret = chars;
			if (!total_len)
				goto out;
		}
	}

	for (;;) {
		int bufs;

		if (!pipe->readers) {
			send_sig(SIGPIPE, current, 0);
			if (!ret)
				ret = -EPIPE;
			break;
		}
		bufs = pipe->nrbufs;
		if (bufs < PIPE_BUFFERS) {
			int newbuf = (pipe->curbuf + bufs) & (PIPE_BUFFERS-1);
			struct pipe_buffer *buf = pipe->bufs + newbuf;
			struct page *page = pipe->tmp_page;
			char *src;
			int error, atomic = 1;

			if (!page) {
				page = alloc_page(GFP_HIGHUSER);
				if (unlikely(!page)) {
					ret = ret ? : -ENOMEM;
					break;
				}
				pipe->tmp_page = page;
			}
			/* Always wake up, even if the copy fails. Otherwise
			 * we lock up (O_NONBLOCK-)readers that sleep due to
			 * syscall merging.
			 * FIXME! Is this really true?
			 */
			do_wakeup = 1;
			chars = PAGE_SIZE;
			if (chars > total_len)
				chars = total_len;

			iov_fault_in_pages_read(iov, chars);
redo2:
			if (atomic)
				src = kmap_atomic(page, KM_USER0);
			else
				src = kmap(page);

			error = pipe_iov_copy_from_user(src, iov, chars,
							atomic);
			if (atomic)
				kunmap_atomic(src, KM_USER0);
			else
				kunmap(page);

			if (unlikely(error)) {
				if (atomic) {
					atomic = 0;
					goto redo2;
				}
				if (!ret)
					ret = error;
				break;
			}
			ret += chars;

			/* Insert it into the buffer array */
			buf->page = page;
			buf->ops = &anon_pipe_buf_ops;
			buf->offset = 0;
			buf->len = chars;
			pipe->nrbufs = ++bufs;
			pipe->tmp_page = NULL;

			total_len -= chars;
			if (!total_len)
				break;
		}
		if (bufs < PIPE_BUFFERS)
			continue;
		if (filp->f_flags & O_NONBLOCK) {
			if (!ret)
				ret = -EAGAIN;
			break;
		}
		if (signal_pending(current)) {
			if (!ret)
				ret = -ERESTARTSYS;
			break;
		}
		if (do_wakeup) {
			wake_up_interruptible_sync(&pipe->wait);
			kill_fasync(&pipe->fasync_readers, SIGIO, POLL_IN);
			do_wakeup = 0;
		}
		pipe->waiting_writers++;
		pipe_wait(pipe);
		pipe->waiting_writers--;
	}
out:
	mutex_unlock(&inode->i_mutex);
	if (do_wakeup) {
		wake_up_interruptible_sync(&pipe->wait);
		kill_fasync(&pipe->fasync_readers, SIGIO, POLL_IN);
	}
	if (ret > 0)
		file_update_time(filp);
	sb_end_write(inode->i_sb);
	return ret;
}