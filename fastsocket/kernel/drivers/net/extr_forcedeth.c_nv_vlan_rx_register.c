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
struct vlan_group {int dummy; } ;
struct net_device {int dummy; } ;
struct fe_priv {int txrxctl_bits; int /*<<< orphan*/  lock; struct vlan_group* vlangrp; } ;

/* Variables and functions */
 int NVREG_TXRXCTL_VLANINS ; 
 int NVREG_TXRXCTL_VLANSTRIP ; 
 scalar_t__ NvRegTxRxControl ; 
 scalar_t__ get_hwbase (struct net_device*) ; 
 struct fe_priv* get_nvpriv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void nv_vlan_rx_register(struct net_device *dev, struct vlan_group *grp)
{
	struct fe_priv *np = get_nvpriv(dev);

	spin_lock_irq(&np->lock);

	/* save vlan group */
	np->vlangrp = grp;

	if (grp) {
		/* enable vlan on MAC */
		np->txrxctl_bits |= NVREG_TXRXCTL_VLANSTRIP | NVREG_TXRXCTL_VLANINS;
	} else {
		/* disable vlan on MAC */
		np->txrxctl_bits &= ~NVREG_TXRXCTL_VLANSTRIP;
		np->txrxctl_bits &= ~NVREG_TXRXCTL_VLANINS;
	}

	writel(np->txrxctl_bits, get_hwbase(dev) + NvRegTxRxControl);

	spin_unlock_irq(&np->lock);
}