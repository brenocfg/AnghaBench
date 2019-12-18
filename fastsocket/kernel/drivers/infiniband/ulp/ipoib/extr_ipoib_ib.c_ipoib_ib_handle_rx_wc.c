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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union ib_gid {int* raw; } ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; struct net_device* dev; scalar_t__ len; scalar_t__ data; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_3__ stats; scalar_t__ broadcast; } ;
struct ipoib_header {int /*<<< orphan*/  proto; } ;
struct ipoib_dev_priv {scalar_t__ local_lid; int /*<<< orphan*/  napi; int /*<<< orphan*/  flags; TYPE_2__* rx_ring; TYPE_1__* qp; } ;
struct ib_wc {unsigned int wr_id; scalar_t__ status; scalar_t__ slid; scalar_t__ src_qp; unsigned int byte_len; int wc_flags; int /*<<< orphan*/  vendor_err; } ;
struct ib_grh {union ib_gid dgid; } ;
struct TYPE_5__ {int /*<<< orphan*/ * mapping; struct sk_buff* skb; } ;
struct TYPE_4__ {scalar_t__ qp_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  IB_GRH_BYTES ; 
 int IB_WC_GRH ; 
 int IB_WC_IP_CSUM_OK ; 
 scalar_t__ IB_WC_SUCCESS ; 
 scalar_t__ IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  IPOIB_ENCAP_LEN ; 
 int /*<<< orphan*/  IPOIB_FLAG_CSUM ; 
 unsigned int IPOIB_OP_RECV ; 
 int IPOIB_UD_RX_SG ; 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  PACKET_MULTICAST ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ipoib_alloc_rx_skb (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  ipoib_dbg_data (struct ipoib_dev_priv*,char*,unsigned int,scalar_t__) ; 
 int ipoib_ib_post_receive (struct net_device*,unsigned int) ; 
 unsigned int ipoib_recvq_size ; 
 int /*<<< orphan*/  ipoib_ud_dma_unmap_rx (struct ipoib_dev_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_ud_skb_put_frags (struct ipoib_dev_priv*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,unsigned int,...) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ memcmp (union ib_gid*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ipoib_ib_handle_rx_wc(struct net_device *dev, struct ib_wc *wc)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	unsigned int wr_id = wc->wr_id & ~IPOIB_OP_RECV;
	struct sk_buff *skb;
	u64 mapping[IPOIB_UD_RX_SG];
	union ib_gid *dgid;

	ipoib_dbg_data(priv, "recv completion: id %d, status: %d\n",
		       wr_id, wc->status);

	if (unlikely(wr_id >= ipoib_recvq_size)) {
		ipoib_warn(priv, "recv completion event with wrid %d (> %d)\n",
			   wr_id, ipoib_recvq_size);
		return;
	}

	skb  = priv->rx_ring[wr_id].skb;

	if (unlikely(wc->status != IB_WC_SUCCESS)) {
		if (wc->status != IB_WC_WR_FLUSH_ERR)
			ipoib_warn(priv, "failed recv event "
				   "(status=%d, wrid=%d vend_err %x)\n",
				   wc->status, wr_id, wc->vendor_err);
		ipoib_ud_dma_unmap_rx(priv, priv->rx_ring[wr_id].mapping);
		dev_kfree_skb_any(skb);
		priv->rx_ring[wr_id].skb = NULL;
		return;
	}

	/*
	 * Drop packets that this interface sent, ie multicast packets
	 * that the HCA has replicated.
	 */
	if (wc->slid == priv->local_lid && wc->src_qp == priv->qp->qp_num)
		goto repost;

	memcpy(mapping, priv->rx_ring[wr_id].mapping,
	       IPOIB_UD_RX_SG * sizeof *mapping);

	/*
	 * If we can't allocate a new RX buffer, dump
	 * this packet and reuse the old buffer.
	 */
	if (unlikely(!ipoib_alloc_rx_skb(dev, wr_id))) {
		++dev->stats.rx_dropped;
		goto repost;
	}

	ipoib_dbg_data(priv, "received %d bytes, SLID 0x%04x\n",
		       wc->byte_len, wc->slid);

	ipoib_ud_dma_unmap_rx(priv, mapping);
	ipoib_ud_skb_put_frags(priv, skb, wc->byte_len);

	/* First byte of dgid signals multicast when 0xff */
	dgid = &((struct ib_grh *)skb->data)->dgid;

	if (!(wc->wc_flags & IB_WC_GRH) || dgid->raw[0] != 0xff)
		skb->pkt_type = PACKET_HOST;
	else if (memcmp(dgid, dev->broadcast + 4, sizeof(union ib_gid)) == 0)
		skb->pkt_type = PACKET_BROADCAST;
	else
		skb->pkt_type = PACKET_MULTICAST;

	skb_pull(skb, IB_GRH_BYTES);

	skb->protocol = ((struct ipoib_header *) skb->data)->proto;
	skb_reset_mac_header(skb);
	skb_pull(skb, IPOIB_ENCAP_LEN);

	++dev->stats.rx_packets;
	dev->stats.rx_bytes += skb->len;

	skb->dev = dev;
	if (test_bit(IPOIB_FLAG_CSUM, &priv->flags) &&
	    		likely(wc->wc_flags & IB_WC_IP_CSUM_OK))
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	napi_gro_receive(&priv->napi, skb);

repost:
	if (unlikely(ipoib_ib_post_receive(dev, wr_id)))
		ipoib_warn(priv, "ipoib_ib_post_receive failed "
			   "for buf %d\n", wr_id);
}