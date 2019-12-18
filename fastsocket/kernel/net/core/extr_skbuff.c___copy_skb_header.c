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
struct sk_buff {int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  tc_verd; int /*<<< orphan*/  tc_index; int /*<<< orphan*/  nf_trace; int /*<<< orphan*/  iif; int /*<<< orphan*/  mark; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ipvs_property; int /*<<< orphan*/  deliver_no_wcard; int /*<<< orphan*/  priority; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  local_df; int /*<<< orphan*/  csum; int /*<<< orphan*/  cb; int /*<<< orphan*/  sp; int /*<<< orphan*/  encapsulation; int /*<<< orphan*/  rxhash; int /*<<< orphan*/  peek_sk; int /*<<< orphan*/  sock_dst; int /*<<< orphan*/  mac_header; int /*<<< orphan*/  network_header; int /*<<< orphan*/  transport_header; int /*<<< orphan*/  dev; int /*<<< orphan*/  tstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nf_copy (struct sk_buff*,struct sk_buff const*) ; 
 int /*<<< orphan*/  dst_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secpath_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_queue_mapping (struct sk_buff*,struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_copy_secmark (struct sk_buff*,struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __copy_skb_header(struct sk_buff *new, const struct sk_buff *old)
{
	new->tstamp		= old->tstamp;
	new->dev		= old->dev;
	new->transport_header	= old->transport_header;
	new->network_header	= old->network_header;
	new->mac_header		= old->mac_header;
	skb_dst_set(new, dst_clone(skb_dst(old)));
	new->sock_dst		= old->sock_dst;
	new->peek_sk		= old->peek_sk;
	new->rxhash		= old->rxhash;
	new->encapsulation	= old->encapsulation;
#ifdef CONFIG_XFRM
	new->sp			= secpath_get(old->sp);
#endif
	memcpy(new->cb, old->cb, sizeof(old->cb));
	new->csum		= old->csum;
	new->local_df		= old->local_df;
	new->pkt_type		= old->pkt_type;
	new->ip_summed		= old->ip_summed;
	skb_copy_queue_mapping(new, old);
	new->priority		= old->priority;
	new->deliver_no_wcard	= old->deliver_no_wcard;
#if defined(CONFIG_IP_VS) || defined(CONFIG_IP_VS_MODULE)
	new->ipvs_property	= old->ipvs_property;
#endif
	new->protocol		= old->protocol;
	new->mark		= old->mark;
	new->iif		= old->iif;
	__nf_copy(new, old);
#if defined(CONFIG_NETFILTER_XT_TARGET_TRACE) || \
    defined(CONFIG_NETFILTER_XT_TARGET_TRACE_MODULE)
	new->nf_trace		= old->nf_trace;
#endif
#ifdef CONFIG_NET_SCHED
	new->tc_index		= old->tc_index;
#ifdef CONFIG_NET_CLS_ACT
	new->tc_verd		= old->tc_verd;
#endif
#endif
	new->vlan_tci		= old->vlan_tci;

	skb_copy_secmark(new, old);
}