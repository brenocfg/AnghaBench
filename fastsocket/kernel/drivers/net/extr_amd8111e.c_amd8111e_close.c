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
struct net_device {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipg_timer; } ;
struct amd8111e_priv {int options; scalar_t__ opened; int /*<<< orphan*/  lock; TYPE_1__ ipg_data; int /*<<< orphan*/  amd8111e_net_dev; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int OPTION_DYN_IPG_ENABLE ; 
 int /*<<< orphan*/  amd8111e_disable_interrupt (struct amd8111e_priv*) ; 
 int /*<<< orphan*/  amd8111e_free_ring (struct amd8111e_priv*) ; 
 int /*<<< orphan*/  amd8111e_free_skbs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd8111e_get_stats (struct net_device*) ; 
 int /*<<< orphan*/  amd8111e_stop_chip (struct amd8111e_priv*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amd8111e_close(struct net_device * dev)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	netif_stop_queue(dev);

	napi_disable(&lp->napi);

	spin_lock_irq(&lp->lock);

	amd8111e_disable_interrupt(lp);
	amd8111e_stop_chip(lp);

	/* Free transmit and receive skbs */
	amd8111e_free_skbs(lp->amd8111e_net_dev);

	netif_carrier_off(lp->amd8111e_net_dev);

	/* Delete ipg timer */
	if(lp->options & OPTION_DYN_IPG_ENABLE)
		del_timer_sync(&lp->ipg_data.ipg_timer);

	spin_unlock_irq(&lp->lock);
	free_irq(dev->irq, dev);
	amd8111e_free_ring(lp);

	/* Update the statistics before closing */
	amd8111e_get_stats(dev);
	lp->opened = 0;
	return 0;
}