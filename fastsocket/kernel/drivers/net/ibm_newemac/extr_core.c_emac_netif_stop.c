#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct emac_instance {int no_mcast; TYPE_1__* ndev; int /*<<< orphan*/  commac; int /*<<< orphan*/  mal; } ;
struct TYPE_6__ {int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mal_poll_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_addr_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_addr_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_tx_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (TYPE_1__*) ; 

__attribute__((used)) static inline void emac_netif_stop(struct emac_instance *dev)
{
	netif_tx_lock_bh(dev->ndev);
	netif_addr_lock(dev->ndev);
	dev->no_mcast = 1;
	netif_addr_unlock(dev->ndev);
	netif_tx_unlock_bh(dev->ndev);
	dev->ndev->trans_start = jiffies;	/* prevent tx timeout */
	mal_poll_disable(dev->mal, &dev->commac);
	netif_tx_disable(dev->ndev);
}