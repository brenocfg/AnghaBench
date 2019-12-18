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
struct net_device {TYPE_1__ dev; } ;
struct ems_usb {int /*<<< orphan*/  open_time; } ;
typedef  enum can_mode { ____Placeholder_can_mode } can_mode ;

/* Variables and functions */
#define  CAN_MODE_START 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SJA1000_MOD_NORMAL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ems_usb_write_mode (struct ems_usb*,int /*<<< orphan*/ ) ; 
 struct ems_usb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static int ems_usb_set_mode(struct net_device *netdev, enum can_mode mode)
{
	struct ems_usb *dev = netdev_priv(netdev);

	if (!dev->open_time)
		return -EINVAL;

	switch (mode) {
	case CAN_MODE_START:
		if (ems_usb_write_mode(dev, SJA1000_MOD_NORMAL))
			dev_warn(netdev->dev.parent, "couldn't start device");

		if (netif_queue_stopped(netdev))
			netif_wake_queue(netdev);
		break;

	default:
		return -EOPNOTSUPP;
	}

	return 0;
}