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
struct rpcrdma_rep {int /*<<< orphan*/ * rr_func; struct rpcrdma_buffer* rr_buffer; } ;
struct rpcrdma_buffer {size_t rb_recv_index; int /*<<< orphan*/  rb_lock; struct rpcrdma_rep** rb_recv_bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
rpcrdma_recv_buffer_put(struct rpcrdma_rep *rep)
{
	struct rpcrdma_buffer *buffers = rep->rr_buffer;
	unsigned long flags;

	rep->rr_func = NULL;
	spin_lock_irqsave(&buffers->rb_lock, flags);
	buffers->rb_recv_bufs[--buffers->rb_recv_index] = rep;
	spin_unlock_irqrestore(&buffers->rb_lock, flags);
}