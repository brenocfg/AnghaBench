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
typedef  int u8 ;
typedef  int u32 ;
struct bnx2fc_rport {int rq_prod_idx; TYPE_1__* conn_db; } ;
struct TYPE_2__ {int rq_prod; } ;

/* Variables and functions */
 int BNX2FC_RQ_WQES_MAX ; 

void bnx2fc_return_rqe(struct bnx2fc_rport *tgt, u8 num_items)
{
	/* return the rq buffer */
	u32 next_prod_idx = tgt->rq_prod_idx + num_items;
	if ((next_prod_idx & 0x7fff) == BNX2FC_RQ_WQES_MAX) {
		/* Wrap around RQ */
		next_prod_idx += 0x8000 - BNX2FC_RQ_WQES_MAX;
	}
	tgt->rq_prod_idx = next_prod_idx;
	tgt->conn_db->rq_prod = tgt->rq_prod_idx;
}