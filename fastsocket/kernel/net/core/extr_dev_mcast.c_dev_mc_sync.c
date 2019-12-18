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
 int __dev_addr_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dev_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (struct net_device*) ; 

int dev_mc_sync(struct net_device *to, struct net_device *from)
{
	int err = 0;

	netif_addr_lock_bh(to);
	err = __dev_addr_sync(&to->mc_list, &to->mc_count,
			      &from->mc_list, &from->mc_count);
	if (!err)
		__dev_set_rx_mode(to);
	netif_addr_unlock_bh(to);

	return err;
}