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
typedef  int /*<<< orphan*/  u32 ;
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BULK_IN_EP ; 
 int /*<<< orphan*/  BULK_OUT_EP ; 
 int /*<<< orphan*/  CTRL_EP ; 
 int /*<<< orphan*/  EP_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_IN_EP ; 
 int /*<<< orphan*/  INT_OUT_EP ; 
 int /*<<< orphan*/  ISOC_IN_EP ; 
 int /*<<< orphan*/  ISOC_OUT_EP ; 
 int usb_endpoint_dir_in (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_xfer_bulk (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_xfer_control (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_xfer_int (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_xfer_isoc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 xhci_get_endpoint_type(struct usb_device *udev,
		struct usb_host_endpoint *ep)
{
	int in;
	u32 type;

	in = usb_endpoint_dir_in(&ep->desc);
	if (usb_endpoint_xfer_control(&ep->desc)) {
		type = EP_TYPE(CTRL_EP);
	} else if (usb_endpoint_xfer_bulk(&ep->desc)) {
		if (in)
			type = EP_TYPE(BULK_IN_EP);
		else
			type = EP_TYPE(BULK_OUT_EP);
	} else if (usb_endpoint_xfer_isoc(&ep->desc)) {
		if (in)
			type = EP_TYPE(ISOC_IN_EP);
		else
			type = EP_TYPE(ISOC_OUT_EP);
	} else if (usb_endpoint_xfer_int(&ep->desc)) {
		if (in)
			type = EP_TYPE(INT_IN_EP);
		else
			type = EP_TYPE(INT_OUT_EP);
	} else {
		BUG();
	}
	return type;
}