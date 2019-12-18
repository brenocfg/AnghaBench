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
struct urb {unsigned char* transfer_buffer; int number_of_packets; unsigned int transfer_buffer_length; TYPE_2__* iso_frame_desc; int /*<<< orphan*/  dev; } ;
struct snd_usb_endpoint {int type; unsigned int stride; unsigned char freqn; TYPE_1__* chip; int /*<<< orphan*/  silence_value; int /*<<< orphan*/  data_subs; int /*<<< orphan*/  (* prepare_data_urb ) (int /*<<< orphan*/ ,struct urb*) ;} ;
struct snd_urb_ctx {int packets; int* packet_size; struct urb* urb; } ;
struct TYPE_4__ {unsigned int offset; int length; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SND_USB_ENDPOINT_TYPE_DATA 129 
#define  SND_USB_ENDPOINT_TYPE_SYNC 128 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_usb_get_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct urb*) ; 

__attribute__((used)) static void prepare_outbound_urb(struct snd_usb_endpoint *ep,
				 struct snd_urb_ctx *ctx)
{
	int i;
	struct urb *urb = ctx->urb;
	unsigned char *cp = urb->transfer_buffer;

	urb->dev = ep->chip->dev; /* we need to set this at each time */

	switch (ep->type) {
	case SND_USB_ENDPOINT_TYPE_DATA:
		if (ep->prepare_data_urb) {
			ep->prepare_data_urb(ep->data_subs, urb);
		} else {
			/* no data provider, so send silence */
			unsigned int offs = 0;
			for (i = 0; i < ctx->packets; ++i) {
				int counts = ctx->packet_size[i];
				urb->iso_frame_desc[i].offset = offs * ep->stride;
				urb->iso_frame_desc[i].length = counts * ep->stride;
				offs += counts;
			}

			urb->number_of_packets = ctx->packets;
			urb->transfer_buffer_length = offs * ep->stride;
			memset(urb->transfer_buffer, ep->silence_value,
			       offs * ep->stride);
		}
		break;

	case SND_USB_ENDPOINT_TYPE_SYNC:
		if (snd_usb_get_speed(ep->chip->dev) >= USB_SPEED_HIGH) {
			/*
			 * fill the length and offset of each urb descriptor.
			 * the fixed 12.13 frequency is passed as 16.16 through the pipe.
			 */
			urb->iso_frame_desc[0].length = 4;
			urb->iso_frame_desc[0].offset = 0;
			cp[0] = ep->freqn;
			cp[1] = ep->freqn >> 8;
			cp[2] = ep->freqn >> 16;
			cp[3] = ep->freqn >> 24;
		} else {
			/*
			 * fill the length and offset of each urb descriptor.
			 * the fixed 10.14 frequency is passed through the pipe.
			 */
			urb->iso_frame_desc[0].length = 3;
			urb->iso_frame_desc[0].offset = 0;
			cp[0] = ep->freqn >> 2;
			cp[1] = ep->freqn >> 10;
			cp[2] = ep->freqn >> 18;
		}

		break;
	}
}