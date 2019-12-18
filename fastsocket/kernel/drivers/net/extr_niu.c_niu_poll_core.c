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
typedef  int u64 ;
typedef  int u32 ;
struct tx_ring_info {int tx_channel; } ;
struct rx_ring_info {int rx_channel; } ;
struct niu_ldg {int v0; int /*<<< orphan*/  napi; } ;
struct niu {int num_tx_rings; int num_rx_rings; struct rx_ring_info* rx_rings; struct tx_ring_info* tx_rings; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  LDN_RXDMA (int) ; 
 int /*<<< orphan*/  LDN_TXDMA (int) ; 
 int /*<<< orphan*/  LD_IM0 (int /*<<< orphan*/ ) ; 
 int niu_rx_work (int /*<<< orphan*/ *,struct niu*,struct rx_ring_info*,int) ; 
 int /*<<< orphan*/  niu_tx_work (struct niu*,struct tx_ring_info*) ; 
 int /*<<< orphan*/  niudbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_poll_core(struct niu *np, struct niu_ldg *lp, int budget)
{
	u64 v0 = lp->v0;
	u32 tx_vec = (v0 >> 32);
	u32 rx_vec = (v0 & 0xffffffff);
	int i, work_done = 0;

	niudbg(INTR, "%s: niu_poll_core() v0[%016llx]\n",
	       np->dev->name, (unsigned long long) v0);

	for (i = 0; i < np->num_tx_rings; i++) {
		struct tx_ring_info *rp = &np->tx_rings[i];
		if (tx_vec & (1 << rp->tx_channel))
			niu_tx_work(np, rp);
		nw64(LD_IM0(LDN_TXDMA(rp->tx_channel)), 0);
	}

	for (i = 0; i < np->num_rx_rings; i++) {
		struct rx_ring_info *rp = &np->rx_rings[i];

		if (rx_vec & (1 << rp->rx_channel)) {
			int this_work_done;

			this_work_done = niu_rx_work(&lp->napi, np, rp,
						     budget);

			budget -= this_work_done;
			work_done += this_work_done;
		}
		nw64(LD_IM0(LDN_RXDMA(rp->rx_channel)), 0);
	}

	return work_done;
}