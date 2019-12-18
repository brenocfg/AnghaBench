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
struct usb_line6 {int /*<<< orphan*/  urb_listen; struct usb_line6* buffer_listen; struct usb_line6* buffer_message; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_line6*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct usb_line6* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void line6_destruct(struct usb_interface *interface)
{
	struct usb_line6 *line6;

	if (interface == NULL)
		return;
	line6 = usb_get_intfdata(interface);
	if (line6 == NULL)
		return;

	/* free buffer memory first: */
	kfree(line6->buffer_message);
	kfree(line6->buffer_listen);

	/* then free URBs: */
	usb_free_urb(line6->urb_listen);

	/* make sure the device isn't destructed twice: */
	usb_set_intfdata(interface, NULL);

	/* free interface data: */
	kfree(line6);
}