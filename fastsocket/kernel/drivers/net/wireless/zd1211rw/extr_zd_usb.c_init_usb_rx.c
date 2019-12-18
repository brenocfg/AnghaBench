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
struct TYPE_3__ {unsigned long data; int /*<<< orphan*/  func; } ;
struct zd_usb_rx {int usb_packet_size; scalar_t__ fragment_length; TYPE_1__ reset_timer_tasklet; int /*<<< orphan*/  idle_work; int /*<<< orphan*/  setup_mutex; int /*<<< orphan*/  lock; } ;
struct zd_usb {int /*<<< orphan*/  intf; struct zd_usb_rx rx; } ;
struct TYPE_4__ {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  ZD_ASSERT (int) ; 
 TYPE_2__* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_rx_idle_timer_handler ; 
 int /*<<< orphan*/  zd_usb_reset_rx_idle_timer_tasklet ; 

__attribute__((used)) static inline void init_usb_rx(struct zd_usb *usb)
{
	struct zd_usb_rx *rx = &usb->rx;

	spin_lock_init(&rx->lock);
	mutex_init(&rx->setup_mutex);
	if (interface_to_usbdev(usb->intf)->speed == USB_SPEED_HIGH) {
		rx->usb_packet_size = 512;
	} else {
		rx->usb_packet_size = 64;
	}
	ZD_ASSERT(rx->fragment_length == 0);
	INIT_DELAYED_WORK(&rx->idle_work, zd_rx_idle_timer_handler);
	rx->reset_timer_tasklet.func = zd_usb_reset_rx_idle_timer_tasklet;
	rx->reset_timer_tasklet.data = (unsigned long)usb;
}