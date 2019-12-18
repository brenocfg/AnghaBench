#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int /*<<< orphan*/  trans_start; TYPE_1__ stats; } ;
struct ipoib_dev_priv {int tx_outstanding; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  ca; } ;
struct ipoib_cm_tx_buf {int /*<<< orphan*/  mapping; struct sk_buff* skb; } ;
struct ipoib_cm_tx {scalar_t__ mtu; int tx_head; TYPE_2__* qp; struct ipoib_cm_tx_buf* tx_ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int IB_CQ_NEXT_COMP ; 
 int IB_CQ_REPORT_MISSED_EVENTS ; 
 scalar_t__ IPOIB_ENCAP_LEN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int ib_req_notify_cq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipoib_cm_skb_too_long (struct net_device*,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dbg_data (struct ipoib_dev_priv*,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_send_comp_handler (int /*<<< orphan*/ ,struct net_device*) ; 
 int ipoib_sendq_size ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,...) ; 
 int /*<<< orphan*/  jiffies ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int post_send (struct ipoib_dev_priv*,struct ipoib_cm_tx*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

void ipoib_cm_send(struct net_device *dev, struct sk_buff *skb, struct ipoib_cm_tx *tx)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_cm_tx_buf *tx_req;
	u64 addr;
	int rc;

	if (unlikely(skb->len > tx->mtu)) {
		ipoib_warn(priv, "packet len %d (> %d) too long to send, dropping\n",
			   skb->len, tx->mtu);
		++dev->stats.tx_dropped;
		++dev->stats.tx_errors;
		ipoib_cm_skb_too_long(dev, skb, tx->mtu - IPOIB_ENCAP_LEN);
		return;
	}

	ipoib_dbg_data(priv, "sending packet: head 0x%x length %d connection 0x%x\n",
		       tx->tx_head, skb->len, tx->qp->qp_num);

	/*
	 * We put the skb into the tx_ring _before_ we call post_send()
	 * because it's entirely possible that the completion handler will
	 * run before we execute anything after the post_send().  That
	 * means we have to make sure everything is properly recorded and
	 * our state is consistent before we call post_send().
	 */
	tx_req = &tx->tx_ring[tx->tx_head & (ipoib_sendq_size - 1)];
	tx_req->skb = skb;
	addr = ib_dma_map_single(priv->ca, skb->data, skb->len, DMA_TO_DEVICE);
	if (unlikely(ib_dma_mapping_error(priv->ca, addr))) {
		++dev->stats.tx_errors;
		dev_kfree_skb_any(skb);
		return;
	}

	tx_req->mapping = addr;

	skb_orphan(skb);
	skb_dst_drop(skb);

	rc = post_send(priv, tx, tx->tx_head & (ipoib_sendq_size - 1),
		       addr, skb->len);
	if (unlikely(rc)) {
		ipoib_warn(priv, "post_send failed, error %d\n", rc);
		++dev->stats.tx_errors;
		ib_dma_unmap_single(priv->ca, addr, skb->len, DMA_TO_DEVICE);
		dev_kfree_skb_any(skb);
	} else {
		dev->trans_start = jiffies;
		++tx->tx_head;

		if (++priv->tx_outstanding == ipoib_sendq_size) {
			ipoib_dbg(priv, "TX ring 0x%x full, stopping kernel net queue\n",
				  tx->qp->qp_num);
			netif_stop_queue(dev);
			rc = ib_req_notify_cq(priv->send_cq,
				IB_CQ_NEXT_COMP | IB_CQ_REPORT_MISSED_EVENTS);
			if (rc < 0)
				ipoib_warn(priv, "request notify on send CQ failed\n");
			else if (rc)
				ipoib_send_comp_handler(priv->send_cq, dev);
		}
	}
}