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
struct usb_iso_packet_descriptor {int offset; int length; } ;
struct usb_device {int dummy; } ;
struct urb {unsigned int pipe; int transfer_buffer_length; int interval; int number_of_packets; int /*<<< orphan*/  complete; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/ * context; struct usb_device* dev; struct usb_iso_packet_descriptor* iso_frame_desc; void* transfer_buffer; } ;
struct TYPE_2__ {struct usb_device* dev; } ;
struct snd_usb_caiaqdev {int /*<<< orphan*/ * data_cb_info; TYPE_1__ chip; } ;

/* Variables and functions */
 int BYTES_PER_FRAME ; 
 int /*<<< orphan*/  ENDPOINT_CAPTURE ; 
 int /*<<< orphan*/  ENDPOINT_PLAYBACK ; 
 int ENOMEM ; 
 int FRAMES_PER_URB ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int N_URBS ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (char*) ; 
 int /*<<< orphan*/  read_completed ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 
 unsigned int usb_rcvisocpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndisocpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_completed ; 

__attribute__((used)) static struct urb **alloc_urbs(struct snd_usb_caiaqdev *dev, int dir, int *ret)
{
	int i, frame;
	struct urb **urbs;
	struct usb_device *usb_dev = dev->chip.dev;
	unsigned int pipe;

	pipe = (dir == SNDRV_PCM_STREAM_PLAYBACK) ?
		usb_sndisocpipe(usb_dev, ENDPOINT_PLAYBACK) :
		usb_rcvisocpipe(usb_dev, ENDPOINT_CAPTURE);

	urbs = kmalloc(N_URBS * sizeof(*urbs), GFP_KERNEL);
	if (!urbs) {
		log("unable to kmalloc() urbs, OOM!?\n");
		*ret = -ENOMEM;
		return NULL;
	}

	for (i = 0; i < N_URBS; i++) {
		urbs[i] = usb_alloc_urb(FRAMES_PER_URB, GFP_KERNEL);
		if (!urbs[i]) {
			log("unable to usb_alloc_urb(), OOM!?\n");
			*ret = -ENOMEM;
			return urbs;
		}

		urbs[i]->transfer_buffer =
			kmalloc(FRAMES_PER_URB * BYTES_PER_FRAME, GFP_KERNEL);
		if (!urbs[i]->transfer_buffer) {
			log("unable to kmalloc() transfer buffer, OOM!?\n");
			*ret = -ENOMEM;
			return urbs;
		}

		for (frame = 0; frame < FRAMES_PER_URB; frame++) {
			struct usb_iso_packet_descriptor *iso =
				&urbs[i]->iso_frame_desc[frame];

			iso->offset = BYTES_PER_FRAME * frame;
			iso->length = BYTES_PER_FRAME;
		}

		urbs[i]->dev = usb_dev;
		urbs[i]->pipe = pipe;
		urbs[i]->transfer_buffer_length = FRAMES_PER_URB
						* BYTES_PER_FRAME;
		urbs[i]->context = &dev->data_cb_info[i];
		urbs[i]->interval = 1;
		urbs[i]->transfer_flags = URB_ISO_ASAP;
		urbs[i]->number_of_packets = FRAMES_PER_URB;
		urbs[i]->complete = (dir == SNDRV_PCM_STREAM_CAPTURE) ?
					read_completed : write_completed;
	}

	*ret = 0;
	return urbs;
}