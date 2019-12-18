#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  udev; } ;
typedef  TYPE_1__ rtl8150_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_VERSION ; 
 int /*<<< orphan*/  ETHTOOL_BUSINFO_LEN ; 
 int /*<<< orphan*/  driver_name ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8150_get_drvinfo(struct net_device *netdev, struct ethtool_drvinfo *info)
{
	rtl8150_t *dev = netdev_priv(netdev);

	strncpy(info->driver, driver_name, ETHTOOL_BUSINFO_LEN);
	strncpy(info->version, DRIVER_VERSION, ETHTOOL_BUSINFO_LEN);
	usb_make_path(dev->udev, info->bus_info, sizeof info->bus_info);
}