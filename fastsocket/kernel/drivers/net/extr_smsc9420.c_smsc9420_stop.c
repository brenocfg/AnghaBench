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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;
struct smsc9420_pdata {int /*<<< orphan*/  mii_bus; int /*<<< orphan*/ * phy_dev; int /*<<< orphan*/  napi; int /*<<< orphan*/  int_lock; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INT_CFG ; 
 int INT_CFG_IRQ_EN_ ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsc9420_dmac_soft_reset (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  smsc9420_free_rx_ring (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  smsc9420_free_tx_ring (struct smsc9420_pdata*) ; 
 int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsc9420_stop_rx (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  smsc9420_stop_tx (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smsc9420_stop(struct net_device *dev)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);
	u32 int_cfg;
	ulong flags;

	BUG_ON(!pd);
	BUG_ON(!pd->phy_dev);

	/* disable master interrupt */
	spin_lock_irqsave(&pd->int_lock, flags);
	int_cfg = smsc9420_reg_read(pd, INT_CFG) & (~INT_CFG_IRQ_EN_);
	smsc9420_reg_write(pd, INT_CFG, int_cfg);
	spin_unlock_irqrestore(&pd->int_lock, flags);

	netif_tx_disable(dev);
	napi_disable(&pd->napi);

	smsc9420_stop_tx(pd);
	smsc9420_free_tx_ring(pd);

	smsc9420_stop_rx(pd);
	smsc9420_free_rx_ring(pd);

	free_irq(dev->irq, pd);

	smsc9420_dmac_soft_reset(pd);

	phy_stop(pd->phy_dev);

	phy_disconnect(pd->phy_dev);
	pd->phy_dev = NULL;
	mdiobus_unregister(pd->mii_bus);
	mdiobus_free(pd->mii_bus);

	return 0;
}