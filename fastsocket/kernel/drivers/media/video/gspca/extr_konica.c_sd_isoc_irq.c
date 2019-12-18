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
typedef  scalar_t__ u8 ;
struct urb {int status; int transfer_buffer_length; scalar_t__ start_frame; int number_of_packets; TYPE_1__* iso_frame_desc; scalar_t__ transfer_buffer; scalar_t__ context; } ;
struct sd {scalar_t__ snapshot_pressed; struct urb* last_data_urb; } ;
struct gspca_dev {int /*<<< orphan*/  input_dev; void* last_packet_type; scalar_t__ frozen; int /*<<< orphan*/  streaming; } ;
struct TYPE_2__ {int actual_length; int offset; scalar_t__ status; } ;

/* Variables and functions */
 void* DISCARD_PACKET ; 
 int D_ERR ; 
 int D_PACK ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  KEY_CAMERA ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_isoc_irq(struct urb *urb)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *) urb->context;
	struct sd *sd = (struct sd *) gspca_dev;
	struct urb *data_urb, *status_urb;
	u8 *data;
	int i, st;

	PDEBUG(D_PACK, "sd isoc irq");
	if (!gspca_dev->streaming)
		return;

	if (urb->status != 0) {
		if (urb->status == -ESHUTDOWN)
			return;		/* disconnection */
#ifdef CONFIG_PM
		if (gspca_dev->frozen)
			return;
#endif
		PDEBUG(D_ERR, "urb status: %d", urb->status);
		st = usb_submit_urb(urb, GFP_ATOMIC);
		if (st < 0)
			err("resubmit urb error %d", st);
		return;
	}

	/* if this is a data URB (ep 0x82), wait */
	if (urb->transfer_buffer_length > 32) {
		sd->last_data_urb = urb;
		return;
	}

	status_urb = urb;
	data_urb   = sd->last_data_urb;
	sd->last_data_urb = NULL;

	if (!data_urb || data_urb->start_frame != status_urb->start_frame) {
		PDEBUG(D_ERR|D_PACK, "lost sync on frames");
		goto resubmit;
	}

	if (data_urb->number_of_packets != status_urb->number_of_packets) {
		PDEBUG(D_ERR|D_PACK,
		       "no packets does not match, data: %d, status: %d",
		       data_urb->number_of_packets,
		       status_urb->number_of_packets);
		goto resubmit;
	}

	for (i = 0; i < status_urb->number_of_packets; i++) {
		if (data_urb->iso_frame_desc[i].status ||
		    status_urb->iso_frame_desc[i].status) {
			PDEBUG(D_ERR|D_PACK,
			       "pkt %d data-status %d, status-status %d", i,
			       data_urb->iso_frame_desc[i].status,
			       status_urb->iso_frame_desc[i].status);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			continue;
		}

		if (status_urb->iso_frame_desc[i].actual_length != 1) {
			PDEBUG(D_ERR|D_PACK,
			       "bad status packet length %d",
			       status_urb->iso_frame_desc[i].actual_length);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			continue;
		}

		st = *((u8 *)status_urb->transfer_buffer
				+ status_urb->iso_frame_desc[i].offset);

		data = (u8 *)data_urb->transfer_buffer
				+ data_urb->iso_frame_desc[i].offset;

		/* st: 0x80-0xff: frame start with frame number (ie 0-7f)
		 * otherwise:
		 * bit 0 0: keep packet
		 *	 1: drop packet (padding data)
		 *
		 * bit 4 0 button not clicked
		 *       1 button clicked
		 * button is used to `take a picture' (in software)
		 */
		if (st & 0x80) {
			gspca_frame_add(gspca_dev, LAST_PACKET, NULL, 0);
			gspca_frame_add(gspca_dev, FIRST_PACKET, NULL, 0);
		} else {
#if defined(CONFIG_INPUT) || defined(CONFIG_INPUT_MODULE)
			u8 button_state = st & 0x40 ? 1 : 0;
			if (sd->snapshot_pressed != button_state) {
				input_report_key(gspca_dev->input_dev,
						 KEY_CAMERA,
						 button_state);
				input_sync(gspca_dev->input_dev);
				sd->snapshot_pressed = button_state;
			}
#endif
			if (st & 0x01)
				continue;
		}
		gspca_frame_add(gspca_dev, INTER_PACKET, data,
				data_urb->iso_frame_desc[i].actual_length);
	}

resubmit:
	if (data_urb) {
		st = usb_submit_urb(data_urb, GFP_ATOMIC);
		if (st < 0)
			PDEBUG(D_ERR|D_PACK,
			       "usb_submit_urb(data_urb) ret %d", st);
	}
	st = usb_submit_urb(status_urb, GFP_ATOMIC);
	if (st < 0)
		err("usb_submit_urb(status_urb) ret %d", st);
}