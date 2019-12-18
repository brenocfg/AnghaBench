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
struct eth_rx_cqe_next_page {void* addr_lo; void* addr_hi; } ;
struct bnx2x_fastpath {scalar_t__ rx_comp_mapping; int /*<<< orphan*/ * rx_comp_ring; } ;

/* Variables and functions */
 int BCM_PAGE_SIZE ; 
 int NUM_RCQ_RINGS ; 
 int RCQ_DESC_CNT ; 
 int /*<<< orphan*/  U64_HI (scalar_t__) ; 
 int /*<<< orphan*/  U64_LO (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_set_next_page_rx_cq(struct bnx2x_fastpath *fp)
{
	int i;

	for (i = 1; i <= NUM_RCQ_RINGS; i++) {
		struct eth_rx_cqe_next_page *nextpg;

		nextpg = (struct eth_rx_cqe_next_page *)
			&fp->rx_comp_ring[RCQ_DESC_CNT * i - 1];
		nextpg->addr_hi =
			cpu_to_le32(U64_HI(fp->rx_comp_mapping +
				   BCM_PAGE_SIZE*(i % NUM_RCQ_RINGS)));
		nextpg->addr_lo =
			cpu_to_le32(U64_LO(fp->rx_comp_mapping +
				   BCM_PAGE_SIZE*(i % NUM_RCQ_RINGS)));
	}
}