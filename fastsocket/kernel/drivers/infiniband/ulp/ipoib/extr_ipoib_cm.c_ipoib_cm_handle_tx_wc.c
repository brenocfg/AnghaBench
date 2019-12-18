#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct ipoib_neigh {int /*<<< orphan*/ * cm; } ;
struct TYPE_7__ {int /*<<< orphan*/  reap_task; int /*<<< orphan*/  reap_list; } ;
struct ipoib_dev_priv {unsigned int tx_outstanding; int /*<<< orphan*/  lock; TYPE_3__ cm; int /*<<< orphan*/  flags; int /*<<< orphan*/  ca; } ;
struct ipoib_cm_tx_buf {TYPE_4__* skb; int /*<<< orphan*/  mapping; } ;
struct ipoib_cm_tx {int /*<<< orphan*/  flags; int /*<<< orphan*/  list; struct ipoib_neigh* neigh; int /*<<< orphan*/  tx_tail; struct ipoib_cm_tx_buf* tx_ring; } ;
struct ib_wc {unsigned int wr_id; int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  status; TYPE_1__* qp; } ;
struct TYPE_8__ {scalar_t__ len; } ;
struct TYPE_5__ {struct ipoib_cm_tx* qp_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  IPOIB_FLAG_ADMIN_UP ; 
 int /*<<< orphan*/  IPOIB_FLAG_INITIALIZED ; 
 int /*<<< orphan*/  IPOIB_FLAG_OPER_UP ; 
 unsigned int IPOIB_OP_CM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_4__*) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dbg_data (struct ipoib_dev_priv*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_neigh_free (struct ipoib_neigh*) ; 
 unsigned int ipoib_sendq_size ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void ipoib_cm_handle_tx_wc(struct net_device *dev, struct ib_wc *wc)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_cm_tx *tx = wc->qp->qp_context;
	unsigned int wr_id = wc->wr_id & ~IPOIB_OP_CM;
	struct ipoib_cm_tx_buf *tx_req;
	unsigned long flags;

	ipoib_dbg_data(priv, "cm send completion: id %d, status: %d\n",
		       wr_id, wc->status);

	if (unlikely(wr_id >= ipoib_sendq_size)) {
		ipoib_warn(priv, "cm send completion event with wrid %d (> %d)\n",
			   wr_id, ipoib_sendq_size);
		return;
	}

	tx_req = &tx->tx_ring[wr_id];

	ib_dma_unmap_single(priv->ca, tx_req->mapping, tx_req->skb->len, DMA_TO_DEVICE);

	/* FIXME: is this right? Shouldn't we only increment on success? */
	++dev->stats.tx_packets;
	dev->stats.tx_bytes += tx_req->skb->len;

	dev_kfree_skb_any(tx_req->skb);

	netif_tx_lock(dev);

	++tx->tx_tail;
	if (unlikely(--priv->tx_outstanding == ipoib_sendq_size >> 1) &&
	    netif_queue_stopped(dev) &&
	    test_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags))
		netif_wake_queue(dev);

	if (wc->status != IB_WC_SUCCESS &&
	    wc->status != IB_WC_WR_FLUSH_ERR) {
		struct ipoib_neigh *neigh;

		ipoib_dbg(priv, "failed cm send event "
			   "(status=%d, wrid=%d vend_err %x)\n",
			   wc->status, wr_id, wc->vendor_err);

		spin_lock_irqsave(&priv->lock, flags);
		neigh = tx->neigh;

		if (neigh) {
			neigh->cm = NULL;
			ipoib_neigh_free(neigh);

			tx->neigh = NULL;
		}

		if (test_and_clear_bit(IPOIB_FLAG_INITIALIZED, &tx->flags)) {
			list_move(&tx->list, &priv->cm.reap_list);
			queue_work(ipoib_workqueue, &priv->cm.reap_task);
		}

		clear_bit(IPOIB_FLAG_OPER_UP, &tx->flags);

		spin_unlock_irqrestore(&priv->lock, flags);
	}

	netif_tx_unlock(dev);
}