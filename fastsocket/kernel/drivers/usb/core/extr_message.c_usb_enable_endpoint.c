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
struct usb_host_endpoint {int enabled; int /*<<< orphan*/  desc; } ;
struct usb_device {struct usb_host_endpoint** ep_in; struct usb_host_endpoint** ep_out; } ;

/* Variables and functions */
 int usb_endpoint_dir_out (int /*<<< orphan*/ *) ; 
 int usb_endpoint_num (int /*<<< orphan*/ *) ; 
 int usb_endpoint_xfer_control (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hcd_reset_endpoint (struct usb_device*,struct usb_host_endpoint*) ; 

void usb_enable_endpoint(struct usb_device *dev, struct usb_host_endpoint *ep,
		bool reset_ep)
{
	int epnum = usb_endpoint_num(&ep->desc);
	int is_out = usb_endpoint_dir_out(&ep->desc);
	int is_control = usb_endpoint_xfer_control(&ep->desc);

	if (reset_ep)
		usb_hcd_reset_endpoint(dev, ep);
	if (is_out || is_control)
		dev->ep_out[epnum] = ep;
	if (!is_out || is_control)
		dev->ep_in[epnum] = ep;
	ep->enabled = 1;
}