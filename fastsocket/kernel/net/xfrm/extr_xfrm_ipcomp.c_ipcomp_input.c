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
struct xfrm_state {int dummy; } ;
struct sk_buff {scalar_t__ network_header; scalar_t__ transport_header; scalar_t__ data; int /*<<< orphan*/  ip_summed; } ;
struct ip_comp_hdr {int nexthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int ipcomp_decompress (struct xfrm_state*,struct sk_buff*) ; 
 scalar_t__ skb_linearize_cow (struct sk_buff*) ; 

int ipcomp_input(struct xfrm_state *x, struct sk_buff *skb)
{
	int nexthdr;
	int err = -ENOMEM;
	struct ip_comp_hdr *ipch;

	if (skb_linearize_cow(skb))
		goto out;

	skb->ip_summed = CHECKSUM_NONE;

	/* Remove ipcomp header and decompress original payload */
	ipch = (void *)skb->data;
	nexthdr = ipch->nexthdr;

	skb->transport_header = skb->network_header + sizeof(*ipch);
	__skb_pull(skb, sizeof(*ipch));
	err = ipcomp_decompress(x, skb);
	if (err)
		goto out;

	err = nexthdr;

out:
	return err;
}