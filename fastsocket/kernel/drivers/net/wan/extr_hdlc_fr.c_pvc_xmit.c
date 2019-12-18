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
struct sk_buff {int len; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_compressed; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {scalar_t__ type; TYPE_2__ stats; TYPE_3__* ml_priv; } ;
struct TYPE_4__ {scalar_t__ fecn; scalar_t__ active; } ;
struct TYPE_6__ {int /*<<< orphan*/  frad; TYPE_1__ state; int /*<<< orphan*/  dlci; } ;
typedef  TYPE_3__ pvc_device ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_P_802_3 ; 
 int ETH_ZLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  fr_hard_header (struct sk_buff**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t pvc_xmit(struct sk_buff *skb, struct net_device *dev)
{
	pvc_device *pvc = dev->ml_priv;

	if (pvc->state.active) {
		if (dev->type == ARPHRD_ETHER) {
			int pad = ETH_ZLEN - skb->len;
			if (pad > 0) { /* Pad the frame with zeros */
				int len = skb->len;
				if (skb_tailroom(skb) < pad)
					if (pskb_expand_head(skb, 0, pad,
							     GFP_ATOMIC)) {
						dev->stats.tx_dropped++;
						dev_kfree_skb(skb);
						return NETDEV_TX_OK;
					}
				skb_put(skb, pad);
				memset(skb->data + len, 0, pad);
			}
			skb->protocol = cpu_to_be16(ETH_P_802_3);
		}
		if (!fr_hard_header(&skb, pvc->dlci)) {
			dev->stats.tx_bytes += skb->len;
			dev->stats.tx_packets++;
			if (pvc->state.fecn) /* TX Congestion counter */
				dev->stats.tx_compressed++;
			skb->dev = pvc->frad;
			dev_queue_xmit(skb);
			return NETDEV_TX_OK;
		}
	}

	dev->stats.tx_dropped++;
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}