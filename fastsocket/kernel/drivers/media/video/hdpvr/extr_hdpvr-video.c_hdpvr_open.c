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
struct hdpvr_fh {struct hdpvr_device* dev; } ;
struct hdpvr_device {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  open_count; int /*<<< orphan*/  v4l2_dev; } ;
struct file {struct hdpvr_fh* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hdpvr_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 scalar_t__ video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdpvr_open(struct file *file)
{
	struct hdpvr_device *dev;
	struct hdpvr_fh *fh;
	int retval = -ENOMEM;

	dev = (struct hdpvr_device *)video_get_drvdata(video_devdata(file));
	if (!dev) {
		pr_err("open failing with with ENODEV\n");
		retval = -ENODEV;
		goto err;
	}

	fh = kzalloc(sizeof(struct hdpvr_fh), GFP_KERNEL);
	if (!fh) {
		v4l2_err(&dev->v4l2_dev, "Out of memory\n");
		goto err;
	}
	/* lock the device to allow correctly handling errors
	 * in resumption */
	mutex_lock(&dev->io_mutex);
	dev->open_count++;
	mutex_unlock(&dev->io_mutex);

	fh->dev = dev;

	/* save our object in the file's private structure */
	file->private_data = fh;

	retval = 0;
err:
	return retval;
}