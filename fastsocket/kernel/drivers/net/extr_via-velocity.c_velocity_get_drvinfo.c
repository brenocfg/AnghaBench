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
struct velocity_info {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  VELOCITY_NAME ; 
 int /*<<< orphan*/  VELOCITY_VERSION ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void velocity_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct velocity_info *vptr = netdev_priv(dev);
	strcpy(info->driver, VELOCITY_NAME);
	strcpy(info->version, VELOCITY_VERSION);
	strcpy(info->bus_info, pci_name(vptr->pdev));
}