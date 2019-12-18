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
struct urb {scalar_t__ actual_length; int number_of_packets; TYPE_1__* iso_frame_desc; scalar_t__ transfer_buffer; int /*<<< orphan*/  transfer_buffer_length; struct flexcop_usb* context; } ;
struct flexcop_usb {int dummy; } ;
struct TYPE_2__ {scalar_t__ status; scalar_t__ actual_length; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  deb_ts (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  err (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  flexcop_usb_process_frame (struct flexcop_usb*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flexcop_usb_urb_complete(struct urb *urb)
{
	struct flexcop_usb *fc_usb = urb->context;
	int i;

	if (urb->actual_length > 0)
		deb_ts("urb completed, bufsize: %d actlen; %d\n",
			urb->transfer_buffer_length, urb->actual_length);

	for (i = 0; i < urb->number_of_packets; i++) {
		if (urb->iso_frame_desc[i].status < 0) {
			err("iso frame descriptor %d has an error: %d\n", i,
				urb->iso_frame_desc[i].status);
		} else
			if (urb->iso_frame_desc[i].actual_length > 0) {
				deb_ts("passed %d bytes to the demux\n",
					urb->iso_frame_desc[i].actual_length);

				flexcop_usb_process_frame(fc_usb,
					urb->transfer_buffer +
						urb->iso_frame_desc[i].offset,
					urb->iso_frame_desc[i].actual_length);
			}
		urb->iso_frame_desc[i].status = 0;
		urb->iso_frame_desc[i].actual_length = 0;
	}
	usb_submit_urb(urb,GFP_ATOMIC);
}