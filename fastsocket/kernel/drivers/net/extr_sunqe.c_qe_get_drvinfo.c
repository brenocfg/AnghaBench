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
struct sunqe {struct of_device* op; } ;
struct of_device {int /*<<< orphan*/  node; } ;
struct net_device {int dummy; } ;
struct linux_prom_registers {int which_io; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct sunqe* netdev_priv (struct net_device*) ; 
 struct linux_prom_registers* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void qe_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	const struct linux_prom_registers *regs;
	struct sunqe *qep = netdev_priv(dev);
	struct of_device *op;

	strcpy(info->driver, "sunqe");
	strcpy(info->version, "3.0");

	op = qep->op;
	regs = of_get_property(op->node, "reg", NULL);
	if (regs)
		sprintf(info->bus_info, "SBUS:%d", regs->which_io);

}