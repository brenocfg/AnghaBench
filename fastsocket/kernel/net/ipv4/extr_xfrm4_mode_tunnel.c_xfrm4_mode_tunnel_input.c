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
struct iphdr {int dummy; } ;
struct TYPE_4__ {scalar_t__ protocol; int /*<<< orphan*/  tos; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPPROTO_IPIP ; 
 TYPE_2__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 int XFRM_STATE_DECAP_DSCP ; 
 int XFRM_STATE_NOECN ; 
 int /*<<< orphan*/  ipip_ecn_decapsulate (struct sk_buff*) ; 
 int /*<<< orphan*/  ipip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv4_copy_dscp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 unsigned char* skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_unclone (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm4_mode_tunnel_input(struct xfrm_state *x, struct sk_buff *skb)
{
	const unsigned char *old_mac;
	int err = -EINVAL;

	if (XFRM_MODE_SKB_CB(skb)->protocol != IPPROTO_IPIP)
		goto out;

	if (!pskb_may_pull(skb, sizeof(struct iphdr)))
		goto out;

	err = skb_unclone(skb, GFP_ATOMIC);
	if (err)
		goto out;

	if (x->props.flags & XFRM_STATE_DECAP_DSCP)
		ipv4_copy_dscp(XFRM_MODE_SKB_CB(skb)->tos, ipip_hdr(skb));
	if (!(x->props.flags & XFRM_STATE_NOECN))
		ipip_ecn_decapsulate(skb);

	old_mac = skb_mac_header(skb);
	skb_set_mac_header(skb, -skb->mac_len);
	memmove(skb_mac_header(skb), old_mac, skb->mac_len);
	skb_reset_network_header(skb);
	err = 0;

out:
	return err;
}