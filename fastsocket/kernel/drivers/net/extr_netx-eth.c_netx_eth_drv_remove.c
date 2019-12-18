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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct netx_eth_priv {int /*<<< orphan*/  id; int /*<<< orphan*/  xc; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFIFO_MASK (int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_xc (int /*<<< orphan*/ ) ; 
 struct netx_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pfifo_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  xc_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netx_eth_drv_remove(struct platform_device *pdev)
{
	struct net_device *ndev = dev_get_drvdata(&pdev->dev);
	struct netx_eth_priv *priv = netdev_priv(ndev);

	platform_set_drvdata(pdev, NULL);

	unregister_netdev(ndev);
	xc_stop(priv->xc);
	free_xc(priv->xc);
	free_netdev(ndev);
	pfifo_free(PFIFO_MASK(priv->id));

	return 0;
}