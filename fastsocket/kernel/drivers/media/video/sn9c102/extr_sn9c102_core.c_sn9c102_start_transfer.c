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
struct usb_host_interface {TYPE_2__* endpoint; } ;
struct usb_device {int dummy; } ;
struct urb {unsigned int number_of_packets; unsigned int transfer_buffer_length; int interval; TYPE_3__* iso_frame_desc; scalar_t__ transfer_buffer; int /*<<< orphan*/  complete; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  pipe; struct sn9c102_device* context; struct usb_device* dev; } ;
struct TYPE_8__ {scalar_t__ bytesread; } ;
struct sn9c102_device {int* reg; scalar_t__* transfer_buffer; struct urb** urb; TYPE_4__ sof; int /*<<< orphan*/ * frame_current; struct usb_device* usbdev; } ;
typedef  size_t s8 ;
struct TYPE_7__ {unsigned int offset; unsigned int length; } ;
struct TYPE_5__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,...) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SN9C102_ALTERNATE_SETTING ; 
 unsigned int const SN9C102_ISO_PACKETS ; 
 size_t SN9C102_URBS ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ kzalloc (unsigned int const,int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn9c102_urb_complete ; 
 int sn9c102_write_reg (struct sn9c102_device*,int,int) ; 
 struct urb* usb_alloc_urb (unsigned int const,int /*<<< orphan*/ ) ; 
 struct usb_host_interface* usb_altnum_to_altsetting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_ifnum_to_if (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (struct usb_device*,int) ; 
 int usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sn9c102_start_transfer(struct sn9c102_device* cam)
{
	struct usb_device *udev = cam->usbdev;
	struct urb* urb;
	struct usb_host_interface* altsetting = usb_altnum_to_altsetting(
						    usb_ifnum_to_if(udev, 0),
						    SN9C102_ALTERNATE_SETTING);
	const unsigned int psz = le16_to_cpu(altsetting->
					     endpoint[0].desc.wMaxPacketSize);
	s8 i, j;
	int err = 0;

	for (i = 0; i < SN9C102_URBS; i++) {
		cam->transfer_buffer[i] = kzalloc(SN9C102_ISO_PACKETS * psz,
						  GFP_KERNEL);
		if (!cam->transfer_buffer[i]) {
			err = -ENOMEM;
			DBG(1, "Not enough memory");
			goto free_buffers;
		}
	}

	for (i = 0; i < SN9C102_URBS; i++) {
		urb = usb_alloc_urb(SN9C102_ISO_PACKETS, GFP_KERNEL);
		cam->urb[i] = urb;
		if (!urb) {
			err = -ENOMEM;
			DBG(1, "usb_alloc_urb() failed");
			goto free_urbs;
		}
		urb->dev = udev;
		urb->context = cam;
		urb->pipe = usb_rcvisocpipe(udev, 1);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->number_of_packets = SN9C102_ISO_PACKETS;
		urb->complete = sn9c102_urb_complete;
		urb->transfer_buffer = cam->transfer_buffer[i];
		urb->transfer_buffer_length = psz * SN9C102_ISO_PACKETS;
		urb->interval = 1;
		for (j = 0; j < SN9C102_ISO_PACKETS; j++) {
			urb->iso_frame_desc[j].offset = psz * j;
			urb->iso_frame_desc[j].length = psz;
		}
	}

	/* Enable video */
	if (!(cam->reg[0x01] & 0x04)) {
		err = sn9c102_write_reg(cam, cam->reg[0x01] | 0x04, 0x01);
		if (err) {
			err = -EIO;
			DBG(1, "I/O hardware error");
			goto free_urbs;
		}
	}

	err = usb_set_interface(udev, 0, SN9C102_ALTERNATE_SETTING);
	if (err) {
		DBG(1, "usb_set_interface() failed");
		goto free_urbs;
	}

	cam->frame_current = NULL;
	cam->sof.bytesread = 0;

	for (i = 0; i < SN9C102_URBS; i++) {
		err = usb_submit_urb(cam->urb[i], GFP_KERNEL);
		if (err) {
			for (j = i-1; j >= 0; j--)
				usb_kill_urb(cam->urb[j]);
			DBG(1, "usb_submit_urb() failed, error %d", err);
			goto free_urbs;
		}
	}

	return 0;

free_urbs:
	for (i = 0; (i < SN9C102_URBS) && cam->urb[i]; i++)
		usb_free_urb(cam->urb[i]);

free_buffers:
	for (i = 0; (i < SN9C102_URBS) && cam->transfer_buffer[i]; i++)
		kfree(cam->transfer_buffer[i]);

	return err;
}