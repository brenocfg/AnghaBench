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
struct file {struct em28xx_fh* private_data; } ;
struct em28xx_fh {int users; int state; int /*<<< orphan*/  open; int /*<<< orphan*/  vb_vbiq; int /*<<< orphan*/  vb_vidq; int /*<<< orphan*/  udev; scalar_t__ alt; int /*<<< orphan*/  v4l2_dev; struct em28xx_fh* dev; } ;
struct em28xx {int users; int state; int /*<<< orphan*/  open; int /*<<< orphan*/  vb_vbiq; int /*<<< orphan*/  vb_vidq; int /*<<< orphan*/  udev; scalar_t__ alt; int /*<<< orphan*/  v4l2_dev; struct em28xx* dev; } ;

/* Variables and functions */
 int DEV_DISCONNECTED ; 
 int /*<<< orphan*/  EM28XX_RESOURCE_VBI ; 
 int /*<<< orphan*/  EM28XX_RESOURCE_VIDEO ; 
 int /*<<< orphan*/  EM28XX_SUSPEND ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  em28xx_errdev (char*,int) ; 
 int /*<<< orphan*/  em28xx_release_resources (struct em28xx_fh*) ; 
 int /*<<< orphan*/  em28xx_set_mode (struct em28xx_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_uninit_isoc (struct em28xx_fh*) ; 
 int /*<<< orphan*/  em28xx_videodbg (char*,...) ; 
 int /*<<< orphan*/  kfree (struct em28xx_fh*) ; 
 scalar_t__ res_check (struct em28xx_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_free (struct em28xx_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_power ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_nr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int em28xx_v4l2_close(struct file *filp)
{
	struct em28xx_fh *fh  = filp->private_data;
	struct em28xx    *dev = fh->dev;
	int              errCode;

	em28xx_videodbg("users=%d\n", dev->users);

	if (res_check(fh, EM28XX_RESOURCE_VIDEO)) {
		videobuf_stop(&fh->vb_vidq);
		res_free(fh, EM28XX_RESOURCE_VIDEO);
	}

	if (res_check(fh, EM28XX_RESOURCE_VBI)) {
		videobuf_stop(&fh->vb_vbiq);
		res_free(fh, EM28XX_RESOURCE_VBI);
	}

	if (dev->users == 1) {
		/* the device is already disconnect,
		   free the remaining resources */
		if (dev->state & DEV_DISCONNECTED) {
			em28xx_release_resources(dev);
			kfree(dev);
			return 0;
		}

		/* Save some power by putting tuner to sleep */
		v4l2_device_call_all(&dev->v4l2_dev, 0, core, s_power, 0);

		/* do this before setting alternate! */
		em28xx_uninit_isoc(dev);
		em28xx_set_mode(dev, EM28XX_SUSPEND);

		/* set alternate 0 */
		dev->alt = 0;
		em28xx_videodbg("setting alternate 0\n");
		errCode = usb_set_interface(dev->udev, 0, 0);
		if (errCode < 0) {
			em28xx_errdev("cannot change alternate number to "
					"0 (error=%i)\n", errCode);
		}
	}

	videobuf_mmap_free(&fh->vb_vidq);
	videobuf_mmap_free(&fh->vb_vbiq);
	kfree(fh);
	dev->users--;
	wake_up_interruptible_nr(&dev->open, 1);
	return 0;
}