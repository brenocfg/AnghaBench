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
struct svcxprt_rdma {int sc_max_requests; } ;
struct TYPE_2__ {void** rm_chunks; } ;
struct rpcrdma_msg {int rm_xid; int rm_vers; TYPE_1__ rm_body; void* rm_type; void* rm_credit; } ;
typedef  enum rpcrdma_proc { ____Placeholder_rpcrdma_proc } rpcrdma_proc ;

/* Variables and functions */
 void* htonl (int) ; 
 void* xdr_zero ; 

void svc_rdma_xdr_encode_reply_header(struct svcxprt_rdma *xprt,
				  struct rpcrdma_msg *rdma_argp,
				  struct rpcrdma_msg *rdma_resp,
				  enum rpcrdma_proc rdma_type)
{
	rdma_resp->rm_xid = htonl(rdma_argp->rm_xid);
	rdma_resp->rm_vers = htonl(rdma_argp->rm_vers);
	rdma_resp->rm_credit = htonl(xprt->sc_max_requests);
	rdma_resp->rm_type = htonl(rdma_type);

	/* Encode <nul> chunks lists */
	rdma_resp->rm_body.rm_chunks[0] = xdr_zero;
	rdma_resp->rm_body.rm_chunks[1] = xdr_zero;
	rdma_resp->rm_body.rm_chunks[2] = xdr_zero;
}