#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ len; TYPE_3__* head; } ;
struct svc_rqst {TYPE_4__ rq_arg; } ;
struct TYPE_5__ {scalar_t__ rm_align; scalar_t__ rm_thresh; int* rm_pempty; } ;
struct TYPE_6__ {int* rm_chunks; TYPE_1__ rm_padded; } ;
struct rpcrdma_msg {scalar_t__ rm_xid; scalar_t__ rm_vers; scalar_t__ rm_credit; scalar_t__ rm_type; TYPE_2__ rm_body; } ;
struct TYPE_7__ {int* iov_base; int iov_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 scalar_t__ RDMA_MSGP ; 
 scalar_t__ RPCRDMA_HDRLEN_MIN ; 
 scalar_t__ RPCRDMA_VERSION ; 
 int* decode_read_list (int*,int*) ; 
 int* decode_reply_array (int*,int*) ; 
 int* decode_write_list (int*,int*) ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__) ; 
 void* ntohl (scalar_t__) ; 

int svc_rdma_xdr_decode_req(struct rpcrdma_msg **rdma_req,
			    struct svc_rqst *rqstp)
{
	struct rpcrdma_msg *rmsgp = NULL;
	u32 *va;
	u32 *vaend;
	u32 hdr_len;

	rmsgp = (struct rpcrdma_msg *)rqstp->rq_arg.head[0].iov_base;

	/* Verify that there's enough bytes for header + something */
	if (rqstp->rq_arg.len <= RPCRDMA_HDRLEN_MIN) {
		dprintk("svcrdma: header too short = %d\n",
			rqstp->rq_arg.len);
		return -EINVAL;
	}

	/* Decode the header */
	rmsgp->rm_xid = ntohl(rmsgp->rm_xid);
	rmsgp->rm_vers = ntohl(rmsgp->rm_vers);
	rmsgp->rm_credit = ntohl(rmsgp->rm_credit);
	rmsgp->rm_type = ntohl(rmsgp->rm_type);

	if (rmsgp->rm_vers != RPCRDMA_VERSION)
		return -ENOSYS;

	/* Pull in the extra for the padded case and bump our pointer */
	if (rmsgp->rm_type == RDMA_MSGP) {
		int hdrlen;
		rmsgp->rm_body.rm_padded.rm_align =
			ntohl(rmsgp->rm_body.rm_padded.rm_align);
		rmsgp->rm_body.rm_padded.rm_thresh =
			ntohl(rmsgp->rm_body.rm_padded.rm_thresh);

		va = &rmsgp->rm_body.rm_padded.rm_pempty[4];
		rqstp->rq_arg.head[0].iov_base = va;
		hdrlen = (u32)((unsigned long)va - (unsigned long)rmsgp);
		rqstp->rq_arg.head[0].iov_len -= hdrlen;
		if (hdrlen > rqstp->rq_arg.len)
			return -EINVAL;
		return hdrlen;
	}

	/* The chunk list may contain either a read chunk list or a write
	 * chunk list and a reply chunk list.
	 */
	va = &rmsgp->rm_body.rm_chunks[0];
	vaend = (u32 *)((unsigned long)rmsgp + rqstp->rq_arg.len);
	va = decode_read_list(va, vaend);
	if (!va)
		return -EINVAL;
	va = decode_write_list(va, vaend);
	if (!va)
		return -EINVAL;
	va = decode_reply_array(va, vaend);
	if (!va)
		return -EINVAL;

	rqstp->rq_arg.head[0].iov_base = va;
	hdr_len = (unsigned long)va - (unsigned long)rmsgp;
	rqstp->rq_arg.head[0].iov_len -= hdr_len;

	*rdma_req = rmsgp;
	return hdr_len;
}