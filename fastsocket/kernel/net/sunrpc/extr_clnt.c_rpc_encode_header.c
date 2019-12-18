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
struct TYPE_5__ {TYPE_1__* rpc_proc; } ;
struct rpc_task {TYPE_2__ tk_msg; int /*<<< orphan*/  tk_xprt; struct rpc_rqst* tk_rqstp; struct rpc_clnt* tk_client; } ;
struct rpc_rqst {TYPE_3__* rq_svec; int /*<<< orphan*/  rq_slen; int /*<<< orphan*/  rq_xid; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_vers; int /*<<< orphan*/  cl_prog; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/ * iov_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_CALL ; 
 int /*<<< orphan*/  RPC_VERSION ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rpcauth_marshcred (struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_adjust_iovec (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xprt_skip_transport_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32 *
rpc_encode_header(struct rpc_task *task)
{
	struct rpc_clnt *clnt = task->tk_client;
	struct rpc_rqst	*req = task->tk_rqstp;
	__be32		*p = req->rq_svec[0].iov_base;

	/* FIXME: check buffer size? */

	p = xprt_skip_transport_header(task->tk_xprt, p);
	*p++ = req->rq_xid;		/* XID */
	*p++ = htonl(RPC_CALL);		/* CALL */
	*p++ = htonl(RPC_VERSION);	/* RPC version */
	*p++ = htonl(clnt->cl_prog);	/* program number */
	*p++ = htonl(clnt->cl_vers);	/* program version */
	*p++ = htonl(task->tk_msg.rpc_proc->p_proc);	/* procedure */
	p = rpcauth_marshcred(task, p);
	req->rq_slen = xdr_adjust_iovec(&req->rq_svec[0], p);
	return p;
}