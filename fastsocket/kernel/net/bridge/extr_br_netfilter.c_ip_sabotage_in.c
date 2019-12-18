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
struct net_device {int dummy; } ;
struct TYPE_2__ {int mask; } ;

/* Variables and functions */
 int BRNF_NF_BRIDGE_PREROUTING ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_STOP ; 

__attribute__((used)) static unsigned int ip_sabotage_in(unsigned int hook, struct sk_buff *skb,
				   const struct net_device *in,
				   const struct net_device *out,
				   int (*okfn)(struct sk_buff *))
{
	if (skb->nf_bridge &&
	    !(skb->nf_bridge->mask & BRNF_NF_BRIDGE_PREROUTING)) {
		return NF_STOP;
	}

	return NF_ACCEPT;
}