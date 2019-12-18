#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct vlan_ethhdr {void* h_vlan_TCI; void* h_vlan_proto; void* h_vlan_encapsulated_proto; } ;
struct sk_buff {int* data; scalar_t__ ip_summed; void* protocol; } ;
struct qlcnic_host_tx_ring {size_t producer; int /*<<< orphan*/  num_desc; TYPE_1__* cmd_buf_arr; struct cmd_desc_type0* desc_head; } ;
struct TYPE_7__ {int /*<<< orphan*/  lso_frames; } ;
struct qlcnic_adapter {scalar_t__ tx_pvid; int flags; TYPE_2__ stats; struct qlcnic_host_tx_ring* tx_ring; } ;
struct cmd_desc_type0 {int total_hdr_length; int tcp_hdr_offset; int ip_hdr_offset; int /*<<< orphan*/  mss; int /*<<< orphan*/  eth_addr; } ;
struct TYPE_10__ {int protocol; } ;
struct TYPE_9__ {int nexthdr; } ;
struct TYPE_8__ {int /*<<< orphan*/  gso_size; } ;
struct TYPE_6__ {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int BIT_0 ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int EIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ ETH_P_8021Q ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 scalar_t__ FLAGS_VLAN_OOB ; 
 scalar_t__ FLAGS_VLAN_TAGGED ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int QLCNIC_TAGGING_ENABLED ; 
 int TX_ETHER_PKT ; 
 int TX_TCPV6_PKT ; 
 int TX_TCP_LSO ; 
 int TX_TCP_LSO6 ; 
 int TX_TCP_PKT ; 
 int TX_UDPV6_PKT ; 
 int TX_UDP_PKT ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 size_t get_next_index (size_t,int /*<<< orphan*/ ) ; 
 void* htons (scalar_t__) ; 
 TYPE_5__* ip_hdr (struct sk_buff*) ; 
 TYPE_4__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 scalar_t__ ntohs (void*) ; 
 int /*<<< orphan*/  qlcnic_set_tx_flags_opcode (struct cmd_desc_type0*,scalar_t__,int) ; 
 int /*<<< orphan*/  qlcnic_set_tx_vlan_tci (struct cmd_desc_type0*,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,struct vlan_ethhdr*,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,int,char*,int) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 scalar_t__ vlan_tx_tag_get (struct sk_buff*) ; 
 scalar_t__ vlan_tx_tag_present (struct sk_buff*) ; 

__attribute__((used)) static int qlcnic_tx_pkt(struct qlcnic_adapter *adapter,
			 struct cmd_desc_type0 *first_desc, struct sk_buff *skb)
{
	u8 l4proto, opcode = 0, hdr_len = 0;
	u16 flags = 0, vlan_tci = 0;
	int copied, offset, copy_len, size;
	struct cmd_desc_type0 *hwdesc;
	struct vlan_ethhdr *vh;
	struct qlcnic_host_tx_ring *tx_ring = adapter->tx_ring;
	u16 protocol = ntohs(skb->protocol);
	u32 producer = tx_ring->producer;

	if (protocol == ETH_P_8021Q) {
		vh = (struct vlan_ethhdr *)skb->data;
		flags = FLAGS_VLAN_TAGGED;
		vlan_tci = ntohs(vh->h_vlan_TCI);
		protocol = ntohs(vh->h_vlan_encapsulated_proto);
	} else if (vlan_tx_tag_present(skb)) {
		flags = FLAGS_VLAN_OOB;
		vlan_tci = vlan_tx_tag_get(skb);
	}
	if (unlikely(adapter->tx_pvid)) {
		if (vlan_tci && !(adapter->flags & QLCNIC_TAGGING_ENABLED))
			return -EIO;
		if (vlan_tci && (adapter->flags & QLCNIC_TAGGING_ENABLED))
			goto set_flags;

		flags = FLAGS_VLAN_OOB;
		vlan_tci = adapter->tx_pvid;
	}
set_flags:
	qlcnic_set_tx_vlan_tci(first_desc, vlan_tci);
	qlcnic_set_tx_flags_opcode(first_desc, flags, opcode);

	if (*(skb->data) & BIT_0) {
		flags |= BIT_0;
		memcpy(&first_desc->eth_addr, skb->data, ETH_ALEN);
	}
	opcode = TX_ETHER_PKT;
	if (skb_is_gso(skb)) {
		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		first_desc->mss = cpu_to_le16(skb_shinfo(skb)->gso_size);
		first_desc->total_hdr_length = hdr_len;
		opcode = (protocol == ETH_P_IPV6) ? TX_TCP_LSO6 : TX_TCP_LSO;

		/* For LSO, we need to copy the MAC/IP/TCP headers into
		* the descriptor ring */
		copied = 0;
		offset = 2;

		if (flags & FLAGS_VLAN_OOB) {
			first_desc->total_hdr_length += VLAN_HLEN;
			first_desc->tcp_hdr_offset = VLAN_HLEN;
			first_desc->ip_hdr_offset = VLAN_HLEN;

			/* Only in case of TSO on vlan device */
			flags |= FLAGS_VLAN_TAGGED;

			/* Create a TSO vlan header template for firmware */
			hwdesc = &tx_ring->desc_head[producer];
			tx_ring->cmd_buf_arr[producer].skb = NULL;

			copy_len = min((int)sizeof(struct cmd_desc_type0) -
				       offset, hdr_len + VLAN_HLEN);

			vh = (struct vlan_ethhdr *)((char *) hwdesc + 2);
			skb_copy_from_linear_data(skb, vh, 12);
			vh->h_vlan_proto = htons(ETH_P_8021Q);
			vh->h_vlan_TCI = htons(vlan_tci);

			skb_copy_from_linear_data_offset(skb, 12,
							 (char *)vh + 16,
							 copy_len - 16);
			copied = copy_len - VLAN_HLEN;
			offset = 0;
			producer = get_next_index(producer, tx_ring->num_desc);
		}

		while (copied < hdr_len) {
			size = (int)sizeof(struct cmd_desc_type0) - offset;
			copy_len = min(size, (hdr_len - copied));
			hwdesc = &tx_ring->desc_head[producer];
			tx_ring->cmd_buf_arr[producer].skb = NULL;
			skb_copy_from_linear_data_offset(skb, copied,
							 (char *)hwdesc +
							 offset, copy_len);
			copied += copy_len;
			offset = 0;
			producer = get_next_index(producer, tx_ring->num_desc);
		}

		tx_ring->producer = producer;
		smp_mb();
		adapter->stats.lso_frames++;

	} else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		if (protocol == ETH_P_IP) {
			l4proto = ip_hdr(skb)->protocol;

			if (l4proto == IPPROTO_TCP)
				opcode = TX_TCP_PKT;
			else if (l4proto == IPPROTO_UDP)
				opcode = TX_UDP_PKT;
		} else if (protocol == ETH_P_IPV6) {
			l4proto = ipv6_hdr(skb)->nexthdr;

			if (l4proto == IPPROTO_TCP)
				opcode = TX_TCPV6_PKT;
			else if (l4proto == IPPROTO_UDP)
				opcode = TX_UDPV6_PKT;
		}
	}
	first_desc->tcp_hdr_offset += skb_transport_offset(skb);
	first_desc->ip_hdr_offset += skb_network_offset(skb);
	qlcnic_set_tx_flags_opcode(first_desc, flags, opcode);

	return 0;
}