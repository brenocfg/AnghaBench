#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_mbus_framefmt {int width; int height; int /*<<< orphan*/  code; } ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct ivtv_open_id {struct ivtv* itv; } ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  video_encoding; } ;
struct ivtv {int /*<<< orphan*/  sd_video; TYPE_1__ cxhdl; int /*<<< orphan*/  capturing; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  V4L2_MBUS_FMT_FIXED ; 
 scalar_t__ V4L2_MPEG_VIDEO_ENCODING_MPEG_1 ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int ivtv_g_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 int ivtv_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 int /*<<< orphan*/  s_mbus_fmt ; 
 scalar_t__ v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int ivtv_s_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *fmt)
{
	struct ivtv_open_id *id = fh;
	struct ivtv *itv = id->itv;
	struct v4l2_mbus_framefmt mbus_fmt;
	int ret = ivtv_try_fmt_vid_cap(file, fh, fmt);
	int w = fmt->fmt.pix.width;
	int h = fmt->fmt.pix.height;

	if (ret)
		return ret;

	if (itv->cxhdl.width == w && itv->cxhdl.height == h)
		return 0;

	if (atomic_read(&itv->capturing) > 0)
		return -EBUSY;

	itv->cxhdl.width = w;
	itv->cxhdl.height = h;
	if (v4l2_ctrl_g_ctrl(itv->cxhdl.video_encoding) == V4L2_MPEG_VIDEO_ENCODING_MPEG_1)
		fmt->fmt.pix.width /= 2;
	mbus_fmt.width = fmt->fmt.pix.width;
	mbus_fmt.height = h;
	mbus_fmt.code = V4L2_MBUS_FMT_FIXED;
	v4l2_subdev_call(itv->sd_video, video, s_mbus_fmt, &mbus_fmt);
	return ivtv_g_fmt_vid_cap(file, fh, fmt);
}