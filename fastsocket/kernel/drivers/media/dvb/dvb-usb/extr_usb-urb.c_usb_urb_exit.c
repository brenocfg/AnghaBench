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
struct usb_data_stream {int urbs_initialized; int /*<<< orphan*/ ** urb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  deb_mem (char*,int) ; 
 int /*<<< orphan*/  usb_free_stream_buffers (struct usb_data_stream*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_urb_kill (struct usb_data_stream*) ; 

int usb_urb_exit(struct usb_data_stream *stream)
{
	int i;

	usb_urb_kill(stream);

	for (i = 0; i < stream->urbs_initialized; i++) {
		if (stream->urb_list[i] != NULL) {
			deb_mem("freeing URB no. %d.\n",i);
			/* free the URBs */
			usb_free_urb(stream->urb_list[i]);
		}
	}
	stream->urbs_initialized = 0;

	usb_free_stream_buffers(stream);
	return 0;
}