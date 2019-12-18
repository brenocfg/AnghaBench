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
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {unsigned int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct simeth_local {int /*<<< orphan*/  simfd; TYPE_1__ stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int ETH_ZLEN ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  frame_print (char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct simeth_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int simeth_debug ; 

__attribute__((used)) static int
simeth_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct simeth_local *local = netdev_priv(dev);

#if 0
	/* ensure we have at least ETH_ZLEN bytes (min frame size) */
	unsigned int length = ETH_ZLEN < skb->len ? skb->len : ETH_ZLEN;
	/* Where do the extra padding bytes comes from inthe skbuff ? */
#else
	/* the real driver in the host system is going to take care of that
	 * or maybe it's the NIC itself.
	 */
	unsigned int length = skb->len;
#endif

	local->stats.tx_bytes += skb->len;
	local->stats.tx_packets++;


	if (simeth_debug > 5) frame_print("simeth_tx", skb->data, length);

	netdev_send(local->simfd, skb->data, length);

	/*
	 * we are synchronous on write, so we don't simulate a
	 * trasnmit complete interrupt, thus we don't need to arm a tx
	 */

	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}