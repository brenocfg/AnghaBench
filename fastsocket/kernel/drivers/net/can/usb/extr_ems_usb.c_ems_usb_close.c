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
struct ems_usb {scalar_t__ open_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  SJA1000_MOD_RM ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ems_usb_write_mode (struct ems_usb*,int /*<<< orphan*/ ) ; 
 struct ems_usb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  unlink_all_urbs (struct ems_usb*) ; 

__attribute__((used)) static int ems_usb_close(struct net_device *netdev)
{
	struct ems_usb *dev = netdev_priv(netdev);

	/* Stop polling */
	unlink_all_urbs(dev);

	netif_stop_queue(netdev);

	/* Set CAN controller to reset mode */
	if (ems_usb_write_mode(dev, SJA1000_MOD_RM))
		dev_warn(netdev->dev.parent, "couldn't stop device");

	close_candev(netdev);

	dev->open_time = 0;

	return 0;
}