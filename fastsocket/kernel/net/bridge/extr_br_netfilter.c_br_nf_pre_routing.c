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
struct sk_buff {scalar_t__ protocol; int len; int /*<<< orphan*/  dev; int /*<<< orphan*/  nf_bridge; } ;
struct net_device {int dummy; } ;
struct iphdr {int ihl; int version; int /*<<< orphan*/  tot_len; } ;
struct inet_skb_parm {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IS_PPPOE_IP (struct sk_buff*) ; 
 scalar_t__ IS_PPPOE_IPV6 (struct sk_buff*) ; 
 int /*<<< orphan*/  IS_VLAN_IP (struct sk_buff*) ; 
 scalar_t__ IS_VLAN_IPV6 (struct sk_buff*) ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_PRE_ROUTING ; 
 unsigned int NF_STOLEN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  br_nf_pre_routing_finish ; 
 unsigned int br_nf_pre_routing_ipv6 (unsigned int,struct sk_buff*,struct net_device const*,struct net_device const*,int (*) (struct sk_buff*)) ; 
 int /*<<< orphan*/  brnf_call_ip6tables ; 
 int /*<<< orphan*/  brnf_call_iptables ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ip_fast_csum (int /*<<< orphan*/ *,int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_bridge_alloc (struct sk_buff*) ; 
 int nf_bridge_encap_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_pull_encap_header_rcsum (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_put (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  pskb_trim_rcsum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  setup_pre_routing (struct sk_buff*) ; 
 int /*<<< orphan*/  store_orig_dstaddr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int br_nf_pre_routing(unsigned int hook, struct sk_buff *skb,
				      const struct net_device *in,
				      const struct net_device *out,
				      int (*okfn)(struct sk_buff *))
{
	struct iphdr *iph;
	__u32 len = nf_bridge_encap_header_len(skb);

	if (unlikely(!pskb_may_pull(skb, len)))
		goto out;

	if (skb->protocol == htons(ETH_P_IPV6) || IS_VLAN_IPV6(skb) ||
	    IS_PPPOE_IPV6(skb)) {
#ifdef CONFIG_SYSCTL
		if (!brnf_call_ip6tables)
			return NF_ACCEPT;
#endif
		nf_bridge_pull_encap_header_rcsum(skb);
		return br_nf_pre_routing_ipv6(hook, skb, in, out, okfn);
	}
#ifdef CONFIG_SYSCTL
	if (!brnf_call_iptables)
		return NF_ACCEPT;
#endif

	if (skb->protocol != htons(ETH_P_IP) && !IS_VLAN_IP(skb) &&
	    !IS_PPPOE_IP(skb))
		return NF_ACCEPT;

	nf_bridge_pull_encap_header_rcsum(skb);

	if (!pskb_may_pull(skb, sizeof(struct iphdr)))
		goto inhdr_error;

	iph = ip_hdr(skb);
	if (iph->ihl < 5 || iph->version != 4)
		goto inhdr_error;

	if (!pskb_may_pull(skb, 4 * iph->ihl))
		goto inhdr_error;

	iph = ip_hdr(skb);
	if (ip_fast_csum((__u8 *) iph, iph->ihl) != 0)
		goto inhdr_error;

	len = ntohs(iph->tot_len);
	if (skb->len < len || len < 4 * iph->ihl)
		goto inhdr_error;

	pskb_trim_rcsum(skb, len);

	/* BUG: Should really parse the IP options here. */
	memset(IPCB(skb), 0, sizeof(struct inet_skb_parm));

	nf_bridge_put(skb->nf_bridge);
	if (!nf_bridge_alloc(skb))
		return NF_DROP;
	if (!setup_pre_routing(skb))
		return NF_DROP;
	store_orig_dstaddr(skb);

	NF_HOOK(PF_INET, NF_INET_PRE_ROUTING, skb, skb->dev, NULL,
		br_nf_pre_routing_finish);

	return NF_STOLEN;

inhdr_error:
//      IP_INC_STATS_BH(IpInHdrErrors);
out:
	return NF_DROP;
}