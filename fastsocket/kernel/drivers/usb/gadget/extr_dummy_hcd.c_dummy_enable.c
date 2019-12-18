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
struct usb_ep {unsigned int maxpacket; int /*<<< orphan*/  name; } ;
struct usb_endpoint_descriptor {scalar_t__ bDescriptorType; int bmAttributes; int bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dummy_ep {scalar_t__ wedged; scalar_t__ halted; struct usb_endpoint_descriptor const* desc; TYPE_1__ ep; } ;
struct TYPE_4__ {int /*<<< orphan*/  speed; } ;
struct dummy {TYPE_2__ gadget; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESHUTDOWN ; 
 int USB_DIR_IN ; 
 scalar_t__ USB_DT_ENDPOINT ; 
#define  USB_ENDPOINT_XFER_BULK 132 
#define  USB_ENDPOINT_XFER_INT 131 
#define  USB_ENDPOINT_XFER_ISOC 130 
#define  USB_SPEED_FULL 129 
#define  USB_SPEED_HIGH 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ep0name ; 
 struct dummy* ep_to_dummy (struct dummy_ep*) ; 
 int /*<<< orphan*/  is_enabled (struct dummy*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udc_dev (struct dummy*) ; 
 struct dummy_ep* usb_ep_to_dummy_ep (struct usb_ep*) ; 

__attribute__((used)) static int
dummy_enable (struct usb_ep *_ep, const struct usb_endpoint_descriptor *desc)
{
	struct dummy		*dum;
	struct dummy_ep		*ep;
	unsigned		max;
	int			retval;

	ep = usb_ep_to_dummy_ep (_ep);
	if (!_ep || !desc || ep->desc || _ep->name == ep0name
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		return -EINVAL;
	dum = ep_to_dummy (ep);
	if (!dum->driver || !is_enabled (dum))
		return -ESHUTDOWN;
	max = le16_to_cpu(desc->wMaxPacketSize) & 0x3ff;

	/* drivers must not request bad settings, since lower levels
	 * (hardware or its drivers) may not check.  some endpoints
	 * can't do iso, many have maxpacket limitations, etc.
	 *
	 * since this "hardware" driver is here to help debugging, we
	 * have some extra sanity checks.  (there could be more though,
	 * especially for "ep9out" style fixed function ones.)
	 */
	retval = -EINVAL;
	switch (desc->bmAttributes & 0x03) {
	case USB_ENDPOINT_XFER_BULK:
		if (strstr (ep->ep.name, "-iso")
				|| strstr (ep->ep.name, "-int")) {
			goto done;
		}
		switch (dum->gadget.speed) {
		case USB_SPEED_HIGH:
			if (max == 512)
				break;
			goto done;
		case USB_SPEED_FULL:
			if (max == 8 || max == 16 || max == 32 || max == 64)
				/* we'll fake any legal size */
				break;
			/* save a return statement */
		default:
			goto done;
		}
		break;
	case USB_ENDPOINT_XFER_INT:
		if (strstr (ep->ep.name, "-iso")) /* bulk is ok */
			goto done;
		/* real hardware might not handle all packet sizes */
		switch (dum->gadget.speed) {
		case USB_SPEED_HIGH:
			if (max <= 1024)
				break;
			/* save a return statement */
		case USB_SPEED_FULL:
			if (max <= 64)
				break;
			/* save a return statement */
		default:
			if (max <= 8)
				break;
			goto done;
		}
		break;
	case USB_ENDPOINT_XFER_ISOC:
		if (strstr (ep->ep.name, "-bulk")
				|| strstr (ep->ep.name, "-int"))
			goto done;
		/* real hardware might not handle all packet sizes */
		switch (dum->gadget.speed) {
		case USB_SPEED_HIGH:
			if (max <= 1024)
				break;
			/* save a return statement */
		case USB_SPEED_FULL:
			if (max <= 1023)
				break;
			/* save a return statement */
		default:
			goto done;
		}
		break;
	default:
		/* few chips support control except on ep0 */
		goto done;
	}

	_ep->maxpacket = max;
	ep->desc = desc;

	dev_dbg (udc_dev(dum), "enabled %s (ep%d%s-%s) maxpacket %d\n",
		_ep->name,
		desc->bEndpointAddress & 0x0f,
		(desc->bEndpointAddress & USB_DIR_IN) ? "in" : "out",
		({ char *val;
		 switch (desc->bmAttributes & 0x03) {
		 case USB_ENDPOINT_XFER_BULK: val = "bulk"; break;
		 case USB_ENDPOINT_XFER_ISOC: val = "iso"; break;
		 case USB_ENDPOINT_XFER_INT: val = "intr"; break;
		 default: val = "ctrl"; break;
		 }; val; }),
		max);

	/* at this point real hardware should be NAKing transfers
	 * to that endpoint, until a buffer is queued to it.
	 */
	ep->halted = ep->wedged = 0;
	retval = 0;
done:
	return retval;
}