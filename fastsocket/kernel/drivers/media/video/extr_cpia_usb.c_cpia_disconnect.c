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
struct usb_device {int dummy; } ;
struct usb_cpia {int /*<<< orphan*/ ** buffers; int /*<<< orphan*/ * workbuff; TYPE_1__* curbuff; int /*<<< orphan*/  wq_stream; scalar_t__ open; scalar_t__ present; } ;
struct cam_data {int /*<<< orphan*/ * lowlevel_data; int /*<<< orphan*/  cam_data_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_ERROR ; 
 int /*<<< orphan*/  cam_list_lock_usb ; 
 int /*<<< orphan*/  cpia_unregister_camera (struct cam_data*) ; 
 int /*<<< orphan*/  cpia_usb_close (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct usb_cpia*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct cam_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpia_disconnect(struct usb_interface *intf)
{
	struct cam_data *cam = usb_get_intfdata(intf);
	struct usb_cpia *ucpia;
	struct usb_device *udev;

	usb_set_intfdata(intf, NULL);
	if (!cam)
		return;

	ucpia = (struct usb_cpia *) cam->lowlevel_data;
	spin_lock( &cam_list_lock_usb );
	list_del(&cam->cam_data_list);
	spin_unlock( &cam_list_lock_usb );

	ucpia->present = 0;

	cpia_unregister_camera(cam);
	if(ucpia->open)
		cpia_usb_close(cam->lowlevel_data);

	ucpia->curbuff->status = FRAME_ERROR;

	if (waitqueue_active(&ucpia->wq_stream))
		wake_up_interruptible(&ucpia->wq_stream);

	udev = interface_to_usbdev(intf);

	ucpia->curbuff = ucpia->workbuff = NULL;

	vfree(ucpia->buffers[2]);
	ucpia->buffers[2] = NULL;

	vfree(ucpia->buffers[1]);
	ucpia->buffers[1] = NULL;

	vfree(ucpia->buffers[0]);
	ucpia->buffers[0] = NULL;

	cam->lowlevel_data = NULL;
	kfree(ucpia);
}