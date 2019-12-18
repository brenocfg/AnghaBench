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
struct mv643xx_eth_private {int /*<<< orphan*/  dev; int /*<<< orphan*/ * phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_detach (int /*<<< orphan*/ *) ; 
 struct mv643xx_eth_private* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv643xx_eth_remove(struct platform_device *pdev)
{
	struct mv643xx_eth_private *mp = platform_get_drvdata(pdev);

	unregister_netdev(mp->dev);
	if (mp->phy != NULL)
		phy_detach(mp->phy);
	flush_scheduled_work();
	free_netdev(mp->dev);

	platform_set_drvdata(pdev, NULL);

	return 0;
}