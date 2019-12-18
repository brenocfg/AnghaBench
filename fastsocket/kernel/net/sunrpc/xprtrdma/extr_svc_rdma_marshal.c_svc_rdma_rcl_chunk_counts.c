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
struct TYPE_2__ {int rs_length; } ;
struct rpcrdma_read_chunk {scalar_t__ rc_discrim; TYPE_1__ rc_target; } ;

/* Variables and functions */

void svc_rdma_rcl_chunk_counts(struct rpcrdma_read_chunk *ch,
			       int *ch_count, int *byte_count)
{
	/* compute the number of bytes represented by read chunks */
	*byte_count = 0;
	*ch_count = 0;
	for (; ch->rc_discrim != 0; ch++) {
		*byte_count = *byte_count + ch->rc_target.rs_length;
		*ch_count = *ch_count + 1;
	}
}