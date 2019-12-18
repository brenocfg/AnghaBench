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
struct net_device {int dummy; } ;
struct catc {int /*<<< orphan*/  ctrl_urb; int /*<<< orphan*/  irq_urb; int /*<<< orphan*/  tx_urb; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  timer; int /*<<< orphan*/  is_f5u011; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct catc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int catc_stop(struct net_device *netdev)
{
	struct catc *catc = netdev_priv(netdev);

	netif_stop_queue(netdev);

	if (!catc->is_f5u011)
		del_timer_sync(&catc->timer);

	usb_kill_urb(catc->rx_urb);
	usb_kill_urb(catc->tx_urb);
	usb_kill_urb(catc->irq_urb);
	usb_kill_urb(catc->ctrl_urb);

	return 0;
}