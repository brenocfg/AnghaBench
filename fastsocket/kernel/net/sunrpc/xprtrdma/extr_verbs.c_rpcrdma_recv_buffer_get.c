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
struct TYPE_2__ {scalar_t__ length; } ;
struct rpcrdma_req {int /*<<< orphan*/ * rl_reply; struct rpcrdma_buffer* rl_buffer; TYPE_1__ rl_iov; } ;
struct rpcrdma_buffer {size_t rb_recv_index; size_t rb_max_requests; int /*<<< orphan*/  rb_lock; int /*<<< orphan*/ ** rb_recv_bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
rpcrdma_recv_buffer_get(struct rpcrdma_req *req)
{
	struct rpcrdma_buffer *buffers = req->rl_buffer;
	unsigned long flags;

	if (req->rl_iov.length == 0)	/* special case xprt_rdma_allocate() */
		buffers = ((struct rpcrdma_req *) buffers)->rl_buffer;
	spin_lock_irqsave(&buffers->rb_lock, flags);
	if (buffers->rb_recv_index < buffers->rb_max_requests) {
		req->rl_reply = buffers->rb_recv_bufs[buffers->rb_recv_index];
		buffers->rb_recv_bufs[buffers->rb_recv_index++] = NULL;
	}
	spin_unlock_irqrestore(&buffers->rb_lock, flags);
}