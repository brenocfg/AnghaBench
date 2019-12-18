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
struct platform_device {int dummy; } ;
struct korina_private {int /*<<< orphan*/  tx_dma_regs; int /*<<< orphan*/  rx_dma_regs; int /*<<< orphan*/  eth_regs; } ;
struct korina_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct korina_private* netdev_priv (int /*<<< orphan*/ ) ; 
 struct korina_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int korina_remove(struct platform_device *pdev)
{
	struct korina_device *bif = platform_get_drvdata(pdev);
	struct korina_private *lp = netdev_priv(bif->dev);

	iounmap(lp->eth_regs);
	iounmap(lp->rx_dma_regs);
	iounmap(lp->tx_dma_regs);

	platform_set_drvdata(pdev, NULL);
	unregister_netdev(bif->dev);
	free_netdev(bif->dev);

	return 0;
}