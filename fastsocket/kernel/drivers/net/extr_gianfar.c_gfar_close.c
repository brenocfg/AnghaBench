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
struct net_device {int dummy; } ;
struct gfar_private {int /*<<< orphan*/ * phydev; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  rx_recycle; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_gfar (struct net_device*) ; 

__attribute__((used)) static int gfar_close(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);

	napi_disable(&priv->napi);

	skb_queue_purge(&priv->rx_recycle);
	cancel_work_sync(&priv->reset_task);
	stop_gfar(dev);

	/* Disconnect from the PHY */
	phy_disconnect(priv->phydev);
	priv->phydev = NULL;

	netif_stop_queue(dev);

	return 0;
}