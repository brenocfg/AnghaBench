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
struct sk_buff {int len; } ;
struct net_device {int dummy; } ;
struct ipv6hdr {int dummy; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  dev_net (struct net_device const*) ; 
 scalar_t__ net_ratelimit () ; 
 unsigned int nf_conntrack_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct sk_buff*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static unsigned int ipv6_conntrack_local(unsigned int hooknum,
					 struct sk_buff *skb,
					 const struct net_device *in,
					 const struct net_device *out,
					 int (*okfn)(struct sk_buff *))
{
	/* root is playing with raw sockets. */
	if (skb->len < sizeof(struct ipv6hdr)) {
		if (net_ratelimit())
			printk("ipv6_conntrack_local: packet too short\n");
		return NF_ACCEPT;
	}
	return nf_conntrack_in(dev_net(out), PF_INET6, hooknum, skb);
}