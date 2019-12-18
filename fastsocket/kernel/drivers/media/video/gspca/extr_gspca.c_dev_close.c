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
struct gspca_dev {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  module; int /*<<< orphan*/  usb_lock; scalar_t__ usb_err; scalar_t__ streaming; struct file* capt_file; } ;
struct file {struct gspca_dev* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  frame_free (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_stream_off (struct gspca_dev*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dev_close(struct file *file)
{
	struct gspca_dev *gspca_dev = file->private_data;

	PDEBUG(D_STREAM, "[%s] close", current->comm);
	if (mutex_lock_interruptible(&gspca_dev->queue_lock))
		return -ERESTARTSYS;

	/* if the file did the capture, free the streaming resources */
	if (gspca_dev->capt_file == file) {
		if (gspca_dev->streaming) {
			mutex_lock(&gspca_dev->usb_lock);
			gspca_dev->usb_err = 0;
			gspca_stream_off(gspca_dev);
			mutex_unlock(&gspca_dev->usb_lock);
		}
		frame_free(gspca_dev);
	}
	file->private_data = NULL;
	module_put(gspca_dev->module);
	mutex_unlock(&gspca_dev->queue_lock);

	PDEBUG(D_STREAM, "close done");

	return 0;
}