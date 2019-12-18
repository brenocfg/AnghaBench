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
struct sk_buff {unsigned int priority; } ;
struct sge_txq {unsigned int size; unsigned int in_use; unsigned int gen; unsigned int pidx; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  sendq; int /*<<< orphan*/  stops; } ;
struct sge_qset {int /*<<< orphan*/  txq_stopped; int /*<<< orphan*/  netdev; struct sge_txq* txq; } ;
struct port_info {struct adapter* adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_KDOORBELL ; 
 int F_SELEGRCNTX ; 
 size_t TXQ_LAST_PKT_DB ; 
 size_t TXQ_OFLD ; 
 size_t TXQ_RUNNING ; 
 int /*<<< orphan*/  TX_RECLAIM_CHUNK ; 
 int V_EGRCNTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct port_info* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reclaim_completed_tx (struct adapter*,struct sge_txq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ should_restart_tx (struct sge_txq*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  write_ofld_wr (struct adapter*,struct sk_buff*,struct sge_txq*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void restart_offloadq(unsigned long data)
{
	struct sk_buff *skb;
	struct sge_qset *qs = (struct sge_qset *)data;
	struct sge_txq *q = &qs->txq[TXQ_OFLD];
	const struct port_info *pi = netdev_priv(qs->netdev);
	struct adapter *adap = pi->adapter;

	spin_lock(&q->lock);
again:	reclaim_completed_tx(adap, q, TX_RECLAIM_CHUNK);

	while ((skb = skb_peek(&q->sendq)) != NULL) {
		unsigned int gen, pidx;
		unsigned int ndesc = skb->priority;

		if (unlikely(q->size - q->in_use < ndesc)) {
			set_bit(TXQ_OFLD, &qs->txq_stopped);
			smp_mb__after_clear_bit();

			if (should_restart_tx(q) &&
			    test_and_clear_bit(TXQ_OFLD, &qs->txq_stopped))
				goto again;
			q->stops++;
			break;
		}

		gen = q->gen;
		q->in_use += ndesc;
		pidx = q->pidx;
		q->pidx += ndesc;
		if (q->pidx >= q->size) {
			q->pidx -= q->size;
			q->gen ^= 1;
		}
		__skb_unlink(skb, &q->sendq);
		spin_unlock(&q->lock);

		write_ofld_wr(adap, skb, q, pidx, gen, ndesc);
		spin_lock(&q->lock);
	}
	spin_unlock(&q->lock);

#if USE_GTS
	set_bit(TXQ_RUNNING, &q->flags);
	set_bit(TXQ_LAST_PKT_DB, &q->flags);
#endif
	wmb();
	t3_write_reg(adap, A_SG_KDOORBELL,
		     F_SELEGRCNTX | V_EGRCNTX(q->cntxt_id));
}