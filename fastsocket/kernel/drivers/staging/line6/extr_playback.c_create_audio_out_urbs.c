#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct urb {int start_frame; int /*<<< orphan*/  complete; scalar_t__ error_count; int /*<<< orphan*/  interval; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; } ;
struct snd_line6_pcm {int ep_audio_write; TYPE_1__* line6; struct urb** urb_audio_out; } ;
struct TYPE_2__ {int /*<<< orphan*/  usbdev; int /*<<< orphan*/  ifcdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LINE6_ISO_BUFFERS ; 
 int /*<<< orphan*/  LINE6_ISO_INTERVAL ; 
 int /*<<< orphan*/  LINE6_ISO_PACKETS ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int /*<<< orphan*/  audio_out_callback ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndisocpipe (int /*<<< orphan*/ ,int) ; 

int create_audio_out_urbs(struct snd_line6_pcm *line6pcm)
{
	int i;

	/* create audio URBs and fill in constant values: */
	for (i = 0; i < LINE6_ISO_BUFFERS; ++i) {
		struct urb *urb;

		/* URB for audio out: */
		urb = line6pcm->urb_audio_out[i] = usb_alloc_urb(LINE6_ISO_PACKETS, GFP_KERNEL);

		if (urb == NULL) {
			dev_err(line6pcm->line6->ifcdev, "Out of memory\n");
			return -ENOMEM;
		}

		urb->dev = line6pcm->line6->usbdev;
		urb->pipe = usb_sndisocpipe(line6pcm->line6->usbdev, line6pcm->ep_audio_write & USB_ENDPOINT_NUMBER_MASK);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->start_frame = -1;
		urb->number_of_packets = LINE6_ISO_PACKETS;
		urb->interval = LINE6_ISO_INTERVAL;
		urb->error_count = 0;
		urb->complete = audio_out_callback;
	}

	return 0;
}