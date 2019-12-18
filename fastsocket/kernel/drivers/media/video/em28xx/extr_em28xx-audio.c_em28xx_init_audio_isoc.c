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
struct urb {int interval; int number_of_packets; int transfer_buffer_length; TYPE_1__* iso_frame_desc; int /*<<< orphan*/  complete; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  pipe; struct em28xx* context; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct urb** urb; int /*<<< orphan*/ * transfer_buffer; } ;
struct em28xx {TYPE_2__ adev; int /*<<< orphan*/  udev; } ;
struct TYPE_3__ {int offset; int length; } ;

/* Variables and functions */
 int EM28XX_AUDIO_BUFS ; 
 int EM28XX_AUDIO_MAX_PACKET_SIZE ; 
 int EM28XX_NUM_AUDIO_PACKETS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  em28xx_audio_isocirq ; 
 int /*<<< orphan*/  em28xx_deinit_isoc_audio (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_errdev (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int const) ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em28xx_init_audio_isoc(struct em28xx *dev)
{
	int       i, errCode;
	const int sb_size = EM28XX_NUM_AUDIO_PACKETS *
			    EM28XX_AUDIO_MAX_PACKET_SIZE;

	dprintk("Starting isoc transfers\n");

	for (i = 0; i < EM28XX_AUDIO_BUFS; i++) {
		struct urb *urb;
		int j, k;

		dev->adev.transfer_buffer[i] = kmalloc(sb_size, GFP_ATOMIC);
		if (!dev->adev.transfer_buffer[i])
			return -ENOMEM;

		memset(dev->adev.transfer_buffer[i], 0x80, sb_size);
		urb = usb_alloc_urb(EM28XX_NUM_AUDIO_PACKETS, GFP_ATOMIC);
		if (!urb) {
			em28xx_errdev("usb_alloc_urb failed!\n");
			for (j = 0; j < i; j++) {
				usb_free_urb(dev->adev.urb[j]);
				kfree(dev->adev.transfer_buffer[j]);
			}
			return -ENOMEM;
		}

		urb->dev = dev->udev;
		urb->context = dev;
		urb->pipe = usb_rcvisocpipe(dev->udev, 0x83);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = dev->adev.transfer_buffer[i];
		urb->interval = 1;
		urb->complete = em28xx_audio_isocirq;
		urb->number_of_packets = EM28XX_NUM_AUDIO_PACKETS;
		urb->transfer_buffer_length = sb_size;

		for (j = k = 0; j < EM28XX_NUM_AUDIO_PACKETS;
			     j++, k += EM28XX_AUDIO_MAX_PACKET_SIZE) {
			urb->iso_frame_desc[j].offset = k;
			urb->iso_frame_desc[j].length =
			    EM28XX_AUDIO_MAX_PACKET_SIZE;
		}
		dev->adev.urb[i] = urb;
	}

	for (i = 0; i < EM28XX_AUDIO_BUFS; i++) {
		errCode = usb_submit_urb(dev->adev.urb[i], GFP_ATOMIC);
		if (errCode) {
			em28xx_deinit_isoc_audio(dev);
			return errCode;
		}
	}

	return 0;
}