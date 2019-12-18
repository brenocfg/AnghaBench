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
struct usb_interface {int dummy; } ;
struct camera_data {scalar_t__ open_count; int /*<<< orphan*/  wq_stream; TYPE_1__* curbuff; scalar_t__ buffers; scalar_t__ present; } ;
struct TYPE_2__ {scalar_t__ length; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  FRAME_READY ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  cpia2_driver ; 
 int /*<<< orphan*/  cpia2_unregister_camera (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_usb_stream_stop (struct camera_data*) ; 
 int /*<<< orphan*/  kfree (struct camera_data*) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,struct usb_interface*) ; 
 struct camera_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpia2_usb_disconnect(struct usb_interface *intf)
{
	struct camera_data *cam = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NULL);
	cam->present = 0;

	DBG("Stopping stream\n");
	cpia2_usb_stream_stop(cam);

	DBG("Unregistering camera\n");
	cpia2_unregister_camera(cam);

	if(cam->buffers) {
		DBG("Wakeup waiting processes\n");
		cam->curbuff->status = FRAME_READY;
		cam->curbuff->length = 0;
		if (waitqueue_active(&cam->wq_stream))
			wake_up_interruptible(&cam->wq_stream);
	}

	DBG("Releasing interface\n");
	usb_driver_release_interface(&cpia2_driver, intf);

	if (cam->open_count == 0) {
		DBG("Freeing camera structure\n");
		kfree(cam);
	}

	LOG("CPiA2 camera disconnected.\n");
}