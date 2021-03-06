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
struct net_device {int /*<<< orphan*/  mc_count; int /*<<< orphan*/  mc_list; } ;

/* Variables and functions */
 int __dev_addr_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,int) ; 
 int /*<<< orphan*/  __dev_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (struct net_device*) ; 

int dev_mc_delete(struct net_device *dev, void *addr, int alen, int glbl)
{
	int err;

	netif_addr_lock_bh(dev);
	err = __dev_addr_delete(&dev->mc_list, &dev->mc_count,
				addr, alen, glbl);
	if (!err) {
		/*
		 *	We have altered the list, so the card
		 *	loaded filter is now wrong. Fix it
		 */

		__dev_set_rx_mode(dev);
	}
	netif_addr_unlock_bh(dev);
	return err;
}