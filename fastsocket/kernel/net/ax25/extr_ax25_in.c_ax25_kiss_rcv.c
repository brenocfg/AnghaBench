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
struct sk_buff {int* data; } ;
struct packet_type {int dummy; } ;
struct net_device {scalar_t__ dev_addr; } ;
typedef  int /*<<< orphan*/  ax25_address ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_KISS_HEADER_LEN ; 
 int ax25_rcv (struct sk_buff*,struct net_device*,int /*<<< orphan*/ *,struct packet_type*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

int ax25_kiss_rcv(struct sk_buff *skb, struct net_device *dev,
		  struct packet_type *ptype, struct net_device *orig_dev)
{
	skb_orphan(skb);

	if (!net_eq(dev_net(dev), &init_net)) {
		kfree_skb(skb);
		return 0;
	}

	if ((*skb->data & 0x0F) != 0) {
		kfree_skb(skb);	/* Not a KISS data frame */
		return 0;
	}

	skb_pull(skb, AX25_KISS_HEADER_LEN);	/* Remove the KISS byte */

	return ax25_rcv(skb, dev, (ax25_address *)dev->dev_addr, ptype);
}