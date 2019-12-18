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
struct usb_line6 {int /*<<< orphan*/  ifcdev; int /*<<< orphan*/  ep_control_write; int /*<<< orphan*/  usbdev; scalar_t__ max_packet_size; } ;

/* Variables and functions */
 int HZ ; 
 int LINE6_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  line6_write_hexdump (struct usb_line6*,char,char const*,int) ; 
 int min (scalar_t__,int) ; 
 int usb_interrupt_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int line6_send_raw_message(struct usb_line6 *line6, const char *buffer,
			   int size)
{
	int i, done = 0;

#if DO_DUMP_URB_SEND
	line6_write_hexdump(line6, 'S', buffer, size);
#endif

	for (i = 0; i < size; i += line6->max_packet_size) {
		int partial;
		const char *frag_buf = buffer + i;
		int frag_size = min(line6->max_packet_size, size - i);
		int retval;

		retval = usb_interrupt_msg(line6->usbdev,
					   usb_sndintpipe(line6->usbdev,
							  line6->ep_control_write),
					   (char *)frag_buf, frag_size,
					   &partial, LINE6_TIMEOUT * HZ);

		if (retval) {
			dev_err(line6->ifcdev,
				"usb_interrupt_msg failed (%d)\n", retval);
			break;
		}

		done += frag_size;
	}

	return done;
}