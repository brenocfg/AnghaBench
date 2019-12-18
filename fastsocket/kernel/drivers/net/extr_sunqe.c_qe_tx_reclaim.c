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
typedef  int u32 ;
struct sunqe {int tx_old; int tx_new; TYPE_1__* qe_block; } ;
struct qe_txd {int tx_flags; } ;
struct TYPE_2__ {struct qe_txd* qe_txd; } ;

/* Variables and functions */
 int NEXT_TX (int) ; 
 int TXD_OWN ; 

__attribute__((used)) static void qe_tx_reclaim(struct sunqe *qep)
{
	struct qe_txd *txbase = &qep->qe_block->qe_txd[0];
	int elem = qep->tx_old;

	while (elem != qep->tx_new) {
		u32 flags = txbase[elem].tx_flags;

		if (flags & TXD_OWN)
			break;
		elem = NEXT_TX(elem);
	}
	qep->tx_old = elem;
}