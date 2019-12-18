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
struct videobuf_queue {int /*<<< orphan*/  streaming; int /*<<< orphan*/  stream; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_queue_lock (struct videobuf_queue*) ; 
 int /*<<< orphan*/  videobuf_queue_unlock (struct videobuf_queue*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stream_next_buffer_check_queue(struct videobuf_queue *q, int noblock)
{
	int retval;

checks:
	if (!q->streaming) {
		dprintk(1, "next_buffer: Not streaming\n");
		retval = -EINVAL;
		goto done;
	}

	if (list_empty(&q->stream)) {
		if (noblock) {
			retval = -EAGAIN;
			dprintk(2, "next_buffer: no buffers to dequeue\n");
			goto done;
		} else {
			dprintk(2, "next_buffer: waiting on buffer\n");

			/* Drop lock to avoid deadlock with qbuf */
			videobuf_queue_unlock(q);

			/* Checking list_empty and streaming is safe without
			 * locks because we goto checks to validate while
			 * holding locks before proceeding */
			retval = wait_event_interruptible(q->wait,
				!list_empty(&q->stream) || !q->streaming);
			videobuf_queue_lock(q);

			if (retval)
				goto done;

			goto checks;
		}
	}

	retval = 0;

done:
	return retval;
}