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
struct input_dev {int dummy; } ;
struct gspca_dev {int /*<<< orphan*/  vdev; int /*<<< orphan*/  usb_lock; int /*<<< orphan*/ * dev; struct input_dev* input_dev; int /*<<< orphan*/  wq; scalar_t__ present; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_urbs (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_input_destroy_urb (struct gspca_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gspca_dev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void gspca_disconnect(struct usb_interface *intf)
{
	struct gspca_dev *gspca_dev = usb_get_intfdata(intf);
#if defined(CONFIG_INPUT) || defined(CONFIG_INPUT_MODULE)
	struct input_dev *input_dev;
#endif

	PDEBUG(D_PROBE, "%s disconnect",
		video_device_node_name(&gspca_dev->vdev));
	mutex_lock(&gspca_dev->usb_lock);

	gspca_dev->present = 0;
	wake_up_interruptible(&gspca_dev->wq);

	destroy_urbs(gspca_dev);

#if defined(CONFIG_INPUT) || defined(CONFIG_INPUT_MODULE)
	gspca_input_destroy_urb(gspca_dev);
	input_dev = gspca_dev->input_dev;
	if (input_dev) {
		gspca_dev->input_dev = NULL;
		input_unregister_device(input_dev);
	}
#endif

	/* the device is freed at exit of this function */
	gspca_dev->dev = NULL;
	mutex_unlock(&gspca_dev->usb_lock);

	usb_set_intfdata(intf, NULL);

	/* release the device */
	/* (this will call gspca_release() immediatly or on last close) */
	video_unregister_device(&gspca_dev->vdev);

/*	PDEBUG(D_PROBE, "disconnect complete"); */
}