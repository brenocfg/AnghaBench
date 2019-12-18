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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct netdrv_private {int tx_flag; int /*<<< orphan*/  dirty_tx; int /*<<< orphan*/  cur_tx; int /*<<< orphan*/ * tx_buf; TYPE_1__* tx_info; void* mmio_addr; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  trans_start; } ;
struct TYPE_2__ {scalar_t__ mapping; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int ETH_ZLEN ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  NETDRV_W32 (scalar_t__,int) ; 
 int NUM_TX_DESC ; 
 scalar_t__ TxStatus0 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct netdrv_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int netdrv_start_xmit (struct sk_buff *skb, struct net_device *dev)
{
	struct netdrv_private *tp = netdev_priv(dev);
	void *ioaddr = tp->mmio_addr;
	int entry;

	/* Calculate the next Tx descriptor entry. */
	entry = atomic_read (&tp->cur_tx) % NUM_TX_DESC;

	assert (tp->tx_info[entry].skb == NULL);
	assert (tp->tx_info[entry].mapping == 0);

	tp->tx_info[entry].skb = skb;
	/* tp->tx_info[entry].mapping = 0; */
	skb_copy_from_linear_data(skb, tp->tx_buf[entry], skb->len);

	/* Note: the chip doesn't have auto-pad! */
	NETDRV_W32 (TxStatus0 + (entry * sizeof(u32)),
		 tp->tx_flag | (skb->len >= ETH_ZLEN ? skb->len : ETH_ZLEN));

	dev->trans_start = jiffies;
	atomic_inc (&tp->cur_tx);
	if ((atomic_read (&tp->cur_tx) - atomic_read (&tp->dirty_tx)) >= NUM_TX_DESC)
		netif_stop_queue (dev);

	DPRINTK ("%s: Queued Tx packet at %p size %u to slot %d.\n",
		 dev->name, skb->data, skb->len, entry);

	return NETDEV_TX_OK;
}