#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; } ;
struct net_device {int dummy; } ;
struct iphdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  iptable_security; } ;
struct TYPE_4__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 TYPE_2__* dev_net (struct net_device const*) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 unsigned int ipt_do_table (struct sk_buff*,unsigned int,struct net_device const*,struct net_device const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ipt_local_out_hook(unsigned int hook,
		   struct sk_buff *skb,
		   const struct net_device *in,
		   const struct net_device *out,
		   int (*okfn)(struct sk_buff *))
{
	/* Somebody is playing with raw sockets. */
	if (skb->len < sizeof(struct iphdr)
	    || ip_hdrlen(skb) < sizeof(struct iphdr))
		return NF_ACCEPT;
	return ipt_do_table(skb, hook, in, out,
			    dev_net(out)->ipv4.iptable_security);
}