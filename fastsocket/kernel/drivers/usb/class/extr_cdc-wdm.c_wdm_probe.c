#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct wdm_device {int wMaxCommand; struct wdm_device* irq; struct wdm_device* orq; struct wdm_device* ubuf; TYPE_6__* validity; void* sbuf; void* wMaxPacketSize; struct usb_interface* intf; TYPE_5__* response; void* inbuf; void* bMaxPacketSize0; void* command; int /*<<< orphan*/  rxwork; int /*<<< orphan*/  inum; int /*<<< orphan*/  wait; int /*<<< orphan*/  iuspin; int /*<<< orphan*/  plock; int /*<<< orphan*/  rlock; int /*<<< orphan*/  wlock; } ;
struct usb_interface {scalar_t__ minor; int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; TYPE_1__* altsetting; } ;
struct TYPE_8__ {int bNumEndpoints; scalar_t__ bInterfaceNumber; } ;
struct usb_host_interface {TYPE_3__* endpoint; TYPE_2__ desc; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_10__ {void* bMaxPacketSize0; } ;
struct usb_device {TYPE_4__ descriptor; } ;
struct usb_ctrlrequest {int dummy; } ;
struct usb_cdc_dmm_desc {int /*<<< orphan*/  wMaxCommand; } ;
struct TYPE_12__ {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_9__ {struct usb_endpoint_descriptor desc; } ;
struct TYPE_7__ {int* extra; int extralen; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
#define  USB_CDC_DMM_TYPE 129 
#define  USB_CDC_HEADER_TYPE 128 
 int USB_DT_CS_INTERFACE ; 
 scalar_t__ WDM_MINOR_BASE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  free_urbs (struct wdm_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct wdm_device*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct wdm_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* usb_buffer_alloc (struct usb_device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_6__*,struct usb_device*,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,struct wdm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct wdm_device*) ; 
 int /*<<< orphan*/  wdm_class ; 
 int /*<<< orphan*/  wdm_int_callback ; 
 int /*<<< orphan*/  wdm_rxwork ; 

__attribute__((used)) static int wdm_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	int rv = -EINVAL;
	struct usb_device *udev = interface_to_usbdev(intf);
	struct wdm_device *desc;
	struct usb_host_interface *iface;
	struct usb_endpoint_descriptor *ep;
	struct usb_cdc_dmm_desc *dmhd;
	u8 *buffer = intf->altsetting->extra;
	int buflen = intf->altsetting->extralen;
	u16 maxcom = 0;

	if (!buffer)
		goto out;

	while (buflen > 2) {
		if (buffer [1] != USB_DT_CS_INTERFACE) {
			dev_err(&intf->dev, "skipping garbage\n");
			goto next_desc;
		}

		switch (buffer [2]) {
		case USB_CDC_HEADER_TYPE:
			break;
		case USB_CDC_DMM_TYPE:
			dmhd = (struct usb_cdc_dmm_desc *)buffer;
			maxcom = le16_to_cpu(dmhd->wMaxCommand);
			dev_dbg(&intf->dev,
				"Finding maximum buffer length: %d", maxcom);
			break;
		default:
			dev_err(&intf->dev,
				"Ignoring extra header, type %d, length %d\n",
				buffer[2], buffer[0]);
			break;
		}
next_desc:
		buflen -= buffer[0];
		buffer += buffer[0];
	}

	rv = -ENOMEM;
	desc = kzalloc(sizeof(struct wdm_device), GFP_KERNEL);
	if (!desc)
		goto out;
	mutex_init(&desc->wlock);
	mutex_init(&desc->rlock);
	mutex_init(&desc->plock);
	spin_lock_init(&desc->iuspin);
	init_waitqueue_head(&desc->wait);
	desc->wMaxCommand = maxcom;
	/* this will be expanded and needed in hardware endianness */
	desc->inum = cpu_to_le16((u16)intf->cur_altsetting->desc.bInterfaceNumber);
	desc->intf = intf;
	INIT_WORK(&desc->rxwork, wdm_rxwork);

	rv = -EINVAL;
	iface = intf->cur_altsetting;
	if (iface->desc.bNumEndpoints != 1)
		goto err;
	ep = &iface->endpoint[0].desc;
	if (!ep || !usb_endpoint_is_int_in(ep))
		goto err;

	desc->wMaxPacketSize = le16_to_cpu(ep->wMaxPacketSize);
	desc->bMaxPacketSize0 = udev->descriptor.bMaxPacketSize0;

	desc->orq = kmalloc(sizeof(struct usb_ctrlrequest), GFP_KERNEL);
	if (!desc->orq)
		goto err;
	desc->irq = kmalloc(sizeof(struct usb_ctrlrequest), GFP_KERNEL);
	if (!desc->irq)
		goto err;

	desc->validity = usb_alloc_urb(0, GFP_KERNEL);
	if (!desc->validity)
		goto err;

	desc->response = usb_alloc_urb(0, GFP_KERNEL);
	if (!desc->response)
		goto err;

	desc->command = usb_alloc_urb(0, GFP_KERNEL);
	if (!desc->command)
		goto err;

	desc->ubuf = kmalloc(desc->wMaxCommand, GFP_KERNEL);
	if (!desc->ubuf)
		goto err;

	desc->sbuf = usb_buffer_alloc(interface_to_usbdev(intf),
					desc->wMaxPacketSize,
					GFP_KERNEL,
					&desc->validity->transfer_dma);
	if (!desc->sbuf)
		goto err;

	desc->inbuf = usb_buffer_alloc(interface_to_usbdev(intf),
					desc->bMaxPacketSize0,
					GFP_KERNEL,
					&desc->response->transfer_dma);
	if (!desc->inbuf)
		goto err2;

	usb_fill_int_urb(
		desc->validity,
		interface_to_usbdev(intf),
		usb_rcvintpipe(interface_to_usbdev(intf), ep->bEndpointAddress),
		desc->sbuf,
		desc->wMaxPacketSize,
		wdm_int_callback,
		desc,
		ep->bInterval
	);
	desc->validity->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	usb_set_intfdata(intf, desc);
	rv = usb_register_dev(intf, &wdm_class);
	if (rv < 0)
		goto err3;
	else
		dev_info(&intf->dev, "cdc-wdm%d: USB WDM device\n",
			intf->minor - WDM_MINOR_BASE);
out:
	return rv;
err3:
	usb_set_intfdata(intf, NULL);
	usb_buffer_free(interface_to_usbdev(desc->intf),
			desc->bMaxPacketSize0,
			desc->inbuf,
			desc->response->transfer_dma);
err2:
	usb_buffer_free(interface_to_usbdev(desc->intf),
			desc->wMaxPacketSize,
			desc->sbuf,
			desc->validity->transfer_dma);
err:
	free_urbs(desc);
	kfree(desc->ubuf);
	kfree(desc->orq);
	kfree(desc->irq);
	kfree(desc);
	return rv;
}