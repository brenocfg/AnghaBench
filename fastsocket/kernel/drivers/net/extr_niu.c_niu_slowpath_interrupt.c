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
typedef  int u64 ;
typedef  int u32 ;
struct tx_ring_info {int tx_channel; } ;
struct rx_ring_info {int rx_channel; } ;
struct niu_ldg {int v0; int v1; int v2; } ;
struct niu {int num_rx_rings; int num_tx_rings; struct tx_ring_info* tx_rings; struct rx_ring_info* rx_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_DMA_CTL_STAT (int) ; 
 int /*<<< orphan*/  RX_DMA_CTL_STAT_MEX ; 
 int niu_device_error (struct niu*) ; 
 int /*<<< orphan*/  niu_enable_interrupts (struct niu*,int /*<<< orphan*/ ) ; 
 int niu_mac_interrupt (struct niu*) ; 
 int niu_mif_interrupt (struct niu*) ; 
 int niu_rx_error (struct niu*,struct rx_ring_info*) ; 
 int niu_tx_error (struct niu*,struct tx_ring_info*) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_slowpath_interrupt(struct niu *np, struct niu_ldg *lp,
			      u64 v0, u64 v1, u64 v2)
{

	int i, err = 0;

	lp->v0 = v0;
	lp->v1 = v1;
	lp->v2 = v2;

	if (v1 & 0x00000000ffffffffULL) {
		u32 rx_vec = (v1 & 0xffffffff);

		for (i = 0; i < np->num_rx_rings; i++) {
			struct rx_ring_info *rp = &np->rx_rings[i];

			if (rx_vec & (1 << rp->rx_channel)) {
				int r = niu_rx_error(np, rp);
				if (r) {
					err = r;
				} else {
					if (!v0)
						nw64(RX_DMA_CTL_STAT(rp->rx_channel),
						     RX_DMA_CTL_STAT_MEX);
				}
			}
		}
	}
	if (v1 & 0x7fffffff00000000ULL) {
		u32 tx_vec = (v1 >> 32) & 0x7fffffff;

		for (i = 0; i < np->num_tx_rings; i++) {
			struct tx_ring_info *rp = &np->tx_rings[i];

			if (tx_vec & (1 << rp->tx_channel)) {
				int r = niu_tx_error(np, rp);
				if (r)
					err = r;
			}
		}
	}
	if ((v0 | v1) & 0x8000000000000000ULL) {
		int r = niu_mif_interrupt(np);
		if (r)
			err = r;
	}
	if (v2) {
		if (v2 & 0x01ef) {
			int r = niu_mac_interrupt(np);
			if (r)
				err = r;
		}
		if (v2 & 0x0210) {
			int r = niu_device_error(np);
			if (r)
				err = r;
		}
	}

	if (err)
		niu_enable_interrupts(np, 0);

	return err;
}