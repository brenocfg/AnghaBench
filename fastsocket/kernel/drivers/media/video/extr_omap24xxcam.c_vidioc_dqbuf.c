#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct videobuf_buffer {scalar_t__ baddr; } ;
struct v4l2_buffer {size_t index; } ;
struct TYPE_3__ {struct videobuf_buffer** bufs; } ;
struct omap24xxcam_fh {TYPE_1__ vbq; struct omap24xxcam_device* cam; } ;
struct omap24xxcam_device {int /*<<< orphan*/  sensor_reset_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sdev; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int videobuf_dqbuf (TYPE_1__*,struct v4l2_buffer*,int) ; 
 int /*<<< orphan*/  videobuf_qbuf (TYPE_1__*,struct v4l2_buffer*) ; 
 int vidioc_int_g_needs_reset (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int vidioc_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
	struct omap24xxcam_fh *ofh = fh;
	struct omap24xxcam_device *cam = ofh->cam;
	struct videobuf_buffer *vb;
	int rval;

videobuf_dqbuf_again:
	rval = videobuf_dqbuf(&ofh->vbq, b, file->f_flags & O_NONBLOCK);
	if (rval)
		goto out;

	vb = ofh->vbq.bufs[b->index];

	mutex_lock(&cam->mutex);
	/* _needs_reset returns -EIO if reset is required. */
	rval = vidioc_int_g_needs_reset(cam->sdev, (void *)vb->baddr);
	mutex_unlock(&cam->mutex);
	if (rval == -EIO)
		schedule_work(&cam->sensor_reset_work);
	else
		rval = 0;

out:
	/*
	 * This is a hack. We don't want to show -EIO to the user
	 * space. Requeue the buffer and try again if we're not doing
	 * this in non-blocking mode.
	 */
	if (rval == -EIO) {
		videobuf_qbuf(&ofh->vbq, b);
		if (!(file->f_flags & O_NONBLOCK))
			goto videobuf_dqbuf_again;
		/*
		 * We don't have a videobuf_buffer now --- maybe next
		 * time...
		 */
		rval = -EAGAIN;
	}

	return rval;
}