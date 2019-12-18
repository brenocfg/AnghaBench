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
struct net_device {int /*<<< orphan*/  dev; } ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 struct mii_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mdio_bitbang (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 

__attribute__((used)) static int sh_mdio_release(struct net_device *ndev)
{
	struct mii_bus *bus = dev_get_drvdata(&ndev->dev);

	/* unregister mdio bus */
	mdiobus_unregister(bus);

	/* remove mdio bus info from net_device */
	dev_set_drvdata(&ndev->dev, NULL);

	/* free bitbang info */
	free_mdio_bitbang(bus);

	return 0;
}