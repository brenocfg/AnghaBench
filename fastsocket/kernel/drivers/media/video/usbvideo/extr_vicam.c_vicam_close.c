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
struct vicam_camera {int open_count; int /*<<< orphan*/  cam_lock; struct usb_device* udev; struct vicam_camera* cntrlbuf; int /*<<< orphan*/  framebuf; struct vicam_camera* raw_image; } ;
struct usb_device {int dummy; } ;
struct file {struct vicam_camera* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int VICAM_FRAMES ; 
 int VICAM_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  kfree (struct vicam_camera*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvfree (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_camera_power (struct vicam_camera*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vicam_close(struct file *file)
{
	struct vicam_camera *cam = file->private_data;
	int open_count;
	struct usb_device *udev;

	DBG("close\n");

	/* it's not the end of the world if
	 * we fail to turn the camera off.
	 */

	set_camera_power(cam, 0);

	kfree(cam->raw_image);
	rvfree(cam->framebuf, VICAM_MAX_FRAME_SIZE * VICAM_FRAMES);
	kfree(cam->cntrlbuf);

	mutex_lock(&cam->cam_lock);

	cam->open_count--;
	open_count = cam->open_count;
	udev = cam->udev;

	mutex_unlock(&cam->cam_lock);

	if (!open_count && !udev) {
		kfree(cam);
	}

	return 0;
}