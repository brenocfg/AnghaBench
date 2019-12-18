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
struct mac_info {struct fifo_info* fifos; } ;
struct config_param {int tx_fifo_num; } ;
struct s2io_nic {struct vlan_group* vlgrp; struct mac_info mac_control; struct config_param config; } ;
struct net_device {int dummy; } ;
struct fifo_info {int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int MAX_TX_FIFOS ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void s2io_vlan_rx_register(struct net_device *dev,
				  struct vlan_group *grp)
{
	int i;
	struct s2io_nic *nic = netdev_priv(dev);
	unsigned long flags[MAX_TX_FIFOS];
	struct config_param *config = &nic->config;
	struct mac_info *mac_control = &nic->mac_control;

	for (i = 0; i < config->tx_fifo_num; i++) {
		struct fifo_info *fifo = &mac_control->fifos[i];

		spin_lock_irqsave(&fifo->tx_lock, flags[i]);
	}

	nic->vlgrp = grp;

	for (i = config->tx_fifo_num - 1; i >= 0; i--) {
		struct fifo_info *fifo = &mac_control->fifos[i];

		spin_unlock_irqrestore(&fifo->tx_lock, flags[i]);
	}
}