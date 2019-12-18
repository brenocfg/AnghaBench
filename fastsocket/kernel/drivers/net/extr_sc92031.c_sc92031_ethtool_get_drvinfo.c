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
struct sc92031_priv {struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC92031_NAME ; 
 struct sc92031_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc92031_ethtool_get_drvinfo(struct net_device *dev,
		struct ethtool_drvinfo *drvinfo)
{
	struct sc92031_priv *priv = netdev_priv(dev);
	struct pci_dev *pdev = priv->pdev;

	strcpy(drvinfo->driver, SC92031_NAME);
	strcpy(drvinfo->bus_info, pci_name(pdev));
}