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
struct rpcrdma_write_array {int /*<<< orphan*/  wc_nchunks; TYPE_3__* wc_array; scalar_t__ wc_discrim; } ;
struct TYPE_4__ {int /*<<< orphan*/ * rm_chunks; } ;
struct rpcrdma_msg {TYPE_1__ rm_body; } ;
struct TYPE_5__ {int /*<<< orphan*/  rs_length; } ;
struct TYPE_6__ {TYPE_2__ wc_target; } ;

/* Variables and functions */
 size_t ntohl (int /*<<< orphan*/ ) ; 

int svc_rdma_xdr_get_reply_hdr_len(struct rpcrdma_msg *rmsgp)
{
	struct rpcrdma_write_array *wr_ary;

	/* There is no read-list in a reply */

	/* skip write list */
	wr_ary = (struct rpcrdma_write_array *)
		&rmsgp->rm_body.rm_chunks[1];
	if (wr_ary->wc_discrim)
		wr_ary = (struct rpcrdma_write_array *)
			&wr_ary->wc_array[ntohl(wr_ary->wc_nchunks)].
			wc_target.rs_length;
	else
		wr_ary = (struct rpcrdma_write_array *)
			&wr_ary->wc_nchunks;

	/* skip reply array */
	if (wr_ary->wc_discrim)
		wr_ary = (struct rpcrdma_write_array *)
			&wr_ary->wc_array[ntohl(wr_ary->wc_nchunks)];
	else
		wr_ary = (struct rpcrdma_write_array *)
			&wr_ary->wc_nchunks;

	return (unsigned long) wr_ary - (unsigned long) rmsgp;
}