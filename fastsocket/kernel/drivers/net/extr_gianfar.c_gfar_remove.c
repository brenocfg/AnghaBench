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
struct of_device {int /*<<< orphan*/  dev; } ;
struct gfar_private {int /*<<< orphan*/  ndev; int /*<<< orphan*/  regs; scalar_t__ tbi_node; scalar_t__ phy_node; } ;

/* Variables and functions */
 struct gfar_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (scalar_t__) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfar_remove(struct of_device *ofdev)
{
	struct gfar_private *priv = dev_get_drvdata(&ofdev->dev);

	if (priv->phy_node)
		of_node_put(priv->phy_node);
	if (priv->tbi_node)
		of_node_put(priv->tbi_node);

	dev_set_drvdata(&ofdev->dev, NULL);

	unregister_netdev(priv->ndev);
	iounmap(priv->regs);
	free_netdev(priv->ndev);

	return 0;
}