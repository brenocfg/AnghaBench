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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct tcphdr {int doff; int psh; } ;
struct sk_buff {void* protocol; int len; scalar_t__ data; } ;
struct qlcnic_rx_buffer {int dummy; } ;
struct qlcnic_recv_context {struct qlcnic_host_rds_ring* rds_rings; } ;
struct qlcnic_host_rds_ring {int num_desc; struct qlcnic_rx_buffer* rx_buf_arr; } ;
struct TYPE_3__ {int /*<<< orphan*/  lrobytes; int /*<<< orphan*/  lro_pkts; int /*<<< orphan*/  rxdropped; } ;
struct qlcnic_adapter {size_t max_rds_rings; int flags; TYPE_1__ stats; int /*<<< orphan*/  vlgrp; scalar_t__ mac_learn; struct qlcnic_recv_context* recv_ctx; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct ipv6hdr {void* payload_len; } ;
struct iphdr {int ihl; scalar_t__ check; void* tot_len; } ;
struct TYPE_4__ {int gso_size; int /*<<< orphan*/  gso_type; } ;

/* Variables and functions */
 scalar_t__ ETH_P_IPV6 ; 
 int QLCNIC_ESWITCH_ENABLED ; 
 int QLCNIC_FW_LRO_MSS_CAP ; 
 int QLCNIC_TCP_HDR_SIZE ; 
 int QLCNIC_TCP_TS_HDR_SIZE ; 
 int /*<<< orphan*/  SKB_GSO_TCPV4 ; 
 int /*<<< orphan*/  SKB_GSO_TCPV6 ; 
 int /*<<< orphan*/  STATUS_CKSUM_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 void* eth_type_trans (struct sk_buff*,struct net_device*) ; 
 void* htons (scalar_t__) ; 
 scalar_t__ ip_fast_csum (unsigned char*,int) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 scalar_t__ ntohs (void*) ; 
 int qlcnic_83xx_get_lro_sts_mss (int /*<<< orphan*/ ) ; 
 int qlcnic_83xx_hndl (int /*<<< orphan*/ ) ; 
 int qlcnic_83xx_is_lb_pkt (int /*<<< orphan*/ ,int) ; 
 int qlcnic_83xx_is_psh_bit (int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_83xx_is_tstamp (int /*<<< orphan*/ ) ; 
 int qlcnic_83xx_l2_hdr_off (int /*<<< orphan*/ ) ; 
 int qlcnic_83xx_l4_hdr_off (int /*<<< orphan*/ ) ; 
 int qlcnic_83xx_lro_pktln (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_add_lb_filter (struct qlcnic_adapter*,struct sk_buff*,int,int) ; 
 int qlcnic_check_rx_tagging (struct qlcnic_adapter*,struct sk_buff*,int*) ; 
 struct sk_buff* qlcnic_process_rxbuf (struct qlcnic_adapter*,struct qlcnic_host_rds_ring*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlan_hwaccel_receive_skb (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct qlcnic_rx_buffer *
qlcnic_83xx_process_lro(struct qlcnic_adapter *adapter,
			u8 ring, u64 sts_data[])
{
	struct net_device *netdev = adapter->netdev;
	struct qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	struct qlcnic_rx_buffer *buffer;
	struct sk_buff *skb;
	struct qlcnic_host_rds_ring *rds_ring;
	struct iphdr *iph;
	struct ipv6hdr *ipv6h;
	struct tcphdr *th;
	bool push;
	int l2_hdr_offset, l4_hdr_offset;
	int index, is_lb_pkt;
	u16 lro_length, length, data_offset, gso_size;
	u16 vid = 0xffff, t_vid;

	if (unlikely(ring > adapter->max_rds_rings))
		return NULL;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = qlcnic_83xx_hndl(sts_data[0]);
	if (unlikely(index > rds_ring->num_desc))
		return NULL;

	buffer = &rds_ring->rx_buf_arr[index];

	lro_length = qlcnic_83xx_lro_pktln(sts_data[0]);
	l2_hdr_offset = qlcnic_83xx_l2_hdr_off(sts_data[1]);
	l4_hdr_offset = qlcnic_83xx_l4_hdr_off(sts_data[1]);
	push = qlcnic_83xx_is_psh_bit(sts_data[1]);

	skb = qlcnic_process_rxbuf(adapter, rds_ring, index, STATUS_CKSUM_OK);
	if (!skb)
		return buffer;

	if (adapter->mac_learn &&
	    (adapter->flags & QLCNIC_ESWITCH_ENABLED)) {
		t_vid = 0;
		is_lb_pkt = qlcnic_83xx_is_lb_pkt(sts_data[1], 1);
		qlcnic_add_lb_filter(adapter, skb, is_lb_pkt, t_vid);
	}
	if (qlcnic_83xx_is_tstamp(sts_data[1]))
		data_offset = l4_hdr_offset + QLCNIC_TCP_TS_HDR_SIZE;
	else
		data_offset = l4_hdr_offset + QLCNIC_TCP_HDR_SIZE;

	skb_put(skb, lro_length + data_offset);
	skb_pull(skb, l2_hdr_offset);

	if (unlikely(qlcnic_check_rx_tagging(adapter, skb, &vid))) {
		adapter->stats.rxdropped++;
		dev_kfree_skb(skb);
		return buffer;
	}

	skb->protocol = eth_type_trans(skb, netdev);
	if (ntohs(skb->protocol) == ETH_P_IPV6) {
		ipv6h = (struct ipv6hdr *)skb->data;
		th = (struct tcphdr *)(skb->data + sizeof(struct ipv6hdr));

		length = (th->doff << 2) + lro_length;
		ipv6h->payload_len = htons(length);
	} else {
		iph = (struct iphdr *)skb->data;
		th = (struct tcphdr *)(skb->data + (iph->ihl << 2));
		length = (iph->ihl << 2) + (th->doff << 2) + lro_length;
		iph->tot_len = htons(length);
		iph->check = 0;
		iph->check = ip_fast_csum((unsigned char *)iph, iph->ihl);
	}

	th->psh = push;
	length = skb->len;

	if (adapter->flags & QLCNIC_FW_LRO_MSS_CAP) {
		gso_size = qlcnic_83xx_get_lro_sts_mss(sts_data[0]);
		skb_shinfo(skb)->gso_size = gso_size;
		if (skb->protocol == htons(ETH_P_IPV6))
			skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
		else
			skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
	}

	if (vid != 0xffff)
		vlan_hwaccel_receive_skb(skb, adapter->vlgrp, vid);
	else
		netif_receive_skb(skb);

	adapter->stats.lro_pkts++;
	adapter->stats.lrobytes += length;
	return buffer;
}