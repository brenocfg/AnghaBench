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
struct sk_buff {TYPE_1__* nf_bridge; } ;
typedef  enum ip6_defrag_users { ____Placeholder_ip6_defrag_users } ip6_defrag_users ;
struct TYPE_2__ {int mask; } ;

/* Variables and functions */
 int BRNF_NF_BRIDGE_PREROUTING ; 
 int IP6_DEFRAG_CONNTRACK_BRIDGE_IN ; 
 int IP6_DEFRAG_CONNTRACK_IN ; 
 int IP6_DEFRAG_CONNTRACK_OUT ; 
 unsigned int NF_INET_PRE_ROUTING ; 

__attribute__((used)) static enum ip6_defrag_users nf_ct6_defrag_user(unsigned int hooknum,
						struct sk_buff *skb)
{
#ifdef CONFIG_BRIDGE_NETFILTER
	if (skb->nf_bridge &&
	    skb->nf_bridge->mask & BRNF_NF_BRIDGE_PREROUTING)
		return IP6_DEFRAG_CONNTRACK_BRIDGE_IN;
#endif
	if (hooknum == NF_INET_PRE_ROUTING)
		return IP6_DEFRAG_CONNTRACK_IN;
	else
		return IP6_DEFRAG_CONNTRACK_OUT;

}