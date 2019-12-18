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
typedef  int u32 ;
typedef  void* u16 ;
struct ustorm_eth_rx_producers {void* sge_prod; void* cqe_prod; void* bd_prod; int /*<<< orphan*/  member_0; } ;
struct bnx2x_fastpath {int /*<<< orphan*/  index; scalar_t__ ustorm_rx_prods_offset; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  rx_prods ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,void*,void*) ; 
 int /*<<< orphan*/  NETIF_MSG_RX_STATUS ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void bnx2x_update_rx_prod(struct bnx2x *bp,
					struct bnx2x_fastpath *fp,
					u16 bd_prod, u16 rx_comp_prod,
					u16 rx_sge_prod)
{
	struct ustorm_eth_rx_producers rx_prods = {0};
	u32 i;

	/* Update producers */
	rx_prods.bd_prod = bd_prod;
	rx_prods.cqe_prod = rx_comp_prod;
	rx_prods.sge_prod = rx_sge_prod;

	/* Make sure that the BD and SGE data is updated before updating the
	 * producers since FW might read the BD/SGE right after the producer
	 * is updated.
	 * This is only applicable for weak-ordered memory model archs such
	 * as IA-64. The following barrier is also mandatory since FW will
	 * assumes BDs must have buffers.
	 */
	wmb();

	for (i = 0; i < sizeof(rx_prods)/4; i++)
		REG_WR(bp, fp->ustorm_rx_prods_offset + i*4,
		       ((u32 *)&rx_prods)[i]);

	mmiowb(); /* keep prod updates ordered */

	DP(NETIF_MSG_RX_STATUS,
	   "queue[%d]:  wrote  bd_prod %u  cqe_prod %u  sge_prod %u\n",
	   fp->index, bd_prod, rx_comp_prod, rx_sge_prod);
}