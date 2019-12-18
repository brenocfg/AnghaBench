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
struct pipe_inode_info {int nrbufs; int curbuf; int /*<<< orphan*/  fasync_readers; int /*<<< orphan*/  wait; scalar_t__ waiting_writers; struct pipe_buffer* bufs; int /*<<< orphan*/  readers; } ;
struct pipe_buffer {size_t len; int /*<<< orphan*/  flags; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get ) (struct pipe_inode_info*,struct pipe_buffer*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EPIPE ; 
 int PIPE_BUFFERS ; 
 int /*<<< orphan*/  PIPE_BUF_FLAG_GIFT ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGPIPE ; 
 unsigned int SPLICE_F_NONBLOCK ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_double_lock (struct pipe_inode_info*,struct pipe_inode_info*) ; 
 int /*<<< orphan*/  pipe_unlock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  stub1 (struct pipe_inode_info*,struct pipe_buffer*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int link_pipe(struct pipe_inode_info *ipipe,
		     struct pipe_inode_info *opipe,
		     size_t len, unsigned int flags)
{
	struct pipe_buffer *ibuf, *obuf;
	int ret = 0, i = 0, nbuf;

	/*
	 * Potential ABBA deadlock, work around it by ordering lock
	 * grabbing by pipe info address. Otherwise two different processes
	 * could deadlock (one doing tee from A -> B, the other from B -> A).
	 */
	pipe_double_lock(ipipe, opipe);

	do {
		if (!opipe->readers) {
			send_sig(SIGPIPE, current, 0);
			if (!ret)
				ret = -EPIPE;
			break;
		}

		/*
		 * If we have iterated all input buffers or ran out of
		 * output room, break.
		 */
		if (i >= ipipe->nrbufs || opipe->nrbufs >= PIPE_BUFFERS)
			break;

		ibuf = ipipe->bufs + ((ipipe->curbuf + i) & (PIPE_BUFFERS - 1));
		nbuf = (opipe->curbuf + opipe->nrbufs) & (PIPE_BUFFERS - 1);

		/*
		 * Get a reference to this pipe buffer,
		 * so we can copy the contents over.
		 */
		ibuf->ops->get(ipipe, ibuf);

		obuf = opipe->bufs + nbuf;
		*obuf = *ibuf;

		/*
		 * Don't inherit the gift flag, we need to
		 * prevent multiple steals of this page.
		 */
		obuf->flags &= ~PIPE_BUF_FLAG_GIFT;

		if (obuf->len > len)
			obuf->len = len;

		opipe->nrbufs++;
		ret += obuf->len;
		len -= obuf->len;
		i++;
	} while (len);

	/*
	 * return EAGAIN if we have the potential of some data in the
	 * future, otherwise just return 0
	 */
	if (!ret && ipipe->waiting_writers && (flags & SPLICE_F_NONBLOCK))
		ret = -EAGAIN;

	pipe_unlock(ipipe);
	pipe_unlock(opipe);

	/*
	 * If we put data in the output pipe, wakeup any potential readers.
	 */
	if (ret > 0) {
		smp_mb();
		if (waitqueue_active(&opipe->wait))
			wake_up_interruptible(&opipe->wait);
		kill_fasync(&opipe->fasync_readers, SIGIO, POLL_IN);
	}

	return ret;
}