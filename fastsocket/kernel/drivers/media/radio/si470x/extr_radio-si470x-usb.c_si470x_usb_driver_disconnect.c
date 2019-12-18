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
struct usb_interface {int dummy; } ;
struct si470x_device {int disconnected; scalar_t__ users; int /*<<< orphan*/  disconnect_lock; struct si470x_device* buffer; int /*<<< orphan*/  videodev; struct si470x_device* int_in_buffer; int /*<<< orphan*/  int_in_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLINK_ORANGE_LED ; 
 int /*<<< orphan*/  kfree (struct si470x_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si470x_set_led_state (struct si470x_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct si470x_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void si470x_usb_driver_disconnect(struct usb_interface *intf)
{
	struct si470x_device *radio = usb_get_intfdata(intf);

	mutex_lock(&radio->disconnect_lock);
	radio->disconnected = 1;
	usb_set_intfdata(intf, NULL);
	if (radio->users == 0) {
		/* set led to disconnect state */
		si470x_set_led_state(radio, BLINK_ORANGE_LED);

		/* Free data structures. */
		usb_free_urb(radio->int_in_urb);

		kfree(radio->int_in_buffer);
		video_unregister_device(radio->videodev);
		kfree(radio->buffer);
		kfree(radio);
	}
	mutex_unlock(&radio->disconnect_lock);
}