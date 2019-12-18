#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct file {struct cx23885_fh* private_data; } ;
struct TYPE_7__ {struct cx23885_fh* read_buf; } ;
struct TYPE_6__ {scalar_t__ reading; scalar_t__ streaming; } ;
struct cx23885_fh {TYPE_3__ vidq; TYPE_1__ vbiq; struct cx23885_dev* dev; } ;
struct cx23885_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int /*<<< orphan*/  RESOURCE_VBI ; 
 int /*<<< orphan*/  RESOURCE_VIDEO ; 
 int /*<<< orphan*/  buffer_release (TYPE_3__*,struct cx23885_fh*) ; 
 int /*<<< orphan*/  kfree (struct cx23885_fh*) ; 
 scalar_t__ res_check (struct cx23885_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_free (struct cx23885_dev*,struct cx23885_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  videobuf_mmap_free (TYPE_3__*) ; 
 int /*<<< orphan*/  videobuf_queue_cancel (TYPE_3__*) ; 
 int /*<<< orphan*/  videobuf_read_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_streamoff (TYPE_1__*) ; 

__attribute__((used)) static int video_release(struct file *file)
{
	struct cx23885_fh *fh = file->private_data;
	struct cx23885_dev *dev = fh->dev;

	/* turn off overlay */
	if (res_check(fh, RESOURCE_OVERLAY)) {
		/* FIXME */
		res_free(dev, fh, RESOURCE_OVERLAY);
	}

	/* stop video capture */
	if (res_check(fh, RESOURCE_VIDEO)) {
		videobuf_queue_cancel(&fh->vidq);
		res_free(dev, fh, RESOURCE_VIDEO);
	}
	if (fh->vidq.read_buf) {
		buffer_release(&fh->vidq, fh->vidq.read_buf);
		kfree(fh->vidq.read_buf);
	}

	/* stop vbi capture */
	if (res_check(fh, RESOURCE_VBI)) {
		if (fh->vbiq.streaming)
			videobuf_streamoff(&fh->vbiq);
		if (fh->vbiq.reading)
			videobuf_read_stop(&fh->vbiq);
		res_free(dev, fh, RESOURCE_VBI);
	}

	videobuf_mmap_free(&fh->vidq);
	file->private_data = NULL;
	kfree(fh);

	/* We are not putting the tuner to sleep here on exit, because
	 * we want to use the mpeg encoder in another session to capture
	 * tuner video. Closing this will result in no video to the encoder.
	 */

	return 0;
}