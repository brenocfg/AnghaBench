#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct file {struct cx25821_fh* private_data; } ;
struct TYPE_4__ {struct cx25821_fh* read_buf; } ;
struct cx25821_fh {int /*<<< orphan*/  prio; TYPE_1__ vidq; struct cx25821_dev* dev; } ;
struct cx25821_dev {int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOURCE_VIDEO_IOCTL ; 
 int /*<<< orphan*/  buffer_release (TYPE_1__*,struct cx25821_fh*) ; 
 int /*<<< orphan*/  kfree (struct cx25821_fh*) ; 
 scalar_t__ res_check (struct cx25821_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_free (struct cx25821_dev*,struct cx25821_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_prio_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_mmap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_queue_cancel (TYPE_1__*) ; 

__attribute__((used)) static int video_release(struct file *file)
{
	struct cx25821_fh *fh = file->private_data;
	struct cx25821_dev *dev = fh->dev;

	/* stop video capture */
	if (res_check(fh, RESOURCE_VIDEO_IOCTL)) {
		videobuf_queue_cancel(&fh->vidq);
		res_free(dev, fh, RESOURCE_VIDEO_IOCTL);
	}

	if (fh->vidq.read_buf) {
		buffer_release(&fh->vidq, fh->vidq.read_buf);
		kfree(fh->vidq.read_buf);
	}

	videobuf_mmap_free(&fh->vidq);

	v4l2_prio_close(&dev->prio, &fh->prio);

	file->private_data = NULL;
	kfree(fh);

	return 0;
}