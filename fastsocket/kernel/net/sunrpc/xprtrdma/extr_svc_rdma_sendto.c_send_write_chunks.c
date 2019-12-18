#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct svcxprt_rdma {int sc_max_sge; } ;
struct TYPE_12__ {int page_len; TYPE_5__* tail; TYPE_3__* head; } ;
struct svc_rqst {TYPE_6__ rq_res; } ;
struct svc_rdma_req_map {TYPE_2__* frmr; } ;
struct rpcrdma_write_array {int wc_nchunks; TYPE_4__* wc_array; } ;
struct rpcrdma_segment {int rs_length; int /*<<< orphan*/  rs_handle; int /*<<< orphan*/  rs_offset; } ;
struct TYPE_7__ {int /*<<< orphan*/ * rm_chunks; } ;
struct rpcrdma_msg {TYPE_1__ rm_body; } ;
struct TYPE_11__ {int iov_len; } ;
struct TYPE_10__ {struct rpcrdma_segment wc_target; } ;
struct TYPE_9__ {int iov_len; } ;
struct TYPE_8__ {int map_len; } ;

/* Variables and functions */
 int EIO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 scalar_t__ get_unaligned (int /*<<< orphan*/ *) ; 
 int min (int,int) ; 
 int send_write (struct svcxprt_rdma*,struct svc_rqst*,int /*<<< orphan*/ ,scalar_t__,int,int,struct svc_rdma_req_map*) ; 
 struct rpcrdma_write_array* svc_rdma_get_write_array (struct rpcrdma_msg*) ; 
 int /*<<< orphan*/  svc_rdma_xdr_encode_array_chunk (struct rpcrdma_write_array*,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  svc_rdma_xdr_encode_write_list (struct rpcrdma_msg*,int) ; 

__attribute__((used)) static int send_write_chunks(struct svcxprt_rdma *xprt,
			     struct rpcrdma_msg *rdma_argp,
			     struct rpcrdma_msg *rdma_resp,
			     struct svc_rqst *rqstp,
			     struct svc_rdma_req_map *vec)
{
	u32 xfer_len = rqstp->rq_res.page_len + rqstp->rq_res.tail[0].iov_len;
	int write_len;
	int max_write;
	u32 xdr_off;
	int chunk_off;
	int chunk_no;
	struct rpcrdma_write_array *arg_ary;
	struct rpcrdma_write_array *res_ary;
	int ret;

	arg_ary = svc_rdma_get_write_array(rdma_argp);
	if (!arg_ary)
		return 0;
	res_ary = (struct rpcrdma_write_array *)
		&rdma_resp->rm_body.rm_chunks[1];

	if (vec->frmr)
		max_write = vec->frmr->map_len;
	else
		max_write = xprt->sc_max_sge * PAGE_SIZE;

	/* Write chunks start at the pagelist */
	for (xdr_off = rqstp->rq_res.head[0].iov_len, chunk_no = 0;
	     xfer_len && chunk_no < arg_ary->wc_nchunks;
	     chunk_no++) {
		struct rpcrdma_segment *arg_ch;
		u64 rs_offset;

		arg_ch = &arg_ary->wc_array[chunk_no].wc_target;
		write_len = min(xfer_len, arg_ch->rs_length);

		/* Prepare the response chunk given the length actually
		 * written */
		rs_offset = get_unaligned(&(arg_ch->rs_offset));
		svc_rdma_xdr_encode_array_chunk(res_ary, chunk_no,
					    arg_ch->rs_handle,
					    rs_offset,
					    write_len);
		chunk_off = 0;
		while (write_len) {
			int this_write;
			this_write = min(write_len, max_write);
			ret = send_write(xprt, rqstp,
					 arg_ch->rs_handle,
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
	svc_rdma_xdr_encode_write_list(rdma_resp, chunk_no);

	return rqstp->rq_res.page_len + rqstp->rq_res.tail[0].iov_len;
}