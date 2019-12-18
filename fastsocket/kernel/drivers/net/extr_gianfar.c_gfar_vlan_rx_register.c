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
struct vlan_group {int dummy; } ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct gfar_private {int /*<<< orphan*/  rxlock; TYPE_1__* regs; struct vlan_group* vlgrp; } ;
struct TYPE_2__ {int /*<<< orphan*/  rctrl; int /*<<< orphan*/  tctrl; } ;

/* Variables and functions */
 int RCTRL_PRSDEP_INIT ; 
 int RCTRL_REQ_PARSER ; 
 int RCTRL_VLEX ; 
 int TCTRL_VLINS ; 
 int /*<<< orphan*/  gfar_change_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int gfar_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfar_write (int /*<<< orphan*/ *,int) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gfar_vlan_rx_register(struct net_device *dev,
		struct vlan_group *grp)
{
	struct gfar_private *priv = netdev_priv(dev);
	unsigned long flags;
	u32 tempval;

	spin_lock_irqsave(&priv->rxlock, flags);

	priv->vlgrp = grp;

	if (grp) {
		/* Enable VLAN tag insertion */
		tempval = gfar_read(&priv->regs->tctrl);
		tempval |= TCTRL_VLINS;

		gfar_write(&priv->regs->tctrl, tempval);

		/* Enable VLAN tag extraction */
		tempval = gfar_read(&priv->regs->rctrl);
		tempval |= (RCTRL_VLEX | RCTRL_PRSDEP_INIT);
		gfar_write(&priv->regs->rctrl, tempval);
	} else {
		/* Disable VLAN tag insertion */
		tempval = gfar_read(&priv->regs->tctrl);
		tempval &= ~TCTRL_VLINS;
		gfar_write(&priv->regs->tctrl, tempval);

		/* Disable VLAN tag extraction */
		tempval = gfar_read(&priv->regs->rctrl);
		tempval &= ~RCTRL_VLEX;
		/* If parse is no longer required, then disable parser */
		if (tempval & RCTRL_REQ_PARSER)
			tempval |= RCTRL_PRSDEP_INIT;
		else
			tempval &= ~RCTRL_PRSDEP_INIT;
		gfar_write(&priv->regs->rctrl, tempval);
	}

	gfar_change_mtu(dev, dev->mtu);

	spin_unlock_irqrestore(&priv->rxlock, flags);
}