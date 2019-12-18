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
struct temac_local {int /*<<< orphan*/  dev; int /*<<< orphan*/ * phy_dev; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; scalar_t__ phy_node; int /*<<< orphan*/  ndev; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ll_temac_rx_irq ; 
 int /*<<< orphan*/  ll_temac_tx_irq ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/ * of_phy_connect (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  temac_adjust_link ; 
 int /*<<< orphan*/  temac_device_reset (struct net_device*) ; 

__attribute__((used)) static int temac_open(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	int rc;

	dev_dbg(&ndev->dev, "temac_open()\n");

	if (lp->phy_node) {
		lp->phy_dev = of_phy_connect(lp->ndev, lp->phy_node,
					     temac_adjust_link, 0, 0);
		if (!lp->phy_dev) {
			dev_err(lp->dev, "of_phy_connect() failed\n");
			return -ENODEV;
		}

		phy_start(lp->phy_dev);
	}

	rc = request_irq(lp->tx_irq, ll_temac_tx_irq, 0, ndev->name, ndev);
	if (rc)
		goto err_tx_irq;
	rc = request_irq(lp->rx_irq, ll_temac_rx_irq, 0, ndev->name, ndev);
	if (rc)
		goto err_rx_irq;

	temac_device_reset(ndev);
	return 0;

 err_rx_irq:
	free_irq(lp->tx_irq, ndev);
 err_tx_irq:
	if (lp->phy_dev)
		phy_disconnect(lp->phy_dev);
	lp->phy_dev = NULL;
	dev_err(lp->dev, "request_irq() failed\n");
	return rc;
}