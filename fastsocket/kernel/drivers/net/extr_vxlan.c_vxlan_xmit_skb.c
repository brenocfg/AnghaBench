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
struct vxlanhdr {int /*<<< orphan*/  vx_vni; int /*<<< orphan*/  vx_flags; } ;
struct vxlan_sock {TYPE_3__* sock; } ;
struct udphdr {scalar_t__ check; int /*<<< orphan*/  len; void* source; void* dest; } ;
struct sk_buff {int encapsulation; int /*<<< orphan*/  len; scalar_t__ vlan_tci; } ;
struct TYPE_4__ {int header_len; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__ dst; } ;
struct rtable {TYPE_2__ u; } ;
struct net {int dummy; } ;
struct iphdr {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  void* __be16 ;
struct TYPE_6__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int LL_RESERVED_SPACE (int /*<<< orphan*/ ) ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  VXLAN_FLAGS ; 
 int VXLAN_HLEN ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __vlan_put_tag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int handle_offloads (struct sk_buff*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int iptunnel_xmit (struct net*,struct rtable*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct iphdr const*) ; 
 int skb_cow_head (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlan_tx_tag_get (struct sk_buff*) ; 
 scalar_t__ vlan_tx_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  vxlan_set_owner (int /*<<< orphan*/ ,struct sk_buff*) ; 

int vxlan_xmit_skb(struct net *net, struct vxlan_sock *vs,
		   struct rtable *rt, struct sk_buff *skb,
		   __be32 src, __be32 dst, __u8 tos, __u8 ttl, __be16 df,
		   __be16 src_port, __be16 dst_port, __be32 vni)
{
	struct vxlanhdr *vxh;
	struct udphdr *uh;
	int min_headroom;
	int err;
	const struct iphdr *inner_ip;

	if (!skb->encapsulation) {
		/* skb_reset_inner_headers(skb); */
		skb->encapsulation = 1;
	}

	min_headroom = LL_RESERVED_SPACE(rt->u.dst.dev) + rt->u.dst.header_len
			+ VXLAN_HLEN + sizeof(struct iphdr)
			+ (vlan_tx_tag_present(skb) ? VLAN_HLEN : 0);

	/* Need space for new headers (invalidates iph ptr) */
	err = skb_cow_head(skb, min_headroom);
	if (unlikely(err))
		return err;

	if (vlan_tx_tag_present(skb)) {
		if (WARN_ON(!__vlan_put_tag(skb,
					    vlan_tx_tag_get(skb))))
			return -ENOMEM;

		skb->vlan_tci = 0;
	}

	inner_ip = ip_hdr(skb);

	vxh = (struct vxlanhdr *) __skb_push(skb, sizeof(*vxh));
	vxh->vx_flags = htonl(VXLAN_FLAGS);
	vxh->vx_vni = vni;

	__skb_push(skb, sizeof(*uh));
	skb_reset_transport_header(skb);
	uh = udp_hdr(skb);

	uh->dest = dst_port;
	uh->source = src_port;

	uh->len = htons(skb->len);
	uh->check = 0;

	vxlan_set_owner(vs->sock->sk, skb);

	err = handle_offloads(skb);
	if (err)
		return err;

	return iptunnel_xmit(net, rt, skb, src, dst,
			IPPROTO_UDP, tos, ttl, df, inner_ip);
}