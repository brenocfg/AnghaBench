#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;
struct bmac_data {TYPE_2__* mdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ ofdev; } ;

/* Variables and functions */
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct bmac_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void bmac_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct bmac_data *bp = netdev_priv(dev);
	strcpy(info->driver, "bmac");
	strcpy(info->bus_info, dev_name(&bp->mdev->ofdev.dev));
}