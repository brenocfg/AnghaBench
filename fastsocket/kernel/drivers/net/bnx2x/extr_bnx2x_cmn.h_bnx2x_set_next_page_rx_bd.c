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
struct eth_rx_bd {void* addr_lo; void* addr_hi; } ;
struct bnx2x_fastpath {scalar_t__ rx_desc_mapping; struct eth_rx_bd* rx_desc_ring; } ;

/* Variables and functions */
 int BCM_PAGE_SIZE ; 
 int NUM_RX_RINGS ; 
 int RX_DESC_CNT ; 
 int /*<<< orphan*/  U64_HI (scalar_t__) ; 
 int /*<<< orphan*/  U64_LO (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bnx2x_set_next_page_rx_bd(struct bnx2x_fastpath *fp)
{
	int i;

	for (i = 1; i <= NUM_RX_RINGS; i++) {
		struct eth_rx_bd *rx_bd;

		rx_bd = &fp->rx_desc_ring[RX_DESC_CNT * i - 2];
		rx_bd->addr_hi =
			cpu_to_le32(U64_HI(fp->rx_desc_mapping +
				    BCM_PAGE_SIZE*(i % NUM_RX_RINGS)));
		rx_bd->addr_lo =
			cpu_to_le32(U64_LO(fp->rx_desc_mapping +
				    BCM_PAGE_SIZE*(i % NUM_RX_RINGS)));
	}
}