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
struct TYPE_7__ {int /*<<< orphan*/  flow_type; int /*<<< orphan*/  vlan_id; } ;
struct TYPE_6__ {int src; int /*<<< orphan*/  dst; } ;
union ixgbe_atr_hash_dword {int ip; TYPE_2__ formatted; TYPE_1__ port; int /*<<< orphan*/  dword; } ;
struct tcphdr {int dest; int /*<<< orphan*/  source; int /*<<< orphan*/  syn; scalar_t__ fin; } ;
struct ixgbe_tx_buffer {int protocol; int tx_flags; int /*<<< orphan*/  skb; } ;
struct ixgbe_ring {scalar_t__ atr_sample_rate; scalar_t__ atr_count; int /*<<< orphan*/  queue_index; struct ixgbe_q_vector* q_vector; } ;
struct ixgbe_q_vector {TYPE_5__* adapter; } ;
struct TYPE_9__ {int* s6_addr32; } ;
struct TYPE_8__ {int* s6_addr32; } ;
struct ipv6hdr {scalar_t__ nexthdr; TYPE_4__ daddr; TYPE_3__ saddr; } ;
struct iphdr {scalar_t__ protocol; int saddr; int daddr; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_10__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  IXGBE_ATR_FLOW_TYPE_TCPV4 ; 
 int /*<<< orphan*/  IXGBE_ATR_FLOW_TYPE_TCPV6 ; 
 int IXGBE_TX_FLAGS_HW_VLAN ; 
 int IXGBE_TX_FLAGS_SW_VLAN ; 
 int IXGBE_TX_FLAGS_VLAN_SHIFT ; 
 int __constant_htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  ixgbe_fdir_add_signature_filter_82599 (int /*<<< orphan*/ *,union ixgbe_atr_hash_dword,union ixgbe_atr_hash_dword,int /*<<< orphan*/ ) ; 
 unsigned char* skb_network_header (int /*<<< orphan*/ ) ; 
 struct tcphdr* tcp_hdr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_atr(struct ixgbe_ring *ring,
		      struct ixgbe_tx_buffer *first)
{
	struct ixgbe_q_vector *q_vector = ring->q_vector;
	union ixgbe_atr_hash_dword input = { .dword = 0 };
	union ixgbe_atr_hash_dword common = { .dword = 0 };
	union {
		unsigned char *network;
		struct iphdr *ipv4;
		struct ipv6hdr *ipv6;
	} hdr;
	struct tcphdr *th;
	__be16 vlan_id;

	/* if ring doesn't have a interrupt vector, cannot perform ATR */
	if (!q_vector)
		return;

	/* do nothing if sampling is disabled */
	if (!ring->atr_sample_rate)
		return;

	ring->atr_count++;

	/* snag network header to get L4 type and address */
	hdr.network = skb_network_header(first->skb);

	/* Currently only IPv4/IPv6 with TCP is supported */
	if ((first->protocol != __constant_htons(ETH_P_IPV6) ||
	     hdr.ipv6->nexthdr != IPPROTO_TCP) &&
	    (first->protocol != __constant_htons(ETH_P_IP) ||
	     hdr.ipv4->protocol != IPPROTO_TCP))
		return;

	th = tcp_hdr(first->skb);

	/* skip this packet since it is invalid or the socket is closing */
	if (!th || th->fin)
		return;

	/* sample on all syn packets or once every atr sample count */
	if (!th->syn && (ring->atr_count < ring->atr_sample_rate))
		return;

	/* reset sample count */
	ring->atr_count = 0;

	vlan_id = htons(first->tx_flags >> IXGBE_TX_FLAGS_VLAN_SHIFT);

	/*
	 * src and dst are inverted, think how the receiver sees them
	 *
	 * The input is broken into two sections, a non-compressed section
	 * containing vm_pool, vlan_id, and flow_type.  The rest of the data
	 * is XORed together and stored in the compressed dword.
	 */
	input.formatted.vlan_id = vlan_id;

	/*
	 * since src port and flex bytes occupy the same word XOR them together
	 * and write the value to source port portion of compressed dword
	 */
	if (first->tx_flags & (IXGBE_TX_FLAGS_SW_VLAN | IXGBE_TX_FLAGS_HW_VLAN))
		common.port.src ^= th->dest ^ __constant_htons(ETH_P_8021Q);
	else
		common.port.src ^= th->dest ^ first->protocol;
	common.port.dst ^= th->source;

	if (first->protocol == __constant_htons(ETH_P_IP)) {
		input.formatted.flow_type = IXGBE_ATR_FLOW_TYPE_TCPV4;
		common.ip ^= hdr.ipv4->saddr ^ hdr.ipv4->daddr;
	} else {
		input.formatted.flow_type = IXGBE_ATR_FLOW_TYPE_TCPV6;
		common.ip ^= hdr.ipv6->saddr.s6_addr32[0] ^
			     hdr.ipv6->saddr.s6_addr32[1] ^
			     hdr.ipv6->saddr.s6_addr32[2] ^
			     hdr.ipv6->saddr.s6_addr32[3] ^
			     hdr.ipv6->daddr.s6_addr32[0] ^
			     hdr.ipv6->daddr.s6_addr32[1] ^
			     hdr.ipv6->daddr.s6_addr32[2] ^
			     hdr.ipv6->daddr.s6_addr32[3];
	}

	/* This assumes the Rx queue and Tx queue are bound to the same CPU */
	ixgbe_fdir_add_signature_filter_82599(&q_vector->adapter->hw,
					      input, common, ring->queue_index);
}