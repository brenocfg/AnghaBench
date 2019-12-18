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
struct net_device {int dummy; } ;
struct meth_private {int dma_ctrl; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {unsigned long int_stat; } ;
struct TYPE_4__ {TYPE_1__ eth; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int METH_DMA_RX_INT_EN ; 
 unsigned long METH_INT_ERROR ; 
 unsigned long METH_INT_RX_THRESHOLD ; 
 unsigned long METH_INT_TX_EMPTY ; 
 unsigned long METH_INT_TX_PKT ; 
 TYPE_2__* mace ; 
 int /*<<< orphan*/  meth_error (struct net_device*,unsigned long) ; 
 int /*<<< orphan*/  meth_rx (struct net_device*,unsigned long) ; 
 int /*<<< orphan*/  meth_tx_cleanup (struct net_device*,unsigned long) ; 
 struct meth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static irqreturn_t meth_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct meth_private *priv = netdev_priv(dev);
	unsigned long status;

	status = mace->eth.int_stat;
	while (status & 0xff) {
		/* First handle errors - if we get Rx underflow,
		 * Rx DMA will be disabled, and Rx handler will reenable
		 * it. I don't think it's possible to get Rx underflow,
		 * without getting Rx interrupt */
		if (status & METH_INT_ERROR) {
			meth_error(dev, status);
		}
		if (status & (METH_INT_TX_EMPTY | METH_INT_TX_PKT)) {
			/* a transmission is over: free the skb */
			meth_tx_cleanup(dev, status);
		}
		if (status & METH_INT_RX_THRESHOLD) {
			if (!(priv->dma_ctrl & METH_DMA_RX_INT_EN))
				break;
			/* send it to meth_rx for handling */
			meth_rx(dev, status);
		}
		status = mace->eth.int_stat;
	}

	return IRQ_HANDLED;
}