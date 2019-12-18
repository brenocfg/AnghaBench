#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_stream_kernel {int n_o_ps; } ;
struct usb_iso_packet_descriptor {int length; scalar_t__ offset; } ;
struct usb_device {int dummy; } ;
struct urb {char* transfer_buffer; int pipe; int number_of_packets; int interval; int transfer_buffer_length; struct usb_iso_packet_descriptor* iso_frame_desc; struct usb_stream_kernel* context; struct usb_device* dev; int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int USB_STREAM_NURBS ; 
 unsigned int usb_maxpacket (struct usb_device*,int,scalar_t__) ; 
 scalar_t__ usb_pipeout (int) ; 

__attribute__((used)) static void init_pipe_urbs(struct usb_stream_kernel *sk, unsigned use_packsize,
			   struct urb **urbs, char *transfer,
			   struct usb_device *dev, int pipe)
{
	int u, p;
	int maxpacket = use_packsize ?
		use_packsize : usb_maxpacket(dev, pipe, usb_pipeout(pipe));
	int transfer_length = maxpacket * sk->n_o_ps;

	for (u = 0; u < USB_STREAM_NURBS;
	     ++u, transfer += transfer_length) {
		struct urb *urb = urbs[u];
		struct usb_iso_packet_descriptor *desc;
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = transfer;
		urb->dev = dev;
		urb->pipe = pipe;
		urb->number_of_packets = sk->n_o_ps;
		urb->context = sk;
		urb->interval = 1;
		if (usb_pipeout(pipe))
			continue;

		urb->transfer_buffer_length = transfer_length;
		desc = urb->iso_frame_desc;
		desc->offset = 0;
		desc->length = maxpacket;
		for (p = 1; p < sk->n_o_ps; ++p) {
			desc[p].offset = desc[p - 1].offset + maxpacket;
			desc[p].length = maxpacket;
		}
	}
}