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
struct ns83820 {int /*<<< orphan*/  pci_dev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct ns83820* PRIV (struct net_device*) ; 
 char* VERSION ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ns83820_get_drvinfo(struct net_device *ndev, struct ethtool_drvinfo *info)
{
	struct ns83820 *dev = PRIV(ndev);
	strcpy(info->driver, "ns83820");
	strcpy(info->version, VERSION);
	strcpy(info->bus_info, pci_name(dev->pci_dev));
}