#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ nfct; } ;
struct net_device {int dummy; } ;
typedef  enum ip_defrag_users { ____Placeholder_ip_defrag_users } ip_defrag_users ;
struct TYPE_2__ {int frag_off; } ;

/* Variables and functions */
 int IP_MF ; 
 int IP_OFFSET ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_STOLEN ; 
 int htons (int) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int nf_ct_defrag_user (unsigned int,struct sk_buff*) ; 
 scalar_t__ nf_ct_ipv4_gather_frags (struct sk_buff*,int) ; 

__attribute__((used)) static unsigned int ipv4_conntrack_defrag(unsigned int hooknum,
					  struct sk_buff *skb,
					  const struct net_device *in,
					  const struct net_device *out,
					  int (*okfn)(struct sk_buff *))
{
#if defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
#if !defined(CONFIG_NF_NAT) && !defined(CONFIG_NF_NAT_MODULE)
	/* Previously seen (loopback)?  Ignore.  Do this before
	   fragment check. */
	if (skb->nfct)
		return NF_ACCEPT;
#endif
#endif
	/* Gather fragments. */
	if (ip_hdr(skb)->frag_off & htons(IP_MF | IP_OFFSET)) {
		enum ip_defrag_users user = nf_ct_defrag_user(hooknum, skb);
		if (nf_ct_ipv4_gather_frags(skb, user))
			return NF_STOLEN;
	}
	return NF_ACCEPT;
}