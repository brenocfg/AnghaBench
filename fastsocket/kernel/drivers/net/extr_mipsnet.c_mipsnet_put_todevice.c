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
struct sk_buff {int len; char* data; } ;
struct TYPE_2__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  outb (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regaddr (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txDataBuffer ; 
 int /*<<< orphan*/  txDataCount ; 

__attribute__((used)) static inline void mipsnet_put_todevice(struct net_device *dev,
	struct sk_buff *skb)
{
	int count_to_go = skb->len;
	char *buf_ptr = skb->data;

	outl(skb->len, regaddr(dev, txDataCount));

	for (; count_to_go; buf_ptr++, count_to_go--)
		outb(*buf_ptr, regaddr(dev, txDataBuffer));

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	dev_kfree_skb(skb);
}