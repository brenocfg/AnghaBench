#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vxlanhdr {int vx_flags; int vx_vni; } ;
struct vxlan_sock {int /*<<< orphan*/  (* rcv ) (struct vxlan_sock*,struct sk_buff*,int) ;} ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  sport; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TEB ; 
 int VXLAN_FLAGS ; 
 int /*<<< orphan*/  VXLAN_HLEN ; 
 int htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 scalar_t__ iptunnel_pull_header (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct vxlan_sock*,struct sk_buff*,int) ; 
 scalar_t__ udp_hdr (struct sk_buff*) ; 
 struct vxlan_sock* vxlan_find_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxlan_udp_encap_recv(struct sock *sk, struct sk_buff *skb)
{
	struct vxlan_sock *vs;
	struct vxlanhdr *vxh;
	__be16 port;

	/* Need Vxlan and inner Ethernet header to be present */
	if (!pskb_may_pull(skb, VXLAN_HLEN))
		goto error;

	/* Return packets with reserved bits set */
	vxh = (struct vxlanhdr *)(udp_hdr(skb) + 1);
	if (vxh->vx_flags != htonl(VXLAN_FLAGS) ||
	    (vxh->vx_vni & htonl(0xff))) {
		netdev_dbg(skb->dev, "invalid vxlan flags=%#x vni=%#x\n",
			   ntohl(vxh->vx_flags), ntohl(vxh->vx_vni));
		goto error;
	}

	if (iptunnel_pull_header(skb, VXLAN_HLEN, htons(ETH_P_TEB)))
		goto drop;

	port = inet_sk(sk)->sport;

	vs = vxlan_find_sock(sock_net(sk), port);
	if (!vs)
		goto drop;

	vs->rcv(vs, skb, vxh->vx_vni);
	return 0;

drop:
	/* Consume bad packet */
	kfree_skb(skb);
	return 0;

error:
	/* Return non vxlan pkt */
	return 1;
}