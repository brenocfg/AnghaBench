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
struct v4l2_pix_format {int bytesperline; int width; int sizeimage; int height; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cafe_format_struct {int bpp; int /*<<< orphan*/  mbus_code; int /*<<< orphan*/  pixelformat; } ;
struct cafe_camera {int /*<<< orphan*/  s_mutex; } ;

/* Variables and functions */
 struct cafe_format_struct* cafe_find_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sensor_call (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  try_mbus_fmt ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (struct v4l2_mbus_framefmt*,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (struct v4l2_pix_format*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int cafe_vidioc_try_fmt_vid_cap(struct file *filp, void *priv,
		struct v4l2_format *fmt)
{
	struct cafe_camera *cam = priv;
	struct cafe_format_struct *f;
	struct v4l2_pix_format *pix = &fmt->fmt.pix;
	struct v4l2_mbus_framefmt mbus_fmt;
	int ret;

	f = cafe_find_format(pix->pixelformat);
	pix->pixelformat = f->pixelformat;
	v4l2_fill_mbus_format(&mbus_fmt, pix, f->mbus_code);
	mutex_lock(&cam->s_mutex);
	ret = sensor_call(cam, video, try_mbus_fmt, &mbus_fmt);
	mutex_unlock(&cam->s_mutex);
	v4l2_fill_pix_format(pix, &mbus_fmt);
	pix->bytesperline = pix->width * f->bpp;
	pix->sizeimage = pix->height * pix->bytesperline;
	return ret;
}