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
struct ucc_geth_private {int dummy; } ;
struct device {int dummy; } ;
struct of_device {struct device dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct ucc_geth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ucc_geth_memclean (struct ucc_geth_private*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ucc_geth_remove(struct of_device* ofdev)
{
	struct device *device = &ofdev->dev;
	struct net_device *dev = dev_get_drvdata(device);
	struct ucc_geth_private *ugeth = netdev_priv(dev);

	unregister_netdev(dev);
	free_netdev(dev);
	ucc_geth_memclean(ugeth);
	dev_set_drvdata(device, NULL);

	return 0;
}