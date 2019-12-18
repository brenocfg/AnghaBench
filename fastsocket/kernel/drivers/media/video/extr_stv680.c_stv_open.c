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
struct usb_stv {int user; int maxframesize; int /*<<< orphan*/  fbuf; } ;
struct file {struct video_device* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int STV680_NUMFRAMES ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  rvmalloc (int) ; 
 int stv_init (struct usb_stv*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 struct video_device* video_devdata (struct file*) ; 
 struct usb_stv* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int stv_open(struct file *file)
{
	struct video_device *dev = video_devdata(file);
	struct usb_stv *stv680 = video_get_drvdata(dev);
	int err = 0;

	/* we are called with the BKL held */
	lock_kernel();
	stv680->user = 1;
	err = stv_init (stv680);	/* main initialization routine for camera */

	if (err >= 0) {
		stv680->fbuf = rvmalloc (stv680->maxframesize * STV680_NUMFRAMES);
		if (!stv680->fbuf) {
			PDEBUG (0, "STV(e): Could not rvmalloc frame bufer");
			err = -ENOMEM;
		}
		file->private_data = dev;
	}
	if (err)
		stv680->user = 0;
	unlock_kernel();

	return err;
}