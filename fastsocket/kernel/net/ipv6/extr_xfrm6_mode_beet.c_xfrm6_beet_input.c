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
struct TYPE_5__ {int /*<<< orphan*/  a6; } ;
struct TYPE_4__ {int /*<<< orphan*/  a6; } ;
struct TYPE_6__ {TYPE_2__ saddr; TYPE_1__ daddr; } ;
struct xfrm_state {TYPE_3__ sel; } ;
struct sk_buff {int mac_len; scalar_t__ len; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  payload_len; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,struct in6_addr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,int) ; 
 int skb_cow_head (struct sk_buff*,int) ; 
 unsigned char* skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  xfrm6_beet_make_header (struct sk_buff*) ; 

__attribute__((used)) static int xfrm6_beet_input(struct xfrm_state *x, struct sk_buff *skb)
{
	struct ipv6hdr *ip6h;
	const unsigned char *old_mac;
	int size = sizeof(struct ipv6hdr);
	int err;

	err = skb_cow_head(skb, size + skb->mac_len);
	if (err)
		goto out;

	__skb_push(skb, size);
	skb_reset_network_header(skb);

	old_mac = skb_mac_header(skb);
	skb_set_mac_header(skb, -skb->mac_len);
	memmove(skb_mac_header(skb), old_mac, skb->mac_len);

	xfrm6_beet_make_header(skb);

	ip6h = ipv6_hdr(skb);
	ip6h->payload_len = htons(skb->len - size);
	ipv6_addr_copy(&ip6h->daddr, (struct in6_addr *) &x->sel.daddr.a6);
	ipv6_addr_copy(&ip6h->saddr, (struct in6_addr *) &x->sel.saddr.a6);
	err = 0;
out:
	return err;
}