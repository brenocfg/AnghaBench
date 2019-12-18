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
struct sk_buff {char* data; scalar_t__ len; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_CUST ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,char*,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void
cpc_trace(struct net_device *dev, struct sk_buff *skb_main, char rx_tx)
{
	struct sk_buff *skb;

	if ((skb = dev_alloc_skb(10 + skb_main->len)) == NULL) {
		printk("%s: out of memory\n", dev->name);
		return;
	}
	skb_put(skb, 10 + skb_main->len);

	skb->dev = dev;
	skb->protocol = htons(ETH_P_CUST);
	skb_reset_mac_header(skb);
	skb->pkt_type = PACKET_HOST;
	skb->len = 10 + skb_main->len;

	skb_copy_to_linear_data(skb, dev->name, 5);
	skb->data[5] = '[';
	skb->data[6] = rx_tx;
	skb->data[7] = ']';
	skb->data[8] = ':';
	skb->data[9] = ' ';
	skb_copy_from_linear_data(skb_main, &skb->data[10], skb_main->len);

	netif_rx(skb);
}