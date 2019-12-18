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
struct spider_net_card {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERSION ; 
 int /*<<< orphan*/  memset (struct ethtool_drvinfo*,int /*<<< orphan*/ ,int) ; 
 struct spider_net_card* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spider_net_driver_name ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
spider_net_ethtool_get_drvinfo(struct net_device *netdev,
			       struct ethtool_drvinfo *drvinfo)
{
	struct spider_net_card *card;
	card = netdev_priv(netdev);

	/* clear and fill out info */
	memset(drvinfo, 0, sizeof(struct ethtool_drvinfo));
	strncpy(drvinfo->driver, spider_net_driver_name, 32);
	strncpy(drvinfo->version, VERSION, 32);
	strcpy(drvinfo->fw_version, "no information");
	strncpy(drvinfo->bus_info, pci_name(card->pdev), 32);
}