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
typedef  int /*<<< orphan*/  u16 ;
struct usba_udc {int devstatus; int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; TYPE_1__* driver; int /*<<< orphan*/  test_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct usba_ep {TYPE_2__ ep; int /*<<< orphan*/  state; int /*<<< orphan*/  index; int /*<<< orphan*/  fifo; } ;
struct usb_ctrlrequest {int bRequest; int bRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
typedef  int /*<<< orphan*/  status ;
struct TYPE_3__ {int (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_STA ; 
 int /*<<< orphan*/  DATA_STAGE_IN ; 
 int /*<<< orphan*/  SET_STA ; 
 int /*<<< orphan*/  STATUS_STAGE_ADDR ; 
 int /*<<< orphan*/  STATUS_STAGE_TEST ; 
 int /*<<< orphan*/  USBA_FORCE_STALL ; 
 int /*<<< orphan*/  USBA_TOGGLE_CLR ; 
 int /*<<< orphan*/  USBA_TX_PK_RDY ; 
 int USB_DEVICE_REMOTE_WAKEUP ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_RECIP_INTERFACE ; 
#define  USB_REQ_CLEAR_FEATURE 131 
#define  USB_REQ_GET_STATUS 130 
#define  USB_REQ_SET_ADDRESS 129 
#define  USB_REQ_SET_FEATURE 128 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  feature_is_dev_remote_wakeup (struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  feature_is_dev_test_mode (struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  feature_is_ep_halt (struct usb_ctrlrequest*) ; 
 struct usba_ep* get_ep_by_addr (struct usba_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_stalled (struct usba_udc*,struct usba_ep*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_status (struct usba_udc*,struct usba_ep*) ; 
 int /*<<< orphan*/  set_address (struct usba_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_protocol_stall (struct usba_udc*,struct usba_ep*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  usba_ep_writel (struct usba_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_ep0_setup(struct usba_udc *udc, struct usba_ep *ep,
		struct usb_ctrlrequest *crq)
{
	int retval = 0;

	switch (crq->bRequest) {
	case USB_REQ_GET_STATUS: {
		u16 status;

		if (crq->bRequestType == (USB_DIR_IN | USB_RECIP_DEVICE)) {
			status = cpu_to_le16(udc->devstatus);
		} else if (crq->bRequestType
				== (USB_DIR_IN | USB_RECIP_INTERFACE)) {
			status = cpu_to_le16(0);
		} else if (crq->bRequestType
				== (USB_DIR_IN | USB_RECIP_ENDPOINT)) {
			struct usba_ep *target;

			target = get_ep_by_addr(udc, le16_to_cpu(crq->wIndex));
			if (!target)
				goto stall;

			status = 0;
			if (is_stalled(udc, target))
				status |= cpu_to_le16(1);
		} else
			goto delegate;

		/* Write directly to the FIFO. No queueing is done. */
		if (crq->wLength != cpu_to_le16(sizeof(status)))
			goto stall;
		ep->state = DATA_STAGE_IN;
		__raw_writew(status, ep->fifo);
		usba_ep_writel(ep, SET_STA, USBA_TX_PK_RDY);
		break;
	}

	case USB_REQ_CLEAR_FEATURE: {
		if (crq->bRequestType == USB_RECIP_DEVICE) {
			if (feature_is_dev_remote_wakeup(crq))
				udc->devstatus
					&= ~(1 << USB_DEVICE_REMOTE_WAKEUP);
			else
				/* Can't CLEAR_FEATURE TEST_MODE */
				goto stall;
		} else if (crq->bRequestType == USB_RECIP_ENDPOINT) {
			struct usba_ep *target;

			if (crq->wLength != cpu_to_le16(0)
					|| !feature_is_ep_halt(crq))
				goto stall;
			target = get_ep_by_addr(udc, le16_to_cpu(crq->wIndex));
			if (!target)
				goto stall;

			usba_ep_writel(target, CLR_STA, USBA_FORCE_STALL);
			if (target->index != 0)
				usba_ep_writel(target, CLR_STA,
						USBA_TOGGLE_CLR);
		} else {
			goto delegate;
		}

		send_status(udc, ep);
		break;
	}

	case USB_REQ_SET_FEATURE: {
		if (crq->bRequestType == USB_RECIP_DEVICE) {
			if (feature_is_dev_test_mode(crq)) {
				send_status(udc, ep);
				ep->state = STATUS_STAGE_TEST;
				udc->test_mode = le16_to_cpu(crq->wIndex);
				return 0;
			} else if (feature_is_dev_remote_wakeup(crq)) {
				udc->devstatus |= 1 << USB_DEVICE_REMOTE_WAKEUP;
			} else {
				goto stall;
			}
		} else if (crq->bRequestType == USB_RECIP_ENDPOINT) {
			struct usba_ep *target;

			if (crq->wLength != cpu_to_le16(0)
					|| !feature_is_ep_halt(crq))
				goto stall;

			target = get_ep_by_addr(udc, le16_to_cpu(crq->wIndex));
			if (!target)
				goto stall;

			usba_ep_writel(target, SET_STA, USBA_FORCE_STALL);
		} else
			goto delegate;

		send_status(udc, ep);
		break;
	}

	case USB_REQ_SET_ADDRESS:
		if (crq->bRequestType != (USB_DIR_OUT | USB_RECIP_DEVICE))
			goto delegate;

		set_address(udc, le16_to_cpu(crq->wValue));
		send_status(udc, ep);
		ep->state = STATUS_STAGE_ADDR;
		break;

	default:
delegate:
		spin_unlock(&udc->lock);
		retval = udc->driver->setup(&udc->gadget, crq);
		spin_lock(&udc->lock);
	}

	return retval;

stall:
	pr_err("udc: %s: Invalid setup request: %02x.%02x v%04x i%04x l%d, "
		"halting endpoint...\n",
		ep->ep.name, crq->bRequestType, crq->bRequest,
		le16_to_cpu(crq->wValue), le16_to_cpu(crq->wIndex),
		le16_to_cpu(crq->wLength));
	set_protocol_stall(udc, ep);
	return -1;
}