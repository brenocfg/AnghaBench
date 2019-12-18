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
struct xdr_stream {int dummy; } ;
struct rpcbind_args {unsigned long r_port; } ;
struct TYPE_4__ {TYPE_1__* rpc_proc; } ;
struct rpc_task {TYPE_2__ tk_msg; int /*<<< orphan*/  tk_pid; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; struct rpc_task* rq_task; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long USHORT_MAX ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdr_init_decode (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int rpcb_dec_getport(struct rpc_rqst *req, __be32 *p,
			    struct rpcbind_args *rpcb)
{
	struct rpc_task *task = req->rq_task;
	struct xdr_stream xdr;
	unsigned long port;

	xdr_init_decode(&xdr, &req->rq_rcv_buf, p);

	rpcb->r_port = 0;

	p = xdr_inline_decode(&xdr, sizeof(__be32));
	if (unlikely(p == NULL))
		return -EIO;

	port = ntohl(*p);
	dprintk("RPC: %5u PMAP_%s result: %lu\n", task->tk_pid,
			task->tk_msg.rpc_proc->p_name, port);
	if (unlikely(port > USHORT_MAX))
		return -EIO;

	rpcb->r_port = port;
	return 0;
}