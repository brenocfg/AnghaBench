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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct svcxprt_rdma {int sc_max_sge; } ;
struct TYPE_8__ {int len; } ;
struct svc_rqst {TYPE_4__ rq_res; } ;
struct svc_rdma_req_map {TYPE_2__* frmr; } ;
struct rpcrdma_write_array {int wc_nchunks; TYPE_3__* wc_array; } ;
struct rpcrdma_segment {int rs_length; int /*<<< orphan*/  rs_handle; int /*<<< orphan*/  rs_offset; } ;
struct TYPE_5__ {int /*<<< orphan*/ * rm_chunks; } ;
struct rpcrdma_msg {TYPE_1__ rm_body; } ;
struct TYPE_7__ {struct rpcrdma_segment wc_target; } ;
struct TYPE_6__ {int map_len; } ;

/* Variables and functions */
 int EIO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 scalar_t__ get_unaligned (int /*<<< orphan*/ *) ; 
 int min (int,int) ; 
 int send_write (struct svcxprt_rdma*,struct svc_rqst*,int /*<<< orphan*/ ,scalar_t__,int,int,struct svc_rdma_req_map*) ; 
 struct rpcrdma_write_array* svc_rdma_get_reply_array (struct rpcrdma_msg*) ; 
 int /*<<< orphan*/  svc_rdma_xdr_encode_array_chunk (struct rpcrdma_write_array*,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  svc_rdma_xdr_encode_reply_array (struct rpcrdma_write_array*,int) ; 

__attribute__((used)) static int send_reply_chunks(struct svcxprt_rdma *xprt,
			     struct rpcrdma_msg *rdma_argp,
			     struct rpcrdma_msg *rdma_resp,
			     struct svc_rqst *rqstp,
			     struct svc_rdma_req_map *vec)
{
	u32 xfer_len = rqstp->rq_res.len;
	int write_len;
	int max_write;
	u32 xdr_off;
	int chunk_no;
	int chunk_off;
	struct rpcrdma_segment *ch;
	struct rpcrdma_write_array *arg_ary;
	struct rpcrdma_write_array *res_ary;
	int ret;

	arg_ary = svc_rdma_get_reply_array(rdma_argp);
	if (!arg_ary)
		return 0;
	/* XXX: need to fix when reply lists occur with read-list and or
	 * write-list */
	res_ary = (struct rpcrdma_write_array *)
		&rdma_resp->rm_body.rm_chunks[2];

	if (vec->frmr)
		max_write = vec->frmr->map_len;
	else
		max_write = xprt->sc_max_sge * PAGE_SIZE;

	/* xdr offset starts at RPC message */
	for (xdr_off = 0, chunk_no = 0;
	     xfer_len && chunk_no < arg_ary->wc_nchunks;
	     chunk_no++) {
		u64 rs_offset;
		ch = &arg_ary->wc_array[chunk_no].wc_target;
		write_len = min(xfer_len, ch->rs_length);

		/* Prepare the reply chunk given the length actually
		 * written */
		rs_offset = get_unaligned(&(ch->rs_offset));
		svc_rdma_xdr_encode_array_chunk(res_ary, chunk_no,
					    ch->rs_handle, rs_offset,
					    write_len);
		chunk_off = 0;
		while (write_len) {
			int this_write;

			this_write = min(write_len, max_write);
			ret = send_write(xprt, rqstp,
					 ch->rs_handle,
					 rs_offset + chunk_off,
					 xdr_off,
					 this_write,
					 vec);
			if (ret) {
				dprintk("svcrdma: RDMA_WRITE failed, ret=%d\n",
					ret);
				return -EIO;
			}
			chunk_off += this_write;
			xdr_off += this_write;
			xfer_len -= this_write;
			write_len -= this_write;
		}
	}
	/* Update the req with the number of chunks actually used */
	svc_rdma_xdr_encode_reply_array(res_ary, chunk_no);

	return rqstp->rq_res.len;
}