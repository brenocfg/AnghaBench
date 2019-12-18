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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct usb_endpoint_descriptor {int bmAttributes; int bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_3__ {int /*<<< orphan*/  speed; } ;
struct qe_udc {int ep0_dir; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  ep0_state; TYPE_1__ gadget; struct qe_ep* eps; } ;
struct TYPE_4__ {int maxpacket; int /*<<< orphan*/  name; } ;
struct qe_ep {scalar_t__ tm; int init; int dir; TYPE_2__ ep; int /*<<< orphan*/  rxframe; int /*<<< orphan*/  rxbuffer; int /*<<< orphan*/ * txframe; scalar_t__ stopped; struct usb_endpoint_descriptor const* desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ USBP_TM_CTL ; 
 int USB_DIR_BOTH ; 
#define  USB_DIR_IN 136 
#define  USB_DIR_OUT 135 
 int USB_ENDPOINT_DIR_MASK ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
#define  USB_ENDPOINT_XFER_BULK 134 
#define  USB_ENDPOINT_XFER_CONTROL 133 
#define  USB_ENDPOINT_XFER_INT 132 
#define  USB_ENDPOINT_XFER_ISOC 131 
#define  USB_SPEED_FULL 130 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_LOW 128 
 int /*<<< orphan*/  WAIT_FOR_SETUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_ep_bd_init (struct qe_udc*,unsigned char) ; 
 int /*<<< orphan*/  qe_ep_register_init (struct qe_udc*,unsigned char) ; 
 int qe_ep_rxbd_update (struct qe_ep*) ; 
 int /*<<< orphan*/  qe_frame_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int qe_ep_init(struct qe_udc *udc,
		      unsigned char pipe_num,
		      const struct usb_endpoint_descriptor *desc)
{
	struct qe_ep *ep = &udc->eps[pipe_num];
	unsigned long flags;
	int reval = 0;
	u16 max = 0;

	max = le16_to_cpu(desc->wMaxPacketSize);

	/* check the max package size validate for this endpoint */
	/* Refer to USB2.0 spec table 9-13,
	*/
	if (pipe_num != 0) {
		switch (desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) {
		case USB_ENDPOINT_XFER_BULK:
			if (strstr(ep->ep.name, "-iso")
					|| strstr(ep->ep.name, "-int"))
				goto en_done;
			switch (udc->gadget.speed) {
			case USB_SPEED_HIGH:
			if ((max == 128) || (max == 256) || (max == 512))
				break;
			default:
				switch (max) {
				case 4:
				case 8:
				case 16:
				case 32:
				case 64:
					break;
				default:
				case USB_SPEED_LOW:
					goto en_done;
				}
			}
			break;
		case USB_ENDPOINT_XFER_INT:
			if (strstr(ep->ep.name, "-iso"))	/* bulk is ok */
				goto en_done;
			switch (udc->gadget.speed) {
			case USB_SPEED_HIGH:
				if (max <= 1024)
					break;
			case USB_SPEED_FULL:
				if (max <= 64)
					break;
			default:
				if (max <= 8)
					break;
				goto en_done;
			}
			break;
		case USB_ENDPOINT_XFER_ISOC:
			if (strstr(ep->ep.name, "-bulk")
				|| strstr(ep->ep.name, "-int"))
				goto en_done;
			switch (udc->gadget.speed) {
			case USB_SPEED_HIGH:
				if (max <= 1024)
					break;
			case USB_SPEED_FULL:
				if (max <= 1023)
					break;
			default:
				goto en_done;
			}
			break;
		case USB_ENDPOINT_XFER_CONTROL:
			if (strstr(ep->ep.name, "-iso")
				|| strstr(ep->ep.name, "-int"))
				goto en_done;
			switch (udc->gadget.speed) {
			case USB_SPEED_HIGH:
			case USB_SPEED_FULL:
				switch (max) {
				case 1:
				case 2:
				case 4:
				case 8:
				case 16:
				case 32:
				case 64:
					break;
				default:
					goto en_done;
				}
			case USB_SPEED_LOW:
				switch (max) {
				case 1:
				case 2:
				case 4:
				case 8:
					break;
				default:
					goto en_done;
				}
			default:
				goto en_done;
			}
			break;

		default:
			goto en_done;
		}
	} /* if ep0*/

	spin_lock_irqsave(&udc->lock, flags);

	/* initialize ep structure */
	ep->ep.maxpacket = max;
	ep->tm = (u8)(desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK);
	ep->desc = desc;
	ep->stopped = 0;
	ep->init = 1;

	if (pipe_num == 0) {
		ep->dir = USB_DIR_BOTH;
		udc->ep0_dir = USB_DIR_OUT;
		udc->ep0_state = WAIT_FOR_SETUP;
	} else	{
		switch (desc->bEndpointAddress & USB_ENDPOINT_DIR_MASK) {
		case USB_DIR_OUT:
			ep->dir = USB_DIR_OUT;
			break;
		case USB_DIR_IN:
			ep->dir = USB_DIR_IN;
		default:
			break;
		}
	}

	/* hardware special operation */
	qe_ep_bd_init(udc, pipe_num);
	if ((ep->tm == USBP_TM_CTL) || (ep->dir == USB_DIR_OUT)) {
		reval = qe_ep_rxbd_update(ep);
		if (reval)
			goto en_done1;
	}

	if ((ep->tm == USBP_TM_CTL) || (ep->dir == USB_DIR_IN)) {
		ep->txframe = kmalloc(sizeof(*ep->txframe), GFP_ATOMIC);
		if (ep->txframe == NULL) {
			dev_err(udc->dev, "malloc txframe failed\n");
			goto en_done2;
		}
		qe_frame_init(ep->txframe);
	}

	qe_ep_register_init(udc, pipe_num);

	/* Now HW will be NAKing transfers to that EP,
	 * until a buffer is queued to it. */
	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
en_done2:
	kfree(ep->rxbuffer);
	kfree(ep->rxframe);
en_done1:
	spin_unlock_irqrestore(&udc->lock, flags);
en_done:
	dev_err(udc->dev, "failed to initialize %s\n", ep->ep.name);
	return -ENODEV;
}