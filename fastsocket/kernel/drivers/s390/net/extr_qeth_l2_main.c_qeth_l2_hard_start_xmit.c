#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; scalar_t__ protocol; scalar_t__ data; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct TYPE_9__ {int pkt_length; } ;
struct TYPE_10__ {TYPE_2__ l2; } ;
struct qeth_hdr {TYPE_3__ hdr; } ;
struct TYPE_14__ {int tx_bytes; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_carrier_errors; } ;
struct TYPE_13__ {scalar_t__ outbound_start_time; int /*<<< orphan*/  outbound_time; int /*<<< orphan*/  outbound_cnt; } ;
struct TYPE_12__ {scalar_t__ performance_stats; } ;
struct TYPE_11__ {scalar_t__ type; } ;
struct TYPE_8__ {struct qeth_qdio_out_q** out_qs; } ;
struct qeth_card {scalar_t__ state; TYPE_7__ stats; TYPE_6__ perf_stats; TYPE_5__ options; TYPE_4__ info; int /*<<< orphan*/  lan_online; TYPE_1__ qdio; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 scalar_t__ CARD_STATE_UP ; 
 int EBUSY ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 scalar_t__ QETH_CARD_TYPE_OSN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct qeth_hdr* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct qeth_hdr*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  qeth_core_header_cache ; 
 int qeth_do_send_packet (struct qeth_card*,struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,int) ; 
 int qeth_do_send_packet_fast (struct qeth_card*,struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,int,int,int) ; 
 int qeth_get_elements_no (struct qeth_card*,void*,struct sk_buff*,int) ; 
 int qeth_get_ip_version (struct sk_buff*) ; 
 scalar_t__ qeth_get_micros () ; 
 size_t qeth_get_priority_queue (struct qeth_card*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  qeth_l2_fill_header (struct qeth_card*,struct qeth_hdr*,struct sk_buff*,int,int) ; 
 int qeth_l2_get_cast_type (struct qeth_card*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int) ; 

__attribute__((used)) static int qeth_l2_hard_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	int rc;
	struct qeth_hdr *hdr = NULL;
	int elements = 0;
	struct qeth_card *card = dev->ml_priv;
	struct sk_buff *new_skb = skb;
	int ipv = qeth_get_ip_version(skb);
	int cast_type = qeth_l2_get_cast_type(card, skb);
	struct qeth_qdio_out_q *queue = card->qdio.out_qs
		[qeth_get_priority_queue(card, skb, ipv, cast_type)];
	int tx_bytes = skb->len;
	int data_offset = -1;
	int elements_needed = 0;
	int hd_len = 0;

	if ((card->state != CARD_STATE_UP) || !card->lan_online) {
		card->stats.tx_carrier_errors++;
		goto tx_drop;
	}

	if ((card->info.type == QETH_CARD_TYPE_OSN) &&
	    (skb->protocol == htons(ETH_P_IPV6)))
		goto tx_drop;

	if (card->options.performance_stats) {
		card->perf_stats.outbound_cnt++;
		card->perf_stats.outbound_start_time = qeth_get_micros();
	}
	netif_stop_queue(dev);

	if (card->info.type == QETH_CARD_TYPE_OSN)
		hdr = (struct qeth_hdr *)skb->data;
	else {
		if (card->info.type == QETH_CARD_TYPE_IQD) {
			new_skb = skb;
			data_offset = ETH_HLEN;
			hd_len = ETH_HLEN;
			hdr = kmem_cache_alloc(qeth_core_header_cache,
						GFP_ATOMIC);
			if (!hdr)
				goto tx_drop;
			elements_needed++;
			skb_reset_mac_header(new_skb);
			qeth_l2_fill_header(card, hdr, new_skb, ipv, cast_type);
			hdr->hdr.l2.pkt_length = new_skb->len;
			memcpy(((char *)hdr) + sizeof(struct qeth_hdr),
				skb_mac_header(new_skb), ETH_HLEN);
		} else {
			/* create a clone with writeable headroom */
			new_skb = skb_realloc_headroom(skb,
						sizeof(struct qeth_hdr));
			if (!new_skb)
				goto tx_drop;
			hdr = (struct qeth_hdr *)skb_push(new_skb,
						sizeof(struct qeth_hdr));
			skb_set_mac_header(new_skb, sizeof(struct qeth_hdr));
			qeth_l2_fill_header(card, hdr, new_skb, ipv, cast_type);
		}
	}

	elements = qeth_get_elements_no(card, (void *)hdr, new_skb,
						elements_needed);
	if (!elements) {
		if (data_offset >= 0)
			kmem_cache_free(qeth_core_header_cache, hdr);
		goto tx_drop;
	}

	if (card->info.type != QETH_CARD_TYPE_IQD)
		rc = qeth_do_send_packet(card, queue, new_skb, hdr,
					 elements);
	else
		rc = qeth_do_send_packet_fast(card, queue, new_skb, hdr,
					elements, data_offset, hd_len);
	if (!rc) {
		card->stats.tx_packets++;
		card->stats.tx_bytes += tx_bytes;
		if (new_skb != skb)
			dev_kfree_skb_any(skb);
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