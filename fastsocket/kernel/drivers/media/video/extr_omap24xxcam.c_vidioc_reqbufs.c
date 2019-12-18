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
struct v4l2_requestbuffers {scalar_t__ memory; } ;
struct omap24xxcam_fh {int /*<<< orphan*/  vbq; struct omap24xxcam_device* cam; } ;
struct omap24xxcam_device {int /*<<< orphan*/  mutex; scalar_t__ streaming; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int omap24xxcam_vbq_alloc_mmap_buffers (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  omap24xxcam_vbq_free_mmap_buffers (int /*<<< orphan*/ *) ; 
 int videobuf_reqbufs (int /*<<< orphan*/ *,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static int vidioc_reqbufs(struct file *file, void *fh,
			  struct v4l2_requestbuffers *b)
{
	struct omap24xxcam_fh *ofh = fh;
	struct omap24xxcam_device *cam = ofh->cam;
	int rval;

	mutex_lock(&cam->mutex);
	if (cam->streaming) {
		mutex_unlock(&cam->mutex);
		return -EBUSY;
	}

	omap24xxcam_vbq_free_mmap_buffers(&ofh->vbq);
	mutex_unlock(&cam->mutex);

	rval = videobuf_reqbufs(&ofh->vbq, b);

	/*
	 * Either videobuf_reqbufs failed or the buffers are not
	 * memory-mapped (which would need special attention).
	 */
	if (rval < 0 || b->memory != V4L2_MEMORY_MMAP)
		goto out;

	rval = omap24xxcam_vbq_alloc_mmap_buffers(&ofh->vbq, rval);
	if (rval)
		omap24xxcam_vbq_free_mmap_buffers(&ofh->vbq);

out:
	return rval;
}