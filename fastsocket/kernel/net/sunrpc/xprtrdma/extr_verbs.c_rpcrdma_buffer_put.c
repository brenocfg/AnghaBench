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
struct rpcrdma_req {scalar_t__ rl_nchunks; TYPE_3__* rl_segments; TYPE_1__* rl_reply; scalar_t__ rl_niovs; struct rpcrdma_buffer* rl_buffer; } ;
struct rpcrdma_mw {int /*<<< orphan*/  mw_list; } ;
struct rpcrdma_ia {int ri_memreg_strategy; } ;
struct rpcrdma_buffer {size_t rb_send_index; size_t rb_recv_index; int /*<<< orphan*/  rb_lock; int /*<<< orphan*/  rb_mws; TYPE_1__** rb_recv_bufs; struct rpcrdma_req** rb_send_bufs; } ;
struct TYPE_5__ {struct rpcrdma_mw* rl_mw; } ;
struct TYPE_6__ {TYPE_2__ mr_chunk; } ;
struct TYPE_4__ {int /*<<< orphan*/ * rr_func; int /*<<< orphan*/  rr_unbind; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  RPCRDMA_FRMR 131 
 int RPCRDMA_MAX_SEGS ; 
#define  RPCRDMA_MEMWINDOWS 130 
#define  RPCRDMA_MEMWINDOWS_ASYNC 129 
#define  RPCRDMA_MTHCAFMR 128 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rpcrdma_ia* rdmab_to_ia (struct rpcrdma_buffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
rpcrdma_buffer_put(struct rpcrdma_req *req)
{
	struct rpcrdma_buffer *buffers = req->rl_buffer;
	struct rpcrdma_ia *ia = rdmab_to_ia(buffers);
	int i;
	unsigned long flags;

	BUG_ON(req->rl_nchunks != 0);
	spin_lock_irqsave(&buffers->rb_lock, flags);
	buffers->rb_send_bufs[--buffers->rb_send_index] = req;
	req->rl_niovs = 0;
	if (req->rl_reply) {
		buffers->rb_recv_bufs[--buffers->rb_recv_index] = req->rl_reply;
		init_waitqueue_head(&req->rl_reply->rr_unbind);
		req->rl_reply->rr_func = NULL;
		req->rl_reply = NULL;
	}
	switch (ia->ri_memreg_strategy) {
	case RPCRDMA_FRMR:
	case RPCRDMA_MTHCAFMR:
	case RPCRDMA_MEMWINDOWS_ASYNC:
	case RPCRDMA_MEMWINDOWS:
		/*
		 * Cycle mw's back in reverse order, and "spin" them.
		 * This delays and scrambles reuse as much as possible.
		 */
		i = 1;
		do {
			struct rpcrdma_mw **mw;
			mw = &req->rl_segments[i].mr_chunk.rl_mw;
			list_add_tail(&(*mw)->mw_list, &buffers->rb_mws);
			*mw = NULL;
		} while (++i < RPCRDMA_MAX_SEGS);
		list_add_tail(&req->rl_segments[0].mr_chunk.rl_mw->mw_list,
					&buffers->rb_mws);
		req->rl_segments[0].mr_chunk.rl_mw = NULL;
		break;
	default:
		break;
	}
	spin_unlock_irqrestore(&buffers->rb_lock, flags);
}