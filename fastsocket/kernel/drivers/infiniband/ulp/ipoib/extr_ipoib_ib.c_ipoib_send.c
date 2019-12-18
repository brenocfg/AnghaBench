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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ len; scalar_t__ ip_summed; void* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int /*<<< orphan*/  trans_start; TYPE_2__ stats; } ;
struct ipoib_tx_buf {struct sk_buff* skb; } ;
struct TYPE_3__ {int /*<<< orphan*/  send_flags; } ;
struct ipoib_dev_priv {scalar_t__ mcast_mtu; int tx_head; int tx_outstanding; int /*<<< orphan*/  ca; int /*<<< orphan*/  send_cq; TYPE_1__ tx_wr; struct ipoib_tx_buf* tx_ring; } ;
struct ipoib_ah {int last_send; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 int /*<<< orphan*/  IB_SEND_IP_CSUM ; 
 scalar_t__ IPOIB_ENCAP_LEN ; 
 int MAX_SEND_CQE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ ib_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_cm_skb_too_long (struct net_device*,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_dbg_data (struct ipoib_dev_priv*,char*,scalar_t__,struct ipoib_ah*,int /*<<< orphan*/ ) ; 
 int ipoib_dma_map_tx (int /*<<< orphan*/ ,struct ipoib_tx_buf*) ; 
 int /*<<< orphan*/  ipoib_dma_unmap_tx (int /*<<< orphan*/ ,struct ipoib_tx_buf*) ; 
 int ipoib_sendq_size ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,...) ; 
 int /*<<< orphan*/  jiffies ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ poll_tx (struct ipoib_dev_priv*) ; 
 int post_send (struct ipoib_dev_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipoib_tx_buf*,void*,int) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

void ipoib_send(struct net_device *dev, struct sk_buff *skb,
		struct ipoib_ah *address, u32 qpn)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_tx_buf *tx_req;
	int hlen, rc;
	void *phead;

	if (skb_is_gso(skb)) {
		hlen = skb_transport_offset(skb) + tcp_hdrlen(skb);
		phead = skb->data;
		if (unlikely(!skb_pull(skb, hlen))) {
			ipoib_warn(priv, "linear data too small\n");
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			dev_kfree_skb_any(skb);
			return;
		}
	} else {
		if (unlikely(skb->len > priv->mcast_mtu + IPOIB_ENCAP_LEN)) {
			ipoib_warn(priv, "packet len %d (> %d) too long to send, dropping\n",
				   skb->len, priv->mcast_mtu + IPOIB_ENCAP_LEN);
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			ipoib_cm_skb_too_long(dev, skb, priv->mcast_mtu);
			return;
		}
		phead = NULL;
		hlen  = 0;
	}

	ipoib_dbg_data(priv, "sending packet, length=%d address=%p qpn=0x%06x\n",
		       skb->len, address, qpn);

	/*
	 * We put the skb into the tx_ring _before_ we call post_send()
	 * because it's entirely possible that the completion handler will
	 * run before we execute anything after the post_send().  That
	 * means we have to make sure everything is properly recorded and
	 * our state is consistent before we call post_send().
	 */
	tx_req = &priv->tx_ring[priv->tx_head & (ipoib_sendq_size - 1)];
	tx_req->skb = skb;
	if (unlikely(ipoib_dma_map_tx(priv->ca, tx_req))) {
		++dev->stats.tx_errors;
		dev_kfree_skb_any(skb);
		return;
	}

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		priv->tx_wr.send_flags |= IB_SEND_IP_CSUM;
	else
		priv->tx_wr.send_flags &= ~IB_SEND_IP_CSUM;

	if (++priv->tx_outstanding == ipoib_sendq_size) {
		ipoib_dbg(priv, "TX ring full, stopping kernel net queue\n");
		if (ib_req_notify_cq(priv->send_cq, IB_CQ_NEXT_COMP))
			ipoib_warn(priv, "request notify on send CQ failed\n");
		netif_stop_queue(dev);
	}

	skb_orphan(skb);
	skb_dst_drop(skb);

	rc = post_send(priv, priv->tx_head & (ipoib_sendq_size - 1),
		       address->ah, qpn, tx_req, phead, hlen);
	if (unlikely(rc)) {
		ipoib_warn(priv, "post_send failed, error %d\n", rc);
		++dev->stats.tx_errors;
		--priv->tx_outstanding;
		ipoib_dma_unmap_tx(priv->ca, tx_req);
		dev_kfree_skb_any(skb);
		if (netif_queue_stopped(dev))
			netif_wake_queue(dev);
	} else {
		dev->trans_start = jiffies;

		address->last_send = priv->tx_head;
		++priv->tx_head;
	}

	if (unlikely(priv->tx_outstanding > MAX_SEND_CQE))
		while (poll_tx(priv))
			; /* nothing */
}