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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; TYPE_1__ dev; int /*<<< orphan*/  wireless_data; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  ml_priv; } ;
struct airo_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* alloc_netdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  wifi_setup ; 

__attribute__((used)) static struct net_device *init_wifidev(struct airo_info *ai,
					struct net_device *ethdev)
{
	int err;
	struct net_device *dev = alloc_netdev(0, "wifi%d", wifi_setup);
	if (!dev)
		return NULL;
	dev->ml_priv = ethdev->ml_priv;
	dev->irq = ethdev->irq;
	dev->base_addr = ethdev->base_addr;
	dev->wireless_data = ethdev->wireless_data;
	SET_NETDEV_DEV(dev, ethdev->dev.parent);
	memcpy(dev->dev_addr, ethdev->dev_addr, dev->addr_len);
	err = register_netdev(dev);
	if (err<0) {
		free_netdev(dev);
		return NULL;
	}
	return dev;
}