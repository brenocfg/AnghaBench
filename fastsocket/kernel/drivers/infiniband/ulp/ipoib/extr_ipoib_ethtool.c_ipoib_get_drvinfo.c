#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ipoib_dev_priv {TYPE_1__* ca; } ;
struct ib_device_attr {int fw_ver; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  driver; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_query_device (TYPE_1__*,struct ib_device_attr*) ; 
 char* ipoib_driver_version ; 
 int /*<<< orphan*/  kfree (struct ib_device_attr*) ; 
 struct ib_device_attr* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ipoib_get_drvinfo(struct net_device *netdev,
			      struct ethtool_drvinfo *drvinfo)
{
	struct ipoib_dev_priv *priv = netdev_priv(netdev);
	struct ib_device_attr *attr;

	attr = kmalloc(sizeof(*attr), GFP_KERNEL);
	if (attr && !ib_query_device(priv->ca, attr))
		snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
			 "%d.%d.%d", (int)(attr->fw_ver >> 32),
			 (int)(attr->fw_ver >> 16) & 0xffff,
			 (int)attr->fw_ver & 0xffff);
	kfree(attr);

	strlcpy(drvinfo->bus_info, dev_name(priv->ca->dma_device),
		sizeof(drvinfo->bus_info));

	strlcpy(drvinfo->version, ipoib_driver_version,
		sizeof(drvinfo->version));

	strlcpy(drvinfo->driver, "ib_ipoib", sizeof(drvinfo->driver));
}