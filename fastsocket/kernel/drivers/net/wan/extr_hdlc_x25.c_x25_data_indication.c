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
struct sk_buff {unsigned char* data; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int netif_rx (struct sk_buff*) ; 
 scalar_t__ skb_cow (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  x25_type_trans (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static int x25_data_indication(struct net_device *dev, struct sk_buff *skb)
{
	unsigned char *ptr;

	skb_push(skb, 1);

	if (skb_cow(skb, 1))
		return NET_RX_DROP;

	ptr  = skb->data;
	*ptr = 0;

	skb->protocol = x25_type_trans(skb, dev);
	return netif_rx(skb);
}