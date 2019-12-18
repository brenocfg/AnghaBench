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
struct usb_stream_kernel {TYPE_1__* s; int /*<<< orphan*/ * outurb; int /*<<< orphan*/ * inurb; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int USB_STREAM_NURBS ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stream_stopped ; 

void usb_stream_stop(struct usb_stream_kernel *sk)
{
	int u;
	if (!sk->s)
		return;
	for (u = 0; u < USB_STREAM_NURBS; ++u) {
		usb_kill_urb(sk->inurb[u]);
		usb_kill_urb(sk->outurb[u]);
	}
	sk->s->state = usb_stream_stopped;
	msleep(400);
}