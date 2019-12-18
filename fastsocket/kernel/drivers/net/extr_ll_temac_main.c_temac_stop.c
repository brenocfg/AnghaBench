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
struct temac_local {int /*<<< orphan*/ * phy_dev; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; } ;
struct net_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int temac_stop(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);

	dev_dbg(&ndev->dev, "temac_close()\n");

	free_irq(lp->tx_irq, ndev);
	free_irq(lp->rx_irq, ndev);

	if (lp->phy_dev)
		phy_disconnect(lp->phy_dev);
	lp->phy_dev = NULL;

	return 0;
}