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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct rpcrdma_write_chunk {int dummy; } ;
struct rpcrdma_write_array {scalar_t__ wc_discrim; scalar_t__ wc_nchunks; TYPE_2__* wc_array; } ;
struct TYPE_3__ {scalar_t__ rs_handle; scalar_t__ rs_length; int /*<<< orphan*/  rs_offset; } ;
struct TYPE_4__ {TYPE_1__ wc_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,struct rpcrdma_write_array*,int,...) ; 
 void* ntohl (scalar_t__) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static u32 *decode_write_list(u32 *va, u32 *vaend)
{
	int ch_no;
	struct rpcrdma_write_array *ary =
		(struct rpcrdma_write_array *)va;

	/* Check for not write-array */
	if (ary->wc_discrim == xdr_zero)
		return (u32 *)&ary->wc_nchunks;

	if ((unsigned long)ary + sizeof(struct rpcrdma_write_array) >
	    (unsigned long)vaend) {
		dprintk("svcrdma: ary=%p, vaend=%p\n", ary, vaend);
		return NULL;
	}
	ary->wc_discrim = ntohl(ary->wc_discrim);
	ary->wc_nchunks = ntohl(ary->wc_nchunks);
	if (((unsigned long)&ary->wc_array[0] +
	     (sizeof(struct rpcrdma_write_chunk) * ary->wc_nchunks)) >
	    (unsigned long)vaend) {
		dprintk("svcrdma: ary=%p, wc_nchunks=%d, vaend=%p\n",
			ary, ary->wc_nchunks, vaend);
		return NULL;
	}
	for (ch_no = 0; ch_no < ary->wc_nchunks; ch_no++) {
		u64 ch_offset;

		ary->wc_array[ch_no].wc_target.rs_handle =
			ntohl(ary->wc_array[ch_no].wc_target.rs_handle);
		ary->wc_array[ch_no].wc_target.rs_length =
			ntohl(ary->wc_array[ch_no].wc_target.rs_length);
		va = (u32 *)&ary->wc_array[ch_no].wc_target.rs_offset;
		xdr_decode_hyper(va, &ch_offset);
		put_unaligned(ch_offset, (u64 *)va);
	}

	/*
	 * rs_length is the 2nd 4B field in wc_target and taking its
	 * address skips the list terminator
	 */
	return (u32 *)&ary->wc_array[ch_no].wc_target.rs_length;
}