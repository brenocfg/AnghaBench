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
struct port {int* firmware; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* DRV_NAME ; 
 struct port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ixp4xx_get_drvinfo(struct net_device *dev,
			       struct ethtool_drvinfo *info)
{
	struct port *port = netdev_priv(dev);
	strcpy(info->driver, DRV_NAME);
	snprintf(info->fw_version, sizeof(info->fw_version), "%u:%u:%u:%u",
		 port->firmware[0], port->firmware[1],
		 port->firmware[2], port->firmware[3]);
	strcpy(info->bus_info, "internal");
}