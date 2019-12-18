#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct ati_remote {TYPE_3__* interface; TYPE_4__* out_urb; int /*<<< orphan*/  outbuf_dma; TYPE_2__* endpoint_out; int /*<<< orphan*/  outbuf; TYPE_4__* irq_urb; int /*<<< orphan*/  inbuf_dma; TYPE_1__* endpoint_in; int /*<<< orphan*/  inbuf; int /*<<< orphan*/  wait; struct usb_device* udev; } ;
struct TYPE_8__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_5__ {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int DATA_BUFSIZE ; 
 int EIO ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  ati_remote_irq_in ; 
 int /*<<< orphan*/  ati_remote_irq_out ; 
 scalar_t__ ati_remote_sendpacket (struct ati_remote*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init1 ; 
 int /*<<< orphan*/  init2 ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_4__*,struct usb_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ati_remote*,int /*<<< orphan*/ ) ; 
 int usb_maxpacket (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeout (int) ; 
 int usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_sndintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ati_remote_initialize(struct ati_remote *ati_remote)
{
	struct usb_device *udev = ati_remote->udev;
	int pipe, maxp;

	init_waitqueue_head(&ati_remote->wait);

	/* Set up irq_urb */
	pipe = usb_rcvintpipe(udev, ati_remote->endpoint_in->bEndpointAddress);
	maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	maxp = (maxp > DATA_BUFSIZE) ? DATA_BUFSIZE : maxp;

	usb_fill_int_urb(ati_remote->irq_urb, udev, pipe, ati_remote->inbuf,
			 maxp, ati_remote_irq_in, ati_remote,
			 ati_remote->endpoint_in->bInterval);
	ati_remote->irq_urb->transfer_dma = ati_remote->inbuf_dma;
	ati_remote->irq_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/* Set up out_urb */
	pipe = usb_sndintpipe(udev, ati_remote->endpoint_out->bEndpointAddress);
	maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	maxp = (maxp > DATA_BUFSIZE) ? DATA_BUFSIZE : maxp;

	usb_fill_int_urb(ati_remote->out_urb, udev, pipe, ati_remote->outbuf,
			 maxp, ati_remote_irq_out, ati_remote,
			 ati_remote->endpoint_out->bInterval);
	ati_remote->out_urb->transfer_dma = ati_remote->outbuf_dma;
	ati_remote->out_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/* send initialization strings */
	if ((ati_remote_sendpacket(ati_remote, 0x8004, init1)) ||
	    (ati_remote_sendpacket(ati_remote, 0x8007, init2))) {
		dev_err(&ati_remote->interface->dev,
			 "Initializing ati_remote hardware failed.\n");
		return -EIO;
	}

	return 0;
}