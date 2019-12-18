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
struct strip {int /*<<< orphan*/  true_dev_addr; } ;
struct sk_buff {int dummy; } ;
struct net_device {int hard_header_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  protocol; int /*<<< orphan*/  src_addr; } ;
typedef  TYPE_1__ STRIP_Header ;
typedef  int /*<<< orphan*/  MetricomAddress ;

/* Variables and functions */
 int /*<<< orphan*/  htons (unsigned short) ; 
 struct strip* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int strip_header(struct sk_buff *skb, struct net_device *dev,
			unsigned short type, const void *daddr,
			const void *saddr, unsigned len)
{
	struct strip *strip_info = netdev_priv(dev);
	STRIP_Header *header = (STRIP_Header *) skb_push(skb, sizeof(STRIP_Header));

	/*printk(KERN_INFO "%s: strip_header 0x%04X %s\n", dev->name, type,
	   type == ETH_P_IP ? "IP" : type == ETH_P_ARP ? "ARP" : ""); */

	header->src_addr = strip_info->true_dev_addr;
	header->protocol = htons(type);

	/*HexDump("strip_header", netdev_priv(dev), skb->data, skb->data + skb->len); */

	if (!daddr)
		return (-dev->hard_header_len);

	header->dst_addr = *(MetricomAddress *) daddr;
	return (dev->hard_header_len);
}