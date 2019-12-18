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
struct splice_pipe_desc {unsigned int nr_pages; int flags; int /*<<< orphan*/  (* spd_release ) (struct splice_pipe_desc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ops; TYPE_1__* partial; int /*<<< orphan*/ * pages; } ;
struct pipe_inode_info {int nrbufs; int curbuf; int /*<<< orphan*/  fasync_readers; int /*<<< orphan*/  wait; int /*<<< orphan*/  waiting_writers; scalar_t__ inode; struct pipe_buffer* bufs; int /*<<< orphan*/  readers; } ;
struct pipe_buffer {scalar_t__ len; int /*<<< orphan*/  flags; int /*<<< orphan*/  ops; int /*<<< orphan*/  private; int /*<<< orphan*/  offset; int /*<<< orphan*/  page; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  private; scalar_t__ len; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EPIPE ; 
 int ERESTARTSYS ; 
 int PIPE_BUFFERS ; 
 int /*<<< orphan*/  PIPE_BUF_FLAG_GIFT ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int SPLICE_F_GIFT ; 
 int SPLICE_F_NONBLOCK ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_lock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  pipe_unlock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  pipe_wait (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  stub1 (struct splice_pipe_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync (int /*<<< orphan*/ *) ; 

ssize_t splice_to_pipe(struct pipe_inode_info *pipe,
		       struct splice_pipe_desc *spd)
{
	unsigned int spd_pages = spd->nr_pages;
	int ret, do_wakeup, page_nr;

	ret = 0;
	do_wakeup = 0;
	page_nr = 0;

	pipe_lock(pipe);

	for (;;) {
		if (!pipe->readers) {
			send_sig(SIGPIPE, current, 0);
			if (!ret)
				ret = -EPIPE;
			break;
		}

		if (pipe->nrbufs < PIPE_BUFFERS) {
			int newbuf = (pipe->curbuf + pipe->nrbufs) & (PIPE_BUFFERS - 1);
			struct pipe_buffer *buf = pipe->bufs + newbuf;

			buf->page = spd->pages[page_nr];
			buf->offset = spd->partial[page_nr].offset;
			buf->len = spd->partial[page_nr].len;
			buf->private = spd->partial[page_nr].private;
			buf->ops = spd->ops;
			if (spd->flags & SPLICE_F_GIFT)
				buf->flags |= PIPE_BUF_FLAG_GIFT;

			pipe->nrbufs++;
			page_nr++;
			ret += buf->len;

			if (pipe->inode)
				do_wakeup = 1;

			if (!--spd->nr_pages)
				break;
			if (pipe->nrbufs < PIPE_BUFFERS)
				continue;

			break;
		}

		if (spd->flags & SPLICE_F_NONBLOCK) {
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
			smp_mb();
			if (waitqueue_active(&pipe->wait))
				wake_up_interruptible_sync(&pipe->wait);
			kill_fasync(&pipe->fasync_readers, SIGIO, POLL_IN);
			do_wakeup = 0;
		}

		pipe->waiting_writers++;
		pipe_wait(pipe);
		pipe->waiting_writers--;
	}

	pipe_unlock(pipe);

	if (do_wakeup) {
		smp_mb();
		if (waitqueue_active(&pipe->wait))
			wake_up_interruptible(&pipe->wait);
		kill_fasync(&pipe->fasync_readers, SIGIO, POLL_IN);
	}

	while (page_nr < spd_pages)
		spd->spd_release(spd, page_nr++);

	return ret;
}