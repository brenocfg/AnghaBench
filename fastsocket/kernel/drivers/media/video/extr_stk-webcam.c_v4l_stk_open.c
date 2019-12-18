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
struct video_device {int dummy; } ;
struct stk_camera {int /*<<< orphan*/  interface; } ;
struct file {struct stk_camera* private_data; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  is_present (struct stk_camera*) ; 
 int /*<<< orphan*/  usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 struct stk_camera* vdev_to_camera (struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_stk_open(struct file *fp)
{
	struct stk_camera *dev;
	struct video_device *vdev;

	vdev = video_devdata(fp);
	dev = vdev_to_camera(vdev);

	if (dev == NULL || !is_present(dev)) {
		return -ENXIO;
	}
	fp->private_data = dev;
	usb_autopm_get_interface(dev->interface);

	return 0;
}