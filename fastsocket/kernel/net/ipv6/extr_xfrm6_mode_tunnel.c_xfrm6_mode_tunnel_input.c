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
struct TYPE_3__ {int flags; } ;
struct xfrm_state {TYPE_1__ props; } ;
struct sk_buff {int /*<<< orphan*/  mac_len; } ;
struct ipv6hdr {int dummy; } ;
struct TYPE_4__ {scalar_t__ protocol; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPPROTO_IPV6 ; 
 TYPE_2__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 int XFRM_STATE_DECAP_DSCP ; 
 int XFRM_STATE_NOECN ; 
 int /*<<< orphan*/  ipip6_ecn_decapsulate (struct sk_buff*) ; 
 int /*<<< orphan*/  ipipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_copy_dscp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_get_dsfield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 unsigned char* skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_unclone (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm6_mode_tunnel_input(struct xfrm_state *x, struct sk_buff *skb)
{
	int err = -EINVAL;
	const unsigned char *old_mac;

	if (XFRM_MODE_SKB_CB(skb)->protocol != IPPROTO_IPV6)
		goto out;
	if (!pskb_may_pull(skb, sizeof(struct ipv6hdr)))
		goto out;

	err = skb_unclone(skb, GFP_ATOMIC);
	if (err)
		goto out;

	if (x->props.flags & XFRM_STATE_DECAP_DSCP)
		ipv6_copy_dscp(ipv6_get_dsfield(ipv6_hdr(skb)),
			       ipipv6_hdr(skb));
	if (!(x->props.flags & XFRM_STATE_NOECN))
		ipip6_ecn_decapsulate(skb);

	old_mac = skb_mac_header(skb);
	skb_set_mac_header(skb, -skb->mac_len);
	memmove(skb_mac_header(skb), old_mac, skb->mac_len);
	skb_reset_network_header(skb);
	err = 0;

out:
	return err;
}