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
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; } ;
struct ethoc {int /*<<< orphan*/  napi; TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int INT_MASK_ALL ; 
 int INT_MASK_BUSY ; 
 int INT_MASK_RX ; 
 int INT_MASK_TX ; 
 int /*<<< orphan*/  INT_SOURCE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ethoc_ack_irq (struct ethoc*,int) ; 
 int /*<<< orphan*/  ethoc_disable_irq (struct ethoc*,int) ; 
 int /*<<< orphan*/  ethoc_enable_irq (struct ethoc*,int) ; 
 int ethoc_read (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_tx (struct net_device*) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t ethoc_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct ethoc *priv = netdev_priv(dev);
	u32 pending;

	ethoc_disable_irq(priv, INT_MASK_ALL);
	pending = ethoc_read(priv, INT_SOURCE);
	if (unlikely(pending == 0)) {
		ethoc_enable_irq(priv, INT_MASK_ALL);
		return IRQ_NONE;
	}

	ethoc_ack_irq(priv, pending);

	if (pending & INT_MASK_BUSY) {
		dev_err(&dev->dev, "packet dropped\n");
		priv->stats.rx_dropped++;
	}

	if (pending & INT_MASK_RX) {
		if (napi_schedule_prep(&priv->napi))
			__napi_schedule(&priv->napi);
	} else {
		ethoc_enable_irq(priv, INT_MASK_RX);
	}

	if (pending & INT_MASK_TX)
		ethoc_tx(dev);

	ethoc_enable_irq(priv, INT_MASK_ALL & ~INT_MASK_RX);
	return IRQ_HANDLED;
}