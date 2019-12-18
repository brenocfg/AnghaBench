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
struct uvc_streaming {struct urb** urb; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 unsigned int UVC_URBS ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  uvc_free_urb_buffers (struct uvc_streaming*) ; 

__attribute__((used)) static void uvc_uninit_video(struct uvc_streaming *stream, int free_buffers)
{
	struct urb *urb;
	unsigned int i;

	for (i = 0; i < UVC_URBS; ++i) {
		urb = stream->urb[i];
		if (urb == NULL)
			continue;

		usb_kill_urb(urb);
		usb_free_urb(urb);
		stream->urb[i] = NULL;
	}

	if (free_buffers)
		uvc_free_urb_buffers(stream);
}