#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct TYPE_6__ {int bmAttributes; } ;
struct usb_host_endpoint {TYPE_3__ desc; } ;
struct cdc_ncm_ctx {struct usb_host_endpoint* out_ep; struct usb_host_endpoint* in_ep; struct usb_host_endpoint* status_ep; } ;
struct TYPE_4__ {scalar_t__ bNumEndpoints; } ;
struct TYPE_5__ {struct usb_host_endpoint* endpoint; TYPE_1__ desc; } ;

/* Variables and functions */
 int USB_ENDPOINT_XFERTYPE_MASK ; 
#define  USB_ENDPOINT_XFER_BULK 129 
#define  USB_ENDPOINT_XFER_INT 128 
 int /*<<< orphan*/  usb_endpoint_dir_in (TYPE_3__*) ; 

__attribute__((used)) static void
cdc_ncm_find_endpoints(struct cdc_ncm_ctx *ctx, struct usb_interface *intf)
{
	struct usb_host_endpoint *e;
	u8 ep;

	for (ep = 0; ep < intf->cur_altsetting->desc.bNumEndpoints; ep++) {

		e = intf->cur_altsetting->endpoint + ep;
		switch (e->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) {
		case USB_ENDPOINT_XFER_INT:
			if (usb_endpoint_dir_in(&e->desc)) {
				if (ctx->status_ep == NULL)
					ctx->status_ep = e;
			}
			break;

		case USB_ENDPOINT_XFER_BULK:
			if (usb_endpoint_dir_in(&e->desc)) {
				if (ctx->in_ep == NULL)
					ctx->in_ep = e;
			} else {
				if (ctx->out_ep == NULL)
					ctx->out_ep = e;
			}
			break;

		default:
			break;
		}
	}
}