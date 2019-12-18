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
struct net_device {int /*<<< orphan*/  dev; } ;
struct catc {int /*<<< orphan*/  tx_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct catc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void catc_tx_timeout(struct net_device *netdev)
{
	struct catc *catc = netdev_priv(netdev);

	dev_warn(&netdev->dev, "Transmit timed out.\n");
	usb_unlink_urb(catc->tx_urb);
}