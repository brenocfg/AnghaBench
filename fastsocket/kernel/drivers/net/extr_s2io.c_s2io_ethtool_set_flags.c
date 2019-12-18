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
typedef  int u32 ;
struct s2io_nic {int lro; } ;
struct net_device {int features; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_FLAG_LRO ; 
 int NETIF_F_LRO ; 
 scalar_t__ lro_enable ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  s2io_card_down (struct s2io_nic*) ; 
 int s2io_card_up (struct s2io_nic*) ; 
 int /*<<< orphan*/  s2io_reset (struct s2io_nic*) ; 
 int /*<<< orphan*/  s2io_start_all_tx_queue (struct s2io_nic*) ; 
 int /*<<< orphan*/  s2io_stop_all_tx_queue (struct s2io_nic*) ; 

__attribute__((used)) static int s2io_ethtool_set_flags(struct net_device *dev, u32 data)
{
	struct s2io_nic *sp = netdev_priv(dev);
	int rc = 0;
	int changed = 0;

	if (data & ~ETH_FLAG_LRO)
		return -EINVAL;

	if (data & ETH_FLAG_LRO) {
		if (lro_enable) {
			if (!(dev->features & NETIF_F_LRO)) {
				dev->features |= NETIF_F_LRO;
				changed = 1;
			}
		} else
			rc = -EINVAL;
	} else if (dev->features & NETIF_F_LRO) {
		dev->features &= ~NETIF_F_LRO;
		changed = 1;
	}

	if (changed && netif_running(dev)) {
		s2io_stop_all_tx_queue(sp);
		s2io_card_down(sp);
		sp->lro = !!(dev->features & NETIF_F_LRO);
		rc = s2io_card_up(sp);
		if (rc)
			s2io_reset(sp);
		else
			s2io_start_all_tx_queue(sp);
	}

	return rc;
}