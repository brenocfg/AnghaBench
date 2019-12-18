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
typedef  int u16 ;
struct tx_ring_info {int tx_cs; int last_pkt_cnt; int cons; } ;
struct niu {TYPE_1__* dev; struct tx_ring_info* tx_rings; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ NIU_TX_WAKEUP_THRESH (struct tx_ring_info*) ; 
 int TX_CS_MK ; 
 int TX_CS_MMK ; 
 int TX_CS_PKT_CNT ; 
 int TX_CS_PKT_CNT_SHIFT ; 
 int /*<<< orphan*/  TX_DONE ; 
 int /*<<< orphan*/  __netif_tx_lock (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 struct netdev_queue* netdev_get_tx_queue (TYPE_1__*,int) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 scalar_t__ niu_tx_avail (struct tx_ring_info*) ; 
 int /*<<< orphan*/  niudbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int release_tx_packet (struct niu*,struct tx_ring_info*,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void niu_tx_work(struct niu *np, struct tx_ring_info *rp)
{
	struct netdev_queue *txq;
	u16 pkt_cnt, tmp;
	int cons, index;
	u64 cs;

	index = (rp - np->tx_rings);
	txq = netdev_get_tx_queue(np->dev, index);

	cs = rp->tx_cs;
	if (unlikely(!(cs & (TX_CS_MK | TX_CS_MMK))))
		goto out;

	tmp = pkt_cnt = (cs & TX_CS_PKT_CNT) >> TX_CS_PKT_CNT_SHIFT;
	pkt_cnt = (pkt_cnt - rp->last_pkt_cnt) &
		(TX_CS_PKT_CNT >> TX_CS_PKT_CNT_SHIFT);

	rp->last_pkt_cnt = tmp;

	cons = rp->cons;

	niudbg(TX_DONE, "%s: niu_tx_work() pkt_cnt[%u] cons[%d]\n",
	       np->dev->name, pkt_cnt, cons);

	while (pkt_cnt--)
		cons = release_tx_packet(np, rp, cons);

	rp->cons = cons;
	smp_mb();

out:
	if (unlikely(netif_tx_queue_stopped(txq) &&
		     (niu_tx_avail(rp) > NIU_TX_WAKEUP_THRESH(rp)))) {
		__netif_tx_lock(txq, smp_processor_id());
		if (netif_tx_queue_stopped(txq) &&
		    (niu_tx_avail(rp) > NIU_TX_WAKEUP_THRESH(rp)))
			netif_tx_wake_queue(txq);
		__netif_tx_unlock(txq);
	}
}