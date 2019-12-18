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
struct usb_gadget_driver {int /*<<< orphan*/  (* disconnect ) (TYPE_1__*) ;} ;
struct musb_hw_ep {int /*<<< orphan*/  ep_out; scalar_t__ max_packet_sz_rx; int /*<<< orphan*/  ep_in; scalar_t__ max_packet_sz_tx; scalar_t__ is_shared_fifo; } ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct musb {int nr_endpoints; int /*<<< orphan*/  lock; TYPE_1__ g; int /*<<< orphan*/  mregs; struct musb_hw_ep* endpoints; scalar_t__ softconnect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  musb_ep_select (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  musb_pullup (struct musb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_stop (struct musb*) ; 
 int /*<<< orphan*/  nuke (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void stop_activity(struct musb *musb, struct usb_gadget_driver *driver)
{
	int			i;
	struct musb_hw_ep	*hw_ep;

	/* don't disconnect if it's not connected */
	if (musb->g.speed == USB_SPEED_UNKNOWN)
		driver = NULL;
	else
		musb->g.speed = USB_SPEED_UNKNOWN;

	/* deactivate the hardware */
	if (musb->softconnect) {
		musb->softconnect = 0;
		musb_pullup(musb, 0);
	}
	musb_stop(musb);

	/* killing any outstanding requests will quiesce the driver;
	 * then report disconnect
	 */
	if (driver) {
		for (i = 0, hw_ep = musb->endpoints;
				i < musb->nr_endpoints;
				i++, hw_ep++) {
			musb_ep_select(musb->mregs, i);
			if (hw_ep->is_shared_fifo /* || !epnum */) {
				nuke(&hw_ep->ep_in, -ESHUTDOWN);
			} else {
				if (hw_ep->max_packet_sz_tx)
					nuke(&hw_ep->ep_in, -ESHUTDOWN);
				if (hw_ep->max_packet_sz_rx)
					nuke(&hw_ep->ep_out, -ESHUTDOWN);
			}
		}

		spin_unlock(&musb->lock);
		driver->disconnect(&musb->g);
		spin_lock(&musb->lock);
	}
}