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
struct if_tcp_ecn_perf_stat {int total_rxmitpkts; int total_txpkts; int rxmit_percent; int total_oopkts; int total_rxpkts; int oo_percent; int total_reorderpkts; int reorder_percent; } ;

/* Variables and functions */

__attribute__((used)) static void
nstat_ifnet_compute_percentages(struct if_tcp_ecn_perf_stat *ifst)
{
	/* Retransmit percentage */
	if (ifst->total_rxmitpkts > 0 && ifst->total_txpkts > 0) {
		/* shift by 10 for precision */
		ifst->rxmit_percent =
		    ((ifst->total_rxmitpkts << 10) * 100) / ifst->total_txpkts;
	} else {
		ifst->rxmit_percent = 0;
	}

	/* Out-of-order percentage */
	if (ifst->total_oopkts > 0 && ifst->total_rxpkts > 0) {
		/* shift by 10 for precision */
		ifst->oo_percent =
		    ((ifst->total_oopkts << 10) * 100) / ifst->total_rxpkts;
	} else {
		ifst->oo_percent = 0;
	}

	/* Reorder percentage */
	if (ifst->total_reorderpkts > 0 &&
	    (ifst->total_txpkts + ifst->total_rxpkts) > 0) {
		/* shift by 10 for precision */
		ifst->reorder_percent =
		    ((ifst->total_reorderpkts << 10) * 100) /
		    (ifst->total_txpkts + ifst->total_rxpkts);
	} else {
		ifst->reorder_percent = 0;
	}
}