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
typedef  size_t u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * sgl; } ;
struct eth_end_agg_rx_cqe {TYPE_1__ sgl_or_raw_data; } ;
struct bnx2x_fastpath {size_t last_max_sge; size_t rx_sge_prod; int /*<<< orphan*/ * sge_mask; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_VEC64_CLEAR_BIT (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  BIT_VEC64_ELEM_ONE_MASK ; 
 size_t BIT_VEC64_ELEM_SHIFT ; 
 size_t BIT_VEC64_ELEM_SZ ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  NETIF_MSG_RX_STATUS ; 
 size_t NEXT_SGE_MASK_ELEM (size_t) ; 
 size_t RX_SGE (size_t) ; 
 int /*<<< orphan*/  bnx2x_clear_sge_mask_next_elems (struct bnx2x_fastpath*) ; 
 int /*<<< orphan*/  bnx2x_update_last_max_sge (struct bnx2x_fastpath*,size_t) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (void*) ; 

__attribute__((used)) static inline void bnx2x_update_sge_prod(struct bnx2x_fastpath *fp,
					 u16 sge_len,
					 struct eth_end_agg_rx_cqe *cqe)
{
	struct bnx2x *bp = fp->bp;
	u16 last_max, last_elem, first_elem;
	u16 delta = 0;
	u16 i;

	if (!sge_len)
		return;

	/* First mark all used pages */
	for (i = 0; i < sge_len; i++)
		BIT_VEC64_CLEAR_BIT(fp->sge_mask,
			RX_SGE(le16_to_cpu(cqe->sgl_or_raw_data.sgl[i])));

	DP(NETIF_MSG_RX_STATUS, "fp_cqe->sgl[%d] = %d\n",
	   sge_len - 1, le16_to_cpu(cqe->sgl_or_raw_data.sgl[sge_len - 1]));

	/* Here we assume that the last SGE index is the biggest */
	prefetch((void *)(fp->sge_mask));
	bnx2x_update_last_max_sge(fp,
		le16_to_cpu(cqe->sgl_or_raw_data.sgl[sge_len - 1]));

	last_max = RX_SGE(fp->last_max_sge);
	last_elem = last_max >> BIT_VEC64_ELEM_SHIFT;
	first_elem = RX_SGE(fp->rx_sge_prod) >> BIT_VEC64_ELEM_SHIFT;

	/* If ring is not full */
	if (last_elem + 1 != first_elem)
		last_elem++;

	/* Now update the prod */
	for (i = first_elem; i != last_elem; i = NEXT_SGE_MASK_ELEM(i)) {
		if (likely(fp->sge_mask[i]))
			break;

		fp->sge_mask[i] = BIT_VEC64_ELEM_ONE_MASK;
		delta += BIT_VEC64_ELEM_SZ;
	}

	if (delta > 0) {
		fp->rx_sge_prod += delta;
		/* clear page-end entries */
		bnx2x_clear_sge_mask_next_elems(fp);
	}

	DP(NETIF_MSG_RX_STATUS,
	   "fp->last_max_sge = %d  fp->rx_sge_prod = %d\n",
	   fp->last_max_sge, fp->rx_sge_prod);
}