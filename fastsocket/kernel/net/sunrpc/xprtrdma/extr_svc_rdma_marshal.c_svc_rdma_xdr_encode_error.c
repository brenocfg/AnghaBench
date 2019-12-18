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
typedef  int /*<<< orphan*/  u32 ;
struct svcxprt_rdma {int sc_max_requests; } ;
struct rpcrdma_msg {int rm_xid; int rm_vers; } ;
typedef  enum rpcrdma_errcode { ____Placeholder_rpcrdma_errcode } rpcrdma_errcode ;

/* Variables and functions */
 int ERR_VERS ; 
 int RDMA_ERROR ; 
 int RPCRDMA_VERSION ; 
 void* htonl (int) ; 

int svc_rdma_xdr_encode_error(struct svcxprt_rdma *xprt,
			      struct rpcrdma_msg *rmsgp,
			      enum rpcrdma_errcode err, u32 *va)
{
	u32 *startp = va;

	*va++ = htonl(rmsgp->rm_xid);
	*va++ = htonl(rmsgp->rm_vers);
	*va++ = htonl(xprt->sc_max_requests);
	*va++ = htonl(RDMA_ERROR);
	*va++ = htonl(err);
	if (err == ERR_VERS) {
		*va++ = htonl(RPCRDMA_VERSION);
		*va++ = htonl(RPCRDMA_VERSION);
	}

	return (int)((unsigned long)va - (unsigned long)startp);
}