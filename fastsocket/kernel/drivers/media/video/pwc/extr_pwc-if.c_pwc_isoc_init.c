#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct TYPE_6__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_3__* endpoint; TYPE_1__ desc; } ;
struct usb_device {int /*<<< orphan*/  actconfig; } ;
struct urb {int interval; int number_of_packets; TYPE_4__* iso_frame_desc; scalar_t__ start_frame; struct pwc_device* context; int /*<<< orphan*/  complete; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  pipe; struct usb_device* dev; } ;
struct pwc_device {int iso_init; int vmax_packet_size; int vendpoint; TYPE_5__* sbuf; int /*<<< orphan*/  valternate; struct usb_device* udev; scalar_t__ vsync; } ;
struct TYPE_10__ {struct urb* urb; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int offset; int length; } ;
struct TYPE_7__ {int bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_8__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENFILE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISO_BUFFER_SIZE ; 
 int ISO_FRAMES_PER_DESC ; 
 int ISO_MAX_FRAME_SIZE ; 
 int MAX_ISO_BUFS ; 
 int /*<<< orphan*/  PWC_DEBUG_MEMORY (char*,struct urb*) ; 
 int /*<<< orphan*/  PWC_DEBUG_OPEN (char*,...) ; 
 int /*<<< orphan*/  PWC_ERROR (char*,...) ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwc_isoc_cleanup (struct pwc_device*) ; 
 int /*<<< orphan*/  pwc_isoc_handler ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (struct usb_device*,int) ; 
 int usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

int pwc_isoc_init(struct pwc_device *pdev)
{
	struct usb_device *udev;
	struct urb *urb;
	int i, j, ret;

	struct usb_interface *intf;
	struct usb_host_interface *idesc = NULL;

	if (pdev == NULL)
		return -EFAULT;
	if (pdev->iso_init)
		return 0;
	pdev->vsync = 0;
	udev = pdev->udev;

	/* Get the current alternate interface, adjust packet size */
	if (!udev->actconfig)
		return -EFAULT;
	intf = usb_ifnum_to_if(udev, 0);
	if (intf)
		idesc = usb_altnum_to_altsetting(intf, pdev->valternate);

	if (!idesc)
		return -EFAULT;

	/* Search video endpoint */
	pdev->vmax_packet_size = -1;
	for (i = 0; i < idesc->desc.bNumEndpoints; i++) {
		if ((idesc->endpoint[i].desc.bEndpointAddress & 0xF) == pdev->vendpoint) {
			pdev->vmax_packet_size = le16_to_cpu(idesc->endpoint[i].desc.wMaxPacketSize);
			break;
		}
	}

	if (pdev->vmax_packet_size < 0 || pdev->vmax_packet_size > ISO_MAX_FRAME_SIZE) {
		PWC_ERROR("Failed to find packet size for video endpoint in current alternate setting.\n");
		return -ENFILE; /* Odd error, that should be noticeable */
	}

	/* Set alternate interface */
	ret = 0;
	PWC_DEBUG_OPEN("Setting alternate interface %d\n", pdev->valternate);
	ret = usb_set_interface(pdev->udev, 0, pdev->valternate);
	if (ret < 0)
		return ret;

	for (i = 0; i < MAX_ISO_BUFS; i++) {
		urb = usb_alloc_urb(ISO_FRAMES_PER_DESC, GFP_KERNEL);
		if (urb == NULL) {
			PWC_ERROR("Failed to allocate urb %d\n", i);
			ret = -ENOMEM;
			break;
		}
		pdev->sbuf[i].urb = urb;
		PWC_DEBUG_MEMORY("Allocated URB at 0x%p\n", urb);
	}
	if (ret) {
		/* De-allocate in reverse order */
		while (i--) {
			usb_free_urb(pdev->sbuf[i].urb);
			pdev->sbuf[i].urb = NULL;
		}
		return ret;
	}

	/* init URB structure */
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		urb = pdev->sbuf[i].urb;

		urb->interval = 1; // devik
		urb->dev = udev;
		urb->pipe = usb_rcvisocpipe(udev, pdev->vendpoint);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = pdev->sbuf[i].data;
		urb->transfer_buffer_length = ISO_BUFFER_SIZE;
		urb->complete = pwc_isoc_handler;
		urb->context = pdev;
		urb->start_frame = 0;
		urb->number_of_packets = ISO_FRAMES_PER_DESC;
		for (j = 0; j < ISO_FRAMES_PER_DESC; j++) {
			urb->iso_frame_desc[j].offset = j * ISO_MAX_FRAME_SIZE;
			urb->iso_frame_desc[j].length = pdev->vmax_packet_size;
		}
	}

	/* link */
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		ret = usb_submit_urb(pdev->sbuf[i].urb, GFP_KERNEL);
		if (ret) {
			PWC_ERROR("isoc_init() submit_urb %d failed with error %d\n", i, ret);
			pdev->iso_init = 1;
			pwc_isoc_cleanup(pdev);
			return ret;
		}
		PWC_DEBUG_MEMORY("URB 0x%p submitted.\n", pdev->sbuf[i].urb);
	}

	/* All is done... */
	pdev->iso_init = 1;
	PWC_DEBUG_OPEN("<< pwc_isoc_init()\n");
	return 0;
}