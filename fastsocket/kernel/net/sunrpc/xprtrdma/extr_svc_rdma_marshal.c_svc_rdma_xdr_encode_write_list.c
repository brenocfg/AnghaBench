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
struct rpcrdma_write_array {TYPE_2__* wc_array; int /*<<< orphan*/  wc_nchunks; int /*<<< orphan*/  wc_discrim; } ;
struct TYPE_6__ {void** rm_chunks; } ;
struct rpcrdma_msg {TYPE_3__ rm_body; } ;
struct TYPE_4__ {void* rs_length; void* rs_handle; } ;
struct TYPE_5__ {TYPE_1__ wc_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  xdr_one ; 
 void* xdr_zero ; 

void svc_rdma_xdr_encode_write_list(struct rpcrdma_msg *rmsgp, int chunks)
{
	struct rpcrdma_write_array *ary;

	/* no read-list */
	rmsgp->rm_body.rm_chunks[0] = xdr_zero;

	/* write-array discrim */
	ary = (struct rpcrdma_write_array *)
		&rmsgp->rm_body.rm_chunks[1];
	ary->wc_discrim = xdr_one;
	ary->wc_nchunks = htonl(chunks);

	/* write-list terminator */
	ary->wc_array[chunks].wc_target.rs_handle = xdr_zero;

	/* reply-array discriminator */
	ary->wc_array[chunks].wc_target.rs_length = xdr_zero;
}