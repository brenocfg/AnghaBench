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
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_request {scalar_t__ length; int /*<<< orphan*/  complete; } ;
struct usb_ep {int dummy; } ;
struct gmidi_in_port {scalar_t__ active; } ;
struct gmidi_device {int /*<<< orphan*/  in_substream; struct gmidi_in_port in_port; struct usb_ep* in_ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct gmidi_device*,char*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct usb_request* alloc_ep_req (struct usb_ep*,scalar_t__) ; 
 scalar_t__ buflen ; 
 int /*<<< orphan*/  free_ep_req (struct usb_ep*,struct usb_request*) ; 
 int /*<<< orphan*/  gmidi_complete ; 
 int /*<<< orphan*/  gmidi_transmit_byte (struct usb_request*,struct gmidi_in_port*,int /*<<< orphan*/ ) ; 
 int snd_rawmidi_transmit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_ep_queue (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gmidi_transmit(struct gmidi_device *dev, struct usb_request *req)
{
	struct usb_ep *ep = dev->in_ep;
	struct gmidi_in_port *port = &dev->in_port;

	if (!ep) {
		return;
	}
	if (!req) {
		req = alloc_ep_req(ep, buflen);
	}
	if (!req) {
		ERROR(dev, "gmidi_transmit: alloc_ep_request failed\n");
		return;
	}
	req->length = 0;
	req->complete = gmidi_complete;

	if (port->active) {
		while (req->length + 3 < buflen) {
			uint8_t b;
			if (snd_rawmidi_transmit(dev->in_substream, &b, 1)
				!= 1)
			{
				port->active = 0;
				break;
			}
			gmidi_transmit_byte(req, port, b);
		}
	}
	if (req->length > 0) {
		usb_ep_queue(ep, req, GFP_ATOMIC);
	} else {
		free_ep_req(ep, req);
	}
}