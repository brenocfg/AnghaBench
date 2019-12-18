#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int len; scalar_t__ protocol; scalar_t__ ip_summed; scalar_t__ data; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct qeth_hdr_tso {int dummy; } ;
struct TYPE_10__ {int length; } ;
struct TYPE_11__ {TYPE_1__ l3; } ;
struct qeth_hdr {TYPE_2__ hdr; } ;
struct TYPE_13__ {int tx_bytes; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_carrier_errors; } ;
struct TYPE_17__ {int large_send_bytes; int sg_frags_sent; scalar_t__ outbound_start_time; int /*<<< orphan*/  outbound_time; int /*<<< orphan*/  sg_skbs_sent; int /*<<< orphan*/  large_send_cnt; int /*<<< orphan*/  tx_lin; int /*<<< orphan*/  outbound_cnt; } ;
struct TYPE_16__ {scalar_t__ cq; int large_send; scalar_t__ performance_stats; scalar_t__ sniffer; } ;
struct TYPE_14__ {scalar_t__ type; scalar_t__ broadcast_capable; } ;
struct TYPE_12__ {struct qeth_qdio_out_q** out_qs; } ;
struct qeth_card {scalar_t__ state; TYPE_4__ stats; TYPE_8__ perf_stats; TYPE_7__ options; TYPE_5__ info; scalar_t__ vlangrp; TYPE_6__* dev; int /*<<< orphan*/  lan_online; TYPE_3__ qdio; } ;
struct net_device {struct qeth_card* ml_priv; } ;
typedef  enum qeth_large_send_types { ____Placeholder_qeth_large_send_types } qeth_large_send_types ;
struct TYPE_18__ {int nr_frags; } ;
struct TYPE_15__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_IEEE802_TR ; 
 scalar_t__ CARD_STATE_UP ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int EBUSY ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ ETH_P_AF_IUCV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 scalar_t__ QETH_CQ_ENABLED ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*) ; 
 int QETH_LARGE_SEND_NO ; 
 int QETH_LARGE_SEND_TSO ; 
 int RTN_BROADCAST ; 
 int RTN_UNSPEC ; 
 int TR_HLEN ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  __constant_htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct qeth_hdr* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct qeth_hdr*) ; 
 int /*<<< orphan*/  memset (struct qeth_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  qeth_core_header_cache ; 
 int qeth_do_send_packet (struct qeth_card*,struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,int) ; 
 int qeth_do_send_packet_fast (struct qeth_card*,struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,int,int,int /*<<< orphan*/ ) ; 
 int qeth_get_elements_no (struct qeth_card*,void*,struct sk_buff*,int) ; 
 int qeth_get_ip_version (struct sk_buff*) ; 
 scalar_t__ qeth_get_micros () ; 
 size_t qeth_get_priority_queue (struct qeth_card*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  qeth_l3_fill_af_iucv_hdr (struct qeth_card*,struct qeth_hdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  qeth_l3_fill_header (struct qeth_card*,struct qeth_hdr*,struct sk_buff*,int,int) ; 
 int qeth_l3_get_cast_type (struct qeth_card*,struct sk_buff*) ; 
 int /*<<< orphan*/  qeth_l3_hdr_csum (struct qeth_card*,struct qeth_hdr*,struct sk_buff*) ; 
 scalar_t__ qeth_l3_tso_check (struct sk_buff*) ; 
 int qeth_l3_tso_elements (struct sk_buff*) ; 
 int /*<<< orphan*/  qeth_tso_fill_header (struct qeth_card*,struct qeth_hdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,scalar_t__,int) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,int) ; 
 TYPE_9__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_tx_tag_get (struct sk_buff*) ; 
 scalar_t__ vlan_tx_tag_present (struct sk_buff*) ; 

__attribute__((used)) static int qeth_l3_hard_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	int rc;
	u16 *tag;
	struct qeth_hdr *hdr = NULL;
	int elements_needed = 0;
	int elems;
	struct qeth_card *card = dev->ml_priv;
	struct sk_buff *new_skb = NULL;
	int ipv = qeth_get_ip_version(skb);
	int cast_type = qeth_l3_get_cast_type(card, skb);
	struct qeth_qdio_out_q *queue = card->qdio.out_qs
		[qeth_get_priority_queue(card, skb, ipv, cast_type)];
	int tx_bytes = skb->len;
	enum qeth_large_send_types large_send = QETH_LARGE_SEND_NO;
	int data_offset = -1;
	int nr_frags;

	if (((card->info.type == QETH_CARD_TYPE_IQD) &&
	     (((card->options.cq != QETH_CQ_ENABLED) && !ipv) ||
	      ((card->options.cq == QETH_CQ_ENABLED) &&
	       (skb->protocol != ETH_P_AF_IUCV)))) ||
	    card->options.sniffer)
			goto tx_drop;

	if ((card->state != CARD_STATE_UP) || !card->lan_online) {
		card->stats.tx_carrier_errors++;
		goto tx_drop;
	}

	if ((cast_type == RTN_BROADCAST) &&
	    (card->info.broadcast_capable == 0))
		goto tx_drop;

	if (card->options.performance_stats) {
		card->perf_stats.outbound_cnt++;
		card->perf_stats.outbound_start_time = qeth_get_micros();
	}

	if (skb_is_gso(skb))
		large_send = card->options.large_send;

	if ((card->info.type == QETH_CARD_TYPE_IQD) && (!large_send) &&
	    (skb_shinfo(skb)->nr_frags == 0)) {
		new_skb = skb;
		if (new_skb->protocol == ETH_P_AF_IUCV)
			data_offset = 0;
		else
			data_offset = ETH_HLEN;
		hdr = kmem_cache_alloc(qeth_core_header_cache, GFP_ATOMIC);
		if (!hdr)
			goto tx_drop;
		elements_needed++;
	} else {
		/* create a clone with writeable headroom */
		new_skb = skb_realloc_headroom(skb, sizeof(struct qeth_hdr_tso)
					+ VLAN_HLEN);
		if (!new_skb)
			goto tx_drop;
	}

	if (card->info.type == QETH_CARD_TYPE_IQD) {
		if (data_offset < 0)
			skb_pull(new_skb, ETH_HLEN);
	} else {
		if (ipv == 4) {
			if (card->dev->type == ARPHRD_IEEE802_TR)
				skb_pull(new_skb, TR_HLEN);
			else
				skb_pull(new_skb, ETH_HLEN);
		}

		if (ipv != 4 && card->vlangrp &&
				vlan_tx_tag_present(new_skb)) {
			skb_push(new_skb, VLAN_HLEN);
			skb_copy_to_linear_data(new_skb, new_skb->data + 4, 4);
			skb_copy_to_linear_data_offset(new_skb, 4,
				new_skb->data + 8, 4);
			skb_copy_to_linear_data_offset(new_skb, 8,
				new_skb->data + 12, 4);
			tag = (u16 *)(new_skb->data + 12);
			*tag = __constant_htons(ETH_P_8021Q);
			*(tag + 1) = htons(vlan_tx_tag_get(new_skb));
		}
	}

	netif_stop_queue(dev);

	/* fix hardware limitation: as long as we do not have sbal
	 * chaining we can not send long frag lists
	 */
	if (large_send == QETH_LARGE_SEND_TSO) {
		if (qeth_l3_tso_elements(new_skb) + 1 > 16) {
			if (skb_linearize(new_skb))
				goto tx_drop;
			if (card->options.performance_stats)
				card->perf_stats.tx_lin++;
		}
	}

	if ((large_send == QETH_LARGE_SEND_TSO) &&
	    (cast_type == RTN_UNSPEC)) {
		hdr = (struct qeth_hdr *)skb_push(new_skb,
						sizeof(struct qeth_hdr_tso));
		if (qeth_l3_tso_check(new_skb))
			QETH_DBF_MESSAGE(2, "tso skb misaligned\n");
		memset(hdr, 0, sizeof(struct qeth_hdr_tso));
		qeth_l3_fill_header(card, hdr, new_skb, ipv, cast_type);
		qeth_tso_fill_header(card, hdr, new_skb);
		elements_needed++;
	} else {
		if (data_offset < 0) {
			hdr = (struct qeth_hdr *)skb_push(new_skb,
						sizeof(struct qeth_hdr));
			qeth_l3_fill_header(card, hdr, new_skb, ipv,
						cast_type);
		} else {
			if (new_skb->protocol == ETH_P_AF_IUCV)
				qeth_l3_fill_af_iucv_hdr(card, hdr, new_skb);
			else {
				qeth_l3_fill_header(card, hdr, new_skb, ipv,
							cast_type);
				hdr->hdr.l3.length = new_skb->len - data_offset;
			}
		}

		if (skb->ip_summed == CHECKSUM_PARTIAL)
			qeth_l3_hdr_csum(card, hdr, new_skb);
	}

	elems = qeth_get_elements_no(card, (void *)hdr, new_skb,
						 elements_needed);
	if (!elems) {
		if (data_offset >= 0)
			kmem_cache_free(qeth_core_header_cache, hdr);
		goto tx_drop;
	}
	elements_needed += elems;
	nr_frags = skb_shinfo(new_skb)->nr_frags;

	if (card->info.type != QETH_CARD_TYPE_IQD)
		rc = qeth_do_send_packet(card, queue, new_skb, hdr,
					 elements_needed);
	else
		rc = qeth_do_send_packet_fast(card, queue, new_skb, hdr,
					elements_needed, data_offset, 0);

	if (!rc) {
		card->stats.tx_packets++;
		card->stats.tx_bytes += tx_bytes;
		if (new_skb != skb)
			dev_kfree_skb_any(skb);
		if (card->options.performance_stats) {
			if (large_send != QETH_LARGE_SEND_NO) {
				card->perf_stats.large_send_bytes += tx_bytes;
				card->perf_stats.large_send_cnt++;
			}
			if (nr_frags) {
				card->perf_stats.sg_skbs_sent++;
				/* nr_frags + skb->data */
				card->perf_stats.sg_frags_sent += nr_frags + 1;
			}
		}
		rc = NETDEV_TX_OK;
	} else {
		if (data_offset >= 0)
			kmem_cache_free(qeth_core_header_cache, hdr);

		if (rc == -EBUSY) {
			if (new_skb != skb)
				dev_kfree_skb_any(new_skb);
			return NETDEV_TX_BUSY;
		} else
			goto tx_drop;
	}

	netif_wake_queue(dev);
	if (card->options.performance_stats)
		card->perf_stats.outbound_time += qeth_get_micros() -
			card->perf_stats.outbound_start_time;
	return rc;

tx_drop:
	card->stats.tx_dropped++;
	card->stats.tx_errors++;
	if ((new_skb != skb) && new_skb)
		dev_kfree_skb_any(new_skb);
	dev_kfree_skb_any(skb);
	netif_wake_queue(dev);
	return NETDEV_TX_OK;
}