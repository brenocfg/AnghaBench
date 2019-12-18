#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct sk_buff {int len; scalar_t__ mark; } ;
struct net_device {int dummy; } ;
struct iphdr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  saddr ;
typedef  int /*<<< orphan*/  daddr ;
struct TYPE_4__ {int /*<<< orphan*/  ip6table_mangle; } ;
struct TYPE_6__ {TYPE_1__ ipv6; } ;
struct TYPE_5__ {scalar_t__ hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 unsigned int NF_STOLEN ; 
 TYPE_3__* dev_net (struct net_device const*) ; 
 scalar_t__ ip6_route_me_harder (struct sk_buff*) ; 
 unsigned int ip6t_do_table (struct sk_buff*,unsigned int,struct net_device const*,struct net_device const*,int /*<<< orphan*/ ) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static unsigned int
ip6t_local_out_hook(unsigned int hook,
		   struct sk_buff *skb,
		   const struct net_device *in,
		   const struct net_device *out,
		   int (*okfn)(struct sk_buff *))
{

	unsigned int ret;
	struct in6_addr saddr, daddr;
	u_int8_t hop_limit;
	u_int32_t flowlabel, mark;

#if 0
	/* root is playing with raw sockets. */
	if (skb->len < sizeof(struct iphdr)
	    || ip_hdrlen(skb) < sizeof(struct iphdr)) {
		if (net_ratelimit())
			printk("ip6t_hook: happy cracking.\n");
		return NF_ACCEPT;
	}
#endif

	/* save source/dest address, mark, hoplimit, flowlabel, priority,  */
	memcpy(&saddr, &ipv6_hdr(skb)->saddr, sizeof(saddr));
	memcpy(&daddr, &ipv6_hdr(skb)->daddr, sizeof(daddr));
	mark = skb->mark;
	hop_limit = ipv6_hdr(skb)->hop_limit;

	/* flowlabel and prio (includes version, which shouldn't change either */
	flowlabel = *((u_int32_t *)ipv6_hdr(skb));

	ret = ip6t_do_table(skb, hook, in, out,
			    dev_net(out)->ipv6.ip6table_mangle);

	if (ret != NF_DROP && ret != NF_STOLEN
		&& (memcmp(&ipv6_hdr(skb)->saddr, &saddr, sizeof(saddr))
		    || memcmp(&ipv6_hdr(skb)->daddr, &daddr, sizeof(daddr))
		    || skb->mark != mark
		    || ipv6_hdr(skb)->hop_limit != hop_limit))
		return ip6_route_me_harder(skb) == 0 ? ret : NF_DROP;

	return ret;
}