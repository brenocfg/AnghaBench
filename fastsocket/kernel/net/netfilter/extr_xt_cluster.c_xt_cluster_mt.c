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
struct xt_match_param {int /*<<< orphan*/  family; struct xt_cluster_match_info* matchinfo; } ;
struct xt_cluster_match_info {int node_mask; int flags; } ;
struct sk_buff {scalar_t__ pkt_type; } ;
struct nf_conn {struct nf_conn const* master; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 scalar_t__ PACKET_HOST ; 
 scalar_t__ PACKET_MULTICAST ; 
 int XT_CLUSTER_F_INV ; 
 struct nf_conn const nf_conntrack_untracked ; 
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 
 unsigned long xt_cluster_hash (struct nf_conn const*,struct xt_cluster_match_info const*) ; 
 int /*<<< orphan*/  xt_cluster_is_multicast_addr (struct sk_buff const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
xt_cluster_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	struct sk_buff *pskb = (struct sk_buff *)skb;
	const struct xt_cluster_match_info *info = par->matchinfo;
	const struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	unsigned long hash;

	/* This match assumes that all nodes see the same packets. This can be
	 * achieved if the switch that connects the cluster nodes support some
	 * sort of 'port mirroring'. However, if your switch does not support
	 * this, your cluster nodes can reply ARP request using a multicast MAC
	 * address. Thus, your switch will flood the same packets to the
	 * cluster nodes with the same multicast MAC address. Using a multicast
	 * link address is a RFC 1812 (section 3.3.2) violation, but this works
	 * fine in practise.
	 *
	 * Unfortunately, if you use the multicast MAC address, the link layer
	 * sets skbuff's pkt_type to PACKET_MULTICAST, which is not accepted
	 * by TCP and others for packets coming to this node. For that reason,
	 * this match mangles skbuff's pkt_type if it detects a packet
	 * addressed to a unicast address but using PACKET_MULTICAST. Yes, I
	 * know, matches should not alter packets, but we are doing this here
	 * because we would need to add a PKTTYPE target for this sole purpose.
	 */
	if (!xt_cluster_is_multicast_addr(skb, par->family) &&
	    skb->pkt_type == PACKET_MULTICAST) {
	    	pskb->pkt_type = PACKET_HOST;
	}

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NULL)
		return false;

	if (ct == &nf_conntrack_untracked)
		return false;

	if (ct->master)
		hash = xt_cluster_hash(ct->master, info);
	else
		hash = xt_cluster_hash(ct, info);

	return !!((1 << hash) & info->node_mask) ^
	       !!(info->flags & XT_CLUSTER_F_INV);
}