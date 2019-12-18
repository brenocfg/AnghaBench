#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  a4; } ;
struct TYPE_5__ {int /*<<< orphan*/  a4; } ;
struct TYPE_7__ {TYPE_2__ saddr; TYPE_1__ daddr; } ;
struct xfrm_state {TYPE_3__ sel; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  mac_len; scalar_t__ data; } ;
struct iphdr {int ihl; scalar_t__ check; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  tot_len; } ;
struct ip_beet_phdr {int padlen; int hdrlen; scalar_t__ nexthdr; } ;
struct TYPE_8__ {scalar_t__ protocol; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPPROTO_BEETPH ; 
 int IPV4_BEET_PHMAXLEN ; 
 TYPE_4__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ip_fast_csum (int /*<<< orphan*/ ,int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfrm4_beet_make_header (struct sk_buff*) ; 

__attribute__((used)) static int xfrm4_beet_input(struct xfrm_state *x, struct sk_buff *skb)
{
	struct iphdr *iph;
	int optlen = 0;
	int err = -EINVAL;

	if (unlikely(XFRM_MODE_SKB_CB(skb)->protocol == IPPROTO_BEETPH)) {
		struct ip_beet_phdr *ph;
		int phlen;

		if (!pskb_may_pull(skb, sizeof(*ph)))
			goto out;

		ph = (struct ip_beet_phdr *)skb->data;

		phlen = sizeof(*ph) + ph->padlen;
		optlen = ph->hdrlen * 8 + (IPV4_BEET_PHMAXLEN - phlen);
		if (optlen < 0 || optlen & 3 || optlen > 250)
			goto out;

		XFRM_MODE_SKB_CB(skb)->protocol = ph->nexthdr;

		if (!pskb_may_pull(skb, phlen))
			goto out;
		__skb_pull(skb, phlen);
	}

	skb_push(skb, sizeof(*iph));
	skb_reset_network_header(skb);

	memmove(skb->data - skb->mac_len, skb_mac_header(skb),
		skb->mac_len);
	skb_set_mac_header(skb, -skb->mac_len);

	xfrm4_beet_make_header(skb);

	iph = ip_hdr(skb);

	iph->ihl += optlen / 4;
	iph->tot_len = htons(skb->len);
	iph->daddr = x->sel.daddr.a4;
	iph->saddr = x->sel.saddr.a4;
	iph->check = 0;
	iph->check = ip_fast_csum(skb_network_header(skb), iph->ihl);
	err = 0;
out:
	return err;
}