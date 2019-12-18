#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sge_ofld_txq {int /*<<< orphan*/  qresume_tsk; } ;
struct TYPE_5__ {scalar_t__ in_use; } ;
struct sge_eth_txq {TYPE_3__* txq; TYPE_1__ q; } ;
struct sge {unsigned long* txq_maperr; unsigned int ethtxq_rover; unsigned int ethqsets; int /*<<< orphan*/  tx_timer; struct sge_eth_txq* ethtxq; struct sge_ofld_txq** egr_map; } ;
struct adapter {struct sge sge; } ;
struct TYPE_6__ {scalar_t__ trans_start; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned long*) ; 
 unsigned int BITS_PER_LONG ; 
 int HZ ; 
 unsigned int MAX_TIMER_TX_RECLAIM ; 
 int TX_QCHECK_PERIOD ; 
 unsigned int __ffs (unsigned long) ; 
 scalar_t__ __netif_tx_trylock (TYPE_3__*) ; 
 int /*<<< orphan*/  __netif_tx_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  clear_bit (unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  free_tx_desc (struct adapter*,TYPE_1__*,int,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int reclaimable (TYPE_1__*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void sge_tx_timer_cb(unsigned long data)
{
	unsigned long m;
	unsigned int i, budget;
	struct adapter *adap = (struct adapter *)data;
	struct sge *s = &adap->sge;

	for (i = 0; i < ARRAY_SIZE(s->txq_maperr); i++)
		for (m = s->txq_maperr[i]; m; m &= m - 1) {
			unsigned long id = __ffs(m) + i * BITS_PER_LONG;
			struct sge_ofld_txq *txq = s->egr_map[id];

			clear_bit(id, s->txq_maperr);
			tasklet_schedule(&txq->qresume_tsk);
		}

	budget = MAX_TIMER_TX_RECLAIM;
	i = s->ethtxq_rover;
	do {
		struct sge_eth_txq *q = &s->ethtxq[i];

		if (q->q.in_use &&
		    time_after_eq(jiffies, q->txq->trans_start + HZ / 100) &&
		    __netif_tx_trylock(q->txq)) {
			int avail = reclaimable(&q->q);

			if (avail) {
				if (avail > budget)
					avail = budget;

				free_tx_desc(adap, &q->q, avail, true);
				q->q.in_use -= avail;
				budget -= avail;
			}
			__netif_tx_unlock(q->txq);
		}

		if (++i >= s->ethqsets)
			i = 0;
	} while (budget && i != s->ethtxq_rover);
	s->ethtxq_rover = i;
	mod_timer(&s->tx_timer, jiffies + (budget ? TX_QCHECK_PERIOD : 2));
}