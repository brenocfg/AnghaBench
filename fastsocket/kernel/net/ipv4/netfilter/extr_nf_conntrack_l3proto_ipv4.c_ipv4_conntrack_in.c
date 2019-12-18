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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  dev_net (struct net_device const*) ; 
 unsigned int nf_conntrack_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct sk_buff*) ; 

__attribute__((used)) static unsigned int ipv4_conntrack_in(unsigned int hooknum,
				      struct sk_buff *skb,
				      const struct net_device *in,
				      const struct net_device *out,
				      int (*okfn)(struct sk_buff *))
{
	return nf_conntrack_in(dev_net(in), PF_INET, hooknum, skb);
}