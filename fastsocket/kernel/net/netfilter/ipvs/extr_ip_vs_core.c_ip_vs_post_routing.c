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
struct sk_buff {int /*<<< orphan*/  ipvs_property; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 unsigned int NF_STOP ; 

__attribute__((used)) static unsigned int ip_vs_post_routing(unsigned int hooknum,
				       struct sk_buff *skb,
				       const struct net_device *in,
				       const struct net_device *out,
				       int (*okfn)(struct sk_buff *))
{
	if (!skb->ipvs_property)
		return NF_ACCEPT;
	/* The packet was sent from IPVS, exit this chain */
	return NF_STOP;
}