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
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct lt_sendlap {int length; int /*<<< orphan*/  laptype; int /*<<< orphan*/  dnode; int /*<<< orphan*/  command; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  cbuf ;

/* Variables and functions */
 int DEBUG_UPPER ; 
 int /*<<< orphan*/  LT_SENDLAP ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int debug ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  do_write (struct net_device*,struct lt_sendlap*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 unsigned char* skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t ltpc_xmit(struct sk_buff *skb, struct net_device *dev)
{
	/* in kernel 1.3.xx, on entry skb->data points to ddp header,
	 * and skb->len is the length of the ddp data + ddp header
	 */
	int i;
	struct lt_sendlap cbuf;
	unsigned char *hdr;

	cbuf.command = LT_SENDLAP;
	cbuf.dnode = skb->data[0];
	cbuf.laptype = skb->data[2];
	skb_pull(skb,3);	/* skip past LLAP header */
	cbuf.length = skb->len;	/* this is host order */
	skb_reset_transport_header(skb);

	if(debug & DEBUG_UPPER) {
		printk("command ");
		for(i=0;i<6;i++)
			printk("%02x ",((unsigned char *)&cbuf)[i]);
		printk("\n");
	}

	hdr = skb_transport_header(skb);
	do_write(dev, &cbuf, sizeof(cbuf), hdr, skb->len);

	if(debug & DEBUG_UPPER) {
		printk("sent %d ddp bytes\n",skb->len);
		for (i = 0; i < skb->len; i++)
			printk("%02x ", hdr[i]);
		printk("\n");
	}

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}