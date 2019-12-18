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
struct vport {int dummy; } ;
struct sk_buff {int len; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 TYPE_1__* netdev_vport_priv (struct vport*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  secpath_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int internal_dev_recv(struct vport *vport, struct sk_buff *skb)
{
	struct net_device *netdev = netdev_vport_priv(vport)->dev;
	int len;

	len = skb->len;

	skb_dst_drop(skb);
	nf_reset(skb);
	secpath_reset(skb);

	skb->dev = netdev;
	skb->pkt_type = PACKET_HOST;
	skb->protocol = eth_type_trans(skb, netdev);
	skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);

	netif_rx(skb);

	return len;
}