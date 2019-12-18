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
struct TYPE_3__ {int /*<<< orphan*/  usb; } ;
typedef  TYPE_1__ pegasus_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_VERSION ; 
 int /*<<< orphan*/  driver_name ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pegasus_get_drvinfo(struct net_device *dev,
				struct ethtool_drvinfo *info)
{
	pegasus_t *pegasus = netdev_priv(dev);
	strncpy(info->driver, driver_name, sizeof (info->driver) - 1);
	strncpy(info->version, DRIVER_VERSION, sizeof (info->version) - 1);
	usb_make_path(pegasus->usb, info->bus_info, sizeof (info->bus_info));
}