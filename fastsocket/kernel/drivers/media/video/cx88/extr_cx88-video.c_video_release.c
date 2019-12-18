#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct file {struct cx8800_fh* private_data; } ;
struct TYPE_6__ {struct cx8800_fh* read_buf; } ;
struct cx8800_fh {TYPE_1__ vbiq; TYPE_1__ vidq; struct cx8800_dev* dev; } ;
struct cx8800_dev {TYPE_4__* core; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int /*<<< orphan*/  RESOURCE_VBI ; 
 int /*<<< orphan*/  RESOURCE_VIDEO ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_release (TYPE_1__*,struct cx8800_fh*) ; 
 int /*<<< orphan*/  call_all (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  kfree (struct cx8800_fh*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ res_check (struct cx8800_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_free (struct cx8800_dev*,struct cx8800_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  videobuf_mmap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_queue_cancel (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_stop (TYPE_1__*) ; 

__attribute__((used)) static int video_release(struct file *file)
{
	struct cx8800_fh  *fh  = file->private_data;
	struct cx8800_dev *dev = fh->dev;

	/* turn off overlay */
	if (res_check(fh, RESOURCE_OVERLAY)) {
		/* FIXME */
		res_free(dev,fh,RESOURCE_OVERLAY);
	}

	/* stop video capture */
	if (res_check(fh, RESOURCE_VIDEO)) {
		videobuf_queue_cancel(&fh->vidq);
		res_free(dev,fh,RESOURCE_VIDEO);
	}
	if (fh->vidq.read_buf) {
		buffer_release(&fh->vidq,fh->vidq.read_buf);
		kfree(fh->vidq.read_buf);
	}

	/* stop vbi capture */
	if (res_check(fh, RESOURCE_VBI)) {
		videobuf_stop(&fh->vbiq);
		res_free(dev,fh,RESOURCE_VBI);
	}

	videobuf_mmap_free(&fh->vidq);
	videobuf_mmap_free(&fh->vbiq);

	mutex_lock(&dev->core->lock);
	file->private_data = NULL;
	kfree(fh);

	if(atomic_dec_and_test(&dev->core->users))
		call_all(dev->core, core, s_power, 0);
	mutex_unlock(&dev->core->lock);

	return 0;
}