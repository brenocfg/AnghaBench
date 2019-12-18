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
struct usbnet {int /*<<< orphan*/  flags; int /*<<< orphan*/  bh; int /*<<< orphan*/  rxq; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DEV_OPEN ; 
 int /*<<< orphan*/  EVENT_LINK_CHANGE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_urbs (struct usbnet*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __handle_link_change(struct usbnet *dev)
{
	if (!test_bit(EVENT_DEV_OPEN, &dev->flags))
		return;

	if (!netif_carrier_ok(dev->net)) {
		/* kill URBs for reading packets to save bus bandwidth */
		unlink_urbs(dev, &dev->rxq);

		/*
		 * tx_timeout will unlink URBs for sending packets and
		 * tx queue is stopped by netcore after link becomes off
		 */
	} else {
		/* submitting URBs for reading packets */
		tasklet_schedule(&dev->bh);
	}

	clear_bit(EVENT_LINK_CHANGE, &dev->flags);
}