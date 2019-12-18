#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ sizeimage; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_3__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cafe_format_struct {int /*<<< orphan*/  mbus_code; } ;
struct cafe_camera {scalar_t__ state; scalar_t__ n_sbufs; scalar_t__ nbufs; scalar_t__ dma_buf_size; int /*<<< orphan*/  s_mutex; TYPE_2__ pix_format; int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 scalar_t__ S_IDLE ; 
 scalar_t__ cafe_alloc_dma_bufs (struct cafe_camera*,int /*<<< orphan*/ ) ; 
 int cafe_cam_configure (struct cafe_camera*) ; 
 int cafe_ctlr_configure (struct cafe_camera*) ; 
 struct cafe_format_struct* cafe_find_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_free_dma_bufs (struct cafe_camera*) ; 
 int cafe_vidioc_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cafe_vidioc_s_fmt_vid_cap(struct file *filp, void *priv,
		struct v4l2_format *fmt)
{
	struct cafe_camera *cam = priv;
	struct cafe_format_struct *f;
	int ret;

	/*
	 * Can't do anything if the device is not idle
	 * Also can't if there are streaming buffers in place.
	 */
	if (cam->state != S_IDLE || cam->n_sbufs > 0)
		return -EBUSY;

	f = cafe_find_format(fmt->fmt.pix.pixelformat);

	/*
	 * See if the formatting works in principle.
	 */
	ret = cafe_vidioc_try_fmt_vid_cap(filp, priv, fmt);
	if (ret)
		return ret;
	/*
	 * Now we start to change things for real, so let's do it
	 * under lock.
	 */
	mutex_lock(&cam->s_mutex);
	cam->pix_format = fmt->fmt.pix;
	cam->mbus_code = f->mbus_code;

	/*
	 * Make sure we have appropriate DMA buffers.
	 */
	ret = -ENOMEM;
	if (cam->nbufs > 0 && cam->dma_buf_size < cam->pix_format.sizeimage)
		cafe_free_dma_bufs(cam);
	if (cam->nbufs == 0) {
		if (cafe_alloc_dma_bufs(cam, 0))
			goto out;
	}
	/*
	 * It looks like this might work, so let's program the sensor.
	 */
	ret = cafe_cam_configure(cam);
	if (! ret)
		ret = cafe_ctlr_configure(cam);
  out:
	mutex_unlock(&cam->s_mutex);
	return ret;
}