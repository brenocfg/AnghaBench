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
struct net_device {int flags; } ;
struct meth_private {int mac_ctrl; int dma_ctrl; } ;
struct TYPE_3__ {int mac_ctrl; int dma_ctrl; } ;
struct TYPE_4__ {TYPE_1__ eth; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int ENODEV ; 
 int IFF_PROMISC ; 
 int METH_ACCEPT_MCAST ; 
 int METH_DEFAULT_IPG ; 
 int METH_PROMISC ; 
 int METH_RX_DEPTH_SHIFT ; 
 int METH_RX_OFFSET_SHIFT ; 
 int RX_RING_ENTRIES ; 
 int SGI_MAC_RESET ; 
 int /*<<< orphan*/  load_eaddr (struct net_device*) ; 
 TYPE_2__* mace ; 
 scalar_t__ mdio_probe (struct meth_private*) ; 
 int /*<<< orphan*/  meth_check_link (struct net_device*) ; 
 struct meth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int meth_reset(struct net_device *dev)
{
	struct meth_private *priv = netdev_priv(dev);

	/* Reset card */
	mace->eth.mac_ctrl = SGI_MAC_RESET;
	udelay(1);
	mace->eth.mac_ctrl = 0;
	udelay(25);

	/* Load ethernet address */
	load_eaddr(dev);
	/* Should load some "errata", but later */

	/* Check for device */
	if (mdio_probe(priv) < 0) {
		DPRINTK("Unable to find PHY\n");
		return -ENODEV;
	}

	/* Initial mode: 10 | Half-duplex | Accept normal packets */
	priv->mac_ctrl = METH_ACCEPT_MCAST | METH_DEFAULT_IPG;
	if (dev->flags & IFF_PROMISC)
		priv->mac_ctrl |= METH_PROMISC;
	mace->eth.mac_ctrl = priv->mac_ctrl;

	/* Autonegotiate speed and duplex mode */
	meth_check_link(dev);

	/* Now set dma control, but don't enable DMA, yet */
	priv->dma_ctrl = (4 << METH_RX_OFFSET_SHIFT) |
			 (RX_RING_ENTRIES << METH_RX_DEPTH_SHIFT);
	mace->eth.dma_ctrl = priv->dma_ctrl;

	return 0;
}