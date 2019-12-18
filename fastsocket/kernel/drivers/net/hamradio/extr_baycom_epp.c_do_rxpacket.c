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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_2__ stats; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int bufcnt; int /*<<< orphan*/  buf; } ;
struct baycom_state {TYPE_1__ hdlcrx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  check_crc_ccitt (int /*<<< orphan*/ ,int) ; 
 struct sk_buff* dev_alloc_skb (unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct baycom_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 unsigned char* skb_put (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static void do_rxpacket(struct net_device *dev)
{
	struct baycom_state *bc = netdev_priv(dev);
	struct sk_buff *skb;
	unsigned char *cp;
	unsigned pktlen;

	if (bc->hdlcrx.bufcnt < 4) 
		return;
	if (!check_crc_ccitt(bc->hdlcrx.buf, bc->hdlcrx.bufcnt)) 
		return;
	pktlen = bc->hdlcrx.bufcnt-2+1; /* KISS kludge */
	if (!(skb = dev_alloc_skb(pktlen))) {
		printk("%s: memory squeeze, dropping packet\n", dev->name);
		dev->stats.rx_dropped++;
		return;
	}
	cp = skb_put(skb, pktlen);
	*cp++ = 0; /* KISS kludge */
	memcpy(cp, bc->hdlcrx.buf, pktlen - 1);
	skb->protocol = ax25_type_trans(skb, dev);
	netif_rx(skb);
	dev->stats.rx_packets++;
}