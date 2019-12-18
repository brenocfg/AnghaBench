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
struct xfrm_state {int /*<<< orphan*/  lock; scalar_t__ coaddr; } ;
struct sk_buff {scalar_t__ data; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; } ;
struct ipv6_destopt_hdr {int nexthdr; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ipv6_addr_any (struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mip6_destopt_input(struct xfrm_state *x, struct sk_buff *skb)
{
	struct ipv6hdr *iph = ipv6_hdr(skb);
	struct ipv6_destopt_hdr *destopt = (struct ipv6_destopt_hdr *)skb->data;
	int err = destopt->nexthdr;

	spin_lock(&x->lock);
	if (!ipv6_addr_equal(&iph->saddr, (struct in6_addr *)x->coaddr) &&
	    !ipv6_addr_any((struct in6_addr *)x->coaddr))
		err = -ENOENT;
	spin_unlock(&x->lock);

	return err;
}