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
struct usb_keyspan {int /*<<< orphan*/  in_dma; int /*<<< orphan*/  in_buffer; int /*<<< orphan*/  udev; int /*<<< orphan*/  irq_urb; int /*<<< orphan*/  input; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECV_SIZE ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct usb_keyspan*) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct usb_keyspan* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keyspan_disconnect(struct usb_interface *interface)
{
	struct usb_keyspan *remote;

	remote = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	if (remote) {	/* We have a valid driver structure so clean up everything we allocated. */
		input_unregister_device(remote->input);
		usb_kill_urb(remote->irq_urb);
		usb_free_urb(remote->irq_urb);
		usb_buffer_free(remote->udev, RECV_SIZE, remote->in_buffer, remote->in_dma);
		kfree(remote);
	}
}