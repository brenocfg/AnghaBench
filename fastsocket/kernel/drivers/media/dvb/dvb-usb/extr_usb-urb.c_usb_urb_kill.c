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
struct usb_data_stream {int urbs_submitted; int /*<<< orphan*/ * urb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  deb_ts (char*,int) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

int usb_urb_kill(struct usb_data_stream *stream)
{
	int i;
	for (i = 0; i < stream->urbs_submitted; i++) {
		deb_ts("killing URB no. %d.\n",i);

		/* stop the URB */
		usb_kill_urb(stream->urb_list[i]);
	}
	stream->urbs_submitted = 0;
	return 0;
}