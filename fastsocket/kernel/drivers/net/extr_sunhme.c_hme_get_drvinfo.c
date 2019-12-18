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
struct pci_dev {int /*<<< orphan*/  node; } ;
struct of_device {int /*<<< orphan*/  node; } ;
struct net_device {int dummy; } ;
struct linux_prom_registers {int which_io; } ;
struct happy_meal {int happy_flags; struct pci_dev* happy_dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int HFLAG_PCI ; 
 struct happy_meal* netdev_priv (struct net_device*) ; 
 struct linux_prom_registers* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void hme_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct happy_meal *hp = netdev_priv(dev);

	strcpy(info->driver, "sunhme");
	strcpy(info->version, "2.02");
	if (hp->happy_flags & HFLAG_PCI) {
		struct pci_dev *pdev = hp->happy_dev;
		strcpy(info->bus_info, pci_name(pdev));
	}
#ifdef CONFIG_SBUS
	else {
		const struct linux_prom_registers *regs;
		struct of_device *op = hp->happy_dev;
		regs = of_get_property(op->node, "regs", NULL);
		if (regs)
			sprintf(info->bus_info, "SBUS:%d",
				regs->which_io);
	}
#endif
}