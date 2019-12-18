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
struct vxlan_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct vxlan_sock {int dummy; } ;
struct vxlan_dev {int flags; int /*<<< orphan*/  stats; TYPE_2__* dev; } ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ len; scalar_t__ encapsulation; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; } ;
struct iphdr {int /*<<< orphan*/  tos; int /*<<< orphan*/  saddr; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  h_source; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; } ;
struct TYPE_5__ {int features; TYPE_1__ stats; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_UNNECESSARY ; 
 int INET_ECN_set_ce (struct sk_buff*) ; 
 int NETIF_F_RXCSUM ; 
 int VXLAN_F_LEARN ; 
 scalar_t__ compare_ether_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ log_ecn_error ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 struct vxlan_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vxlan_snoop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vxlan_dev* vxlan_vs_find_vni (struct vxlan_sock*,int) ; 

__attribute__((used)) static void vxlan_rcv(struct vxlan_sock *vs,
		      struct sk_buff *skb, __be32 vx_vni)
{
	struct iphdr *oip;
	struct vxlan_dev *vxlan;
	struct vxlan_stats *stats;
	__u32 vni;
	int err;

	vni = ntohl(vx_vni) >> 8;
	/* Is this VNI defined? */
	vxlan = vxlan_vs_find_vni(vs, vni);
	if (!vxlan)
		goto drop;

	skb_reset_mac_header(skb);
	skb->protocol = eth_type_trans(skb, vxlan->dev);

	/* Ignore packet loops (and multicast echo) */
	if (compare_ether_addr(eth_hdr(skb)->h_source,
			       vxlan->dev->dev_addr) == 0)
		goto drop;

	/* Re-examine inner Ethernet packet */
	oip = ip_hdr(skb);
	if ((vxlan->flags & VXLAN_F_LEARN) &&
	    vxlan_snoop(skb->dev, oip->saddr, eth_hdr(skb)->h_source))
		goto drop;

	skb_reset_network_header(skb);

	/* If the NIC driver gave us an encapsulated packet with
	 * CHECKSUM_UNNECESSARY and Rx checksum feature is enabled,
	 * leave the CHECKSUM_UNNECESSARY, the device checksummed it
	 * for us. Otherwise force the upper layers to verify it.
	 */
	if (skb->ip_summed != CHECKSUM_UNNECESSARY || !skb->encapsulation ||
	    !(vxlan->dev->features & NETIF_F_RXCSUM))
		skb->ip_summed = CHECKSUM_NONE;

	skb->encapsulation = 0;

	err = INET_ECN_set_ce(skb);
	if (unlikely(err)) {
		if (log_ecn_error)
			net_info_ratelimited("non-ECT from %pI4 with TOS=%#x\n",
					     &oip->saddr, oip->tos);
		if (err > 1) {
			++vxlan->dev->stats.rx_frame_errors;
			++vxlan->dev->stats.rx_errors;
			goto drop;
		}
	}

	stats = this_cpu_ptr(vxlan->stats);
	u64_stats_update_begin(&stats->syncp);
	stats->rx_packets++;
	stats->rx_bytes += skb->len;
	u64_stats_update_end(&stats->syncp);

	netif_rx(skb);

	return;
drop:
	/* Consume bad packet */
	kfree_skb(skb);
}