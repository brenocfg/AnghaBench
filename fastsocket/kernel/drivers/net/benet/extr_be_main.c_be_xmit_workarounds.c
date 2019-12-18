#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vlan_ethhdr {scalar_t__ h_vlan_proto; } ;
struct sk_buff {int len; scalar_t__ ip_summed; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct iphdr {int /*<<< orphan*/  tot_len; } ;
struct be_adapter {int function_mode; scalar_t__ qnq_vid; scalar_t__ pvid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEx_chip (struct be_adapter*) ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 unsigned int ETH_HLEN ; 
 scalar_t__ ETH_P_8021Q ; 
 int UMC_ENABLED ; 
 unsigned int VLAN_ETH_HLEN ; 
 struct sk_buff* be_insert_vlan_in_pkt (struct be_adapter*,struct sk_buff*,int*) ; 
 scalar_t__ be_ipv6_tx_stall_chk (struct be_adapter*,struct sk_buff*) ; 
 scalar_t__ be_vlan_tag_tx_chk (struct be_adapter*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ htons (scalar_t__) ; 
 scalar_t__ ip_hdr (struct sk_buff*) ; 
 scalar_t__ is_ipv4_pkt (struct sk_buff*) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  qnq_async_evt_rcvd (struct be_adapter*) ; 
 scalar_t__ skb_padto (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlan_tx_tag_present (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *be_xmit_workarounds(struct be_adapter *adapter,
					   struct sk_buff *skb,
					   bool *skip_hw_vlan)
{
	struct vlan_ethhdr *veh = (struct vlan_ethhdr *)skb->data;
	unsigned int eth_hdr_len;
	struct iphdr *ip;

	/* Lancer, SH-R ASICs have a bug wherein Packets that are 32 bytes or less
	 * may cause a transmit stall on that port. So the work-around is to
	 * pad short packets (<= 32 bytes) to a 36-byte length.
	 */
	if (unlikely(!BEx_chip(adapter) && skb->len <= 32)) {
		if (skb_padto(skb, 36))
			goto tx_drop;
		skb->len = 36;
	}

	/* For padded packets, BE HW modifies tot_len field in IP header
	 * incorrecly when VLAN tag is inserted by HW.
	 * For padded packets, Lancer computes incorrect checksum.
	 */
	eth_hdr_len = ntohs(skb->protocol) == ETH_P_8021Q ?
						VLAN_ETH_HLEN : ETH_HLEN;
	if (skb->len <= 60 &&
	    (lancer_chip(adapter) || vlan_tx_tag_present(skb)) &&
	    is_ipv4_pkt(skb)) {
		ip = (struct iphdr *)ip_hdr(skb);
		pskb_trim(skb, eth_hdr_len + ntohs(ip->tot_len));
	}

	/* If vlan tag is already inlined in the packet, skip HW VLAN
	 * tagging in UMC mode
	 */
	if ((adapter->function_mode & UMC_ENABLED) &&
	    veh->h_vlan_proto == htons(ETH_P_8021Q))
			*skip_hw_vlan = true;

	/* HW has a bug wherein it will calculate CSUM for VLAN
	 * pkts even though it is disabled.
	 * Manually insert VLAN in pkt.
	 */
	if (skb->ip_summed != CHECKSUM_PARTIAL &&
	    vlan_tx_tag_present(skb)) {
		skb = be_insert_vlan_in_pkt(adapter, skb, skip_hw_vlan);
		if (unlikely(!skb))
			goto tx_drop;
	}

	/* HW may lockup when VLAN HW tagging is requested on
	 * certain ipv6 packets. Drop such pkts if the HW workaround to
	 * skip HW tagging is not enabled by FW.
	 */
	if (unlikely(be_ipv6_tx_stall_chk(adapter, skb) &&
	    (adapter->pvid || adapter->qnq_vid) &&
	    !qnq_async_evt_rcvd(adapter)))
		goto tx_drop;

	/* Manual VLAN tag insertion to prevent:
	 * ASIC lockup when the ASIC inserts VLAN tag into
	 * certain ipv6 packets. Insert VLAN tags in driver,
	 * and set event, completion, vlan bits accordingly
	 * in the Tx WRB.
	 */
	if (be_ipv6_tx_stall_chk(adapter, skb) &&
	    be_vlan_tag_tx_chk(adapter, skb)) {
		skb = be_insert_vlan_in_pkt(adapter, skb, skip_hw_vlan);
		if (unlikely(!skb))
			goto tx_drop;
	}

	return skb;
tx_drop:
	dev_kfree_skb_any(skb);
	return NULL;
}