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
typedef  int u8 ;
struct sk_buff {scalar_t__ protocol; int* data; int /*<<< orphan*/  dev; scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct dsa_slave_priv {int port; TYPE_3__* parent; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_6__ {int index; TYPE_2__* dst; } ;
struct TYPE_5__ {int /*<<< orphan*/  master_netdev; } ;

/* Variables and functions */
 int DSA_HLEN ; 
 int EDSA_HLEN ; 
 int ETH_ALEN ; 
 int ETH_P_8021Q ; 
 int ETH_P_EDSA ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ htons (int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

netdev_tx_t edsa_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_slave_priv *p = netdev_priv(dev);
	u8 *edsa_header;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	/*
	 * Convert the outermost 802.1q tag to a DSA tag and prepend
	 * a DSA ethertype field is the packet is tagged, or insert
	 * a DSA ethertype plus DSA tag between the addresses and the
	 * current ethertype field if the packet is untagged.
	 */
	if (skb->protocol == htons(ETH_P_8021Q)) {
		if (skb_cow_head(skb, DSA_HLEN) < 0)
			goto out_free;
		skb_push(skb, DSA_HLEN);

		memmove(skb->data, skb->data + DSA_HLEN, 2 * ETH_ALEN);

		/*
		 * Construct tagged FROM_CPU DSA tag from 802.1q tag.
		 */
		edsa_header = skb->data + 2 * ETH_ALEN;
		edsa_header[0] = (ETH_P_EDSA >> 8) & 0xff;
		edsa_header[1] = ETH_P_EDSA & 0xff;
		edsa_header[2] = 0x00;
		edsa_header[3] = 0x00;
		edsa_header[4] = 0x60 | p->parent->index;
		edsa_header[5] = p->port << 3;

		/*
		 * Move CFI field from byte 6 to byte 5.
		 */
		if (edsa_header[6] & 0x10) {
			edsa_header[5] |= 0x01;
			edsa_header[6] &= ~0x10;
		}
	} else {
		if (skb_cow_head(skb, EDSA_HLEN) < 0)
			goto out_free;
		skb_push(skb, EDSA_HLEN);

		memmove(skb->data, skb->data + EDSA_HLEN, 2 * ETH_ALEN);

		/*
		 * Construct untagged FROM_CPU DSA tag.
		 */
		edsa_header = skb->data + 2 * ETH_ALEN;
		edsa_header[0] = (ETH_P_EDSA >> 8) & 0xff;
		edsa_header[1] = ETH_P_EDSA & 0xff;
		edsa_header[2] = 0x00;
		edsa_header[3] = 0x00;
		edsa_header[4] = 0x40 | p->parent->index;
		edsa_header[5] = p->port << 3;
		edsa_header[6] = 0x00;
		edsa_header[7] = 0x00;
	}

	skb->protocol = htons(ETH_P_EDSA);

	skb->dev = p->parent->dst->master_netdev;
	dev_queue_xmit(skb);

	return NETDEV_TX_OK;

out_free:
	kfree_skb(skb);
	return NETDEV_TX_OK;
}