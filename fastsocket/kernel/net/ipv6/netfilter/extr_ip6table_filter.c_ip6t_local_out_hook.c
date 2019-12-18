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
struct TYPE_3__ {int /*<<< orphan*/  ip6table_filter; } ;
struct TYPE_4__ {TYPE_1__ ipv6; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 TYPE_2__* dev_net (struct net_device const*) ; 
 unsigned int ip6t_do_table (struct sk_buff*,unsigned int,struct net_device const*,struct net_device const*,int /*<<< orphan*/ ) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static unsigned int
ip6t_local_out_hook(unsigned int hook,
		   struct sk_buff *skb,
		   const struct net_device *in,
		   const struct net_device *out,
		   int (*okfn)(struct sk_buff *))
{
#if 0
	/* root is playing with raw sockets. */
	if (skb->len < sizeof(struct iphdr)
	    || ip_hdrlen(skb) < sizeof(struct iphdr)) {
		if (net_ratelimit())
			printk("ip6t_hook: happy cracking.\n");
		return NF_ACCEPT;
	}
#endif

	return ip6t_do_table(skb, hook, in, out,
			     dev_net(out)->ipv6.ip6table_filter);
}