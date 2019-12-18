#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_line6_variax {int dummy; } ;
struct usb_line6_pod {int dummy; } ;
struct usb_line6 {int message_length; int /*<<< orphan*/  interface_number; int /*<<< orphan*/  ifcdev; TYPE_3__* usbdev; int /*<<< orphan*/  buffer_message; TYPE_1__* line6midi; } ;
struct urb {int actual_length; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  status; scalar_t__ context; } ;
struct MidiBuffer {int dummy; } ;
struct TYPE_5__ {int idProduct; } ;
struct TYPE_6__ {TYPE_2__ descriptor; } ;
struct TYPE_4__ {int /*<<< orphan*/  midi_mask_receive; struct MidiBuffer midibuf_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MESSAGES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
#define  LINE6_DEVID_BASSPODXT 137 
#define  LINE6_DEVID_BASSPODXTLIVE 136 
#define  LINE6_DEVID_BASSPODXTPRO 135 
#define  LINE6_DEVID_POCKETPOD 134 
#define  LINE6_DEVID_PODXT 133 
#define  LINE6_DEVID_PODXTLIVE 132 
#define  LINE6_DEVID_PODXTPRO 131 
#define  LINE6_DEVID_VARIAX 130 
 int /*<<< orphan*/  LINE6_MESSAGE_MAXLEN ; 
 int /*<<< orphan*/  MISSING_CASE ; 
#define  PODXTLIVE_INTERFACE_POD 129 
#define  PODXTLIVE_INTERFACE_VARIAX 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  line6_dump_urb (struct urb*) ; 
 int /*<<< orphan*/  line6_midi_receive (struct usb_line6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  line6_start_listen (struct usb_line6*) ; 
 int /*<<< orphan*/  line6_write_hexdump (struct usb_line6*,char,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  midibuf_ignore (struct MidiBuffer*,int) ; 
 int midibuf_read (struct MidiBuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ midibuf_skip_message (struct MidiBuffer*,int /*<<< orphan*/ ) ; 
 int midibuf_write (struct MidiBuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pod_process_message (struct usb_line6_pod*) ; 
 int /*<<< orphan*/  variax_process_message (struct usb_line6_variax*) ; 

__attribute__((used)) static void line6_data_received(struct urb *urb)
{
	struct usb_line6 *line6 = (struct usb_line6 *)urb->context;
	struct MidiBuffer *mb = &line6->line6midi->midibuf_in;
	int done;

	if (urb->status == -ESHUTDOWN)
		return;

#if DO_DUMP_URB_RECEIVE
	line6_dump_urb(urb);
#endif

	done = midibuf_write(mb, urb->transfer_buffer, urb->actual_length);

	if (done < urb->actual_length) {
		midibuf_ignore(mb, done);
		DEBUG_MESSAGES(dev_err(line6->ifcdev, "%d %d buffer overflow - message skipped\n", done, urb->actual_length));
	}

	for (;;) {
		done = midibuf_read(mb, line6->buffer_message, LINE6_MESSAGE_MAXLEN);

		if (done == 0)
			break;

		/* MIDI input filter */
		if (midibuf_skip_message(mb, line6->line6midi->midi_mask_receive))
			continue;

		line6->message_length = done;
#if DO_DUMP_MIDI_RECEIVE
		line6_write_hexdump(line6, 'r', line6->buffer_message, done);
#endif
		line6_midi_receive(line6, line6->buffer_message, done);

		switch (line6->usbdev->descriptor.idProduct) {
		case LINE6_DEVID_BASSPODXT:
		case LINE6_DEVID_BASSPODXTLIVE:
		case LINE6_DEVID_BASSPODXTPRO:
		case LINE6_DEVID_PODXT:
		case LINE6_DEVID_PODXTPRO:
		case LINE6_DEVID_POCKETPOD:
			pod_process_message((struct usb_line6_pod *)line6);
			break;

		case LINE6_DEVID_PODXTLIVE:
			switch (line6->interface_number) {
			case PODXTLIVE_INTERFACE_POD:
				pod_process_message((struct usb_line6_pod *)line6);
				break;

			case PODXTLIVE_INTERFACE_VARIAX:
				variax_process_message((struct usb_line6_variax *)line6);
				break;

			default:
				dev_err(line6->ifcdev, "PODxt Live interface %d not supported\n", line6->interface_number);
			}
			break;

		case LINE6_DEVID_VARIAX:
			variax_process_message((struct usb_line6_variax *)line6);
			break;

		default:
			MISSING_CASE;
		}
	}

	line6_start_listen(line6);
}