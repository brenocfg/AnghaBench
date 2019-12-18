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
struct TYPE_2__ {int num; } ;
struct virtqueue {TYPE_1__ vring; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  add_used (struct virtqueue*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  iov_consume (struct iovec*,unsigned int,int) ; 
 int /*<<< orphan*/  iov_empty (struct iovec*,unsigned int) ; 
 unsigned int wait_for_vq_desc (struct virtqueue*,struct iovec*,unsigned int*,unsigned int*) ; 
 int writev (int /*<<< orphan*/ ,struct iovec*,unsigned int) ; 

__attribute__((used)) static void console_output(struct virtqueue *vq)
{
	unsigned int head, out, in;
	struct iovec iov[vq->vring.num];

	/* We usually wait in here, for the Guest to give us something. */
	head = wait_for_vq_desc(vq, iov, &out, &in);
	if (in)
		errx(1, "Input buffers in console output queue?");

	/* writev can return a partial write, so we loop here. */
	while (!iov_empty(iov, out)) {
		int len = writev(STDOUT_FILENO, iov, out);
		if (len <= 0)
			err(1, "Write to stdout gave %i", len);
		iov_consume(iov, out, len);
	}

	/*
	 * We're finished with that buffer: if we're going to sleep,
	 * wait_for_vq_desc() will prod the Guest with an interrupt.
	 */
	add_used(vq, head, 0);
}